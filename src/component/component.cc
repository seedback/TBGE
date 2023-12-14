#include "component.h"

#include <string>
#include <vector>
#include <iostream>

namespace tbge {

// Constructors
Component::Component() {
  if (root_ != nullptr) {
    throw std::runtime_error("Component default constructor should only be "
                             "called to construct the root component, "
                             "otherwise use the Component(Component* parent) "
                             "constructor");
  }
  root_ = this;
  setId();
}

Component::Component(Component* parent) {
  if (parent == nullptr) {
    throw std::runtime_error("Component(Component* parent) constructor requires "
                             "a non-null parent. To construct the root "
                             "component, use the Component() constructor"
                             "instead.");
  }
  setId();
  setParent(parent);
}

// Copy constructor
Component::Component(const Component& component) 
    : Component(component.parent_) {
  // Make copies of all components, and add them to this component
  // Since components can only have one parent this is necessary to ensure
  // that the copied component has all the necessary sub-components as some
  // logic may depend on them
  for (auto current_component : component.components_) {
    // Using copy() instead of the copy constructor allows for polymorphism
    // and ensures that the correct type of component is copied
    Component* new_component = current_component->copy();
    addComponent(new_component);
  }
}

// Destructor
Component::~Component() {
  // Delete all components and since they will also delete their components,
  // all descendants will be deleted
  while (components_.size() > 0) {
    delete components_.back();
  }

  // If this component has a parent, unregister this component from the parent
  // to avoid dangling pointers
  if (parent_ != nullptr) {
    parent_->unregisterComponent(this);
    parent_ = nullptr;
  }

  // If this is the root object, reset the static variables to their default
  // values
  if (this == root_) {
    id_counter_ = kRootId;
    root_ = nullptr;
  }
}

// Accessors
Component* Component::getRoot() {
  return root_;
}

unsigned long long Component::getId() const {
  return id_;
}

const Component* Component::getParent() const {
  return parent_;
}

Component* Component::getComponent(unsigned long long component_id) const {
  // Traverse the components_ vector to find a component with id = child_id
  // and return it
  for (auto component : components_) {
    if (component->getId() == component_id) {
      return component;
    }
  }
  // If no component with id = child_id is found, return a nullptr
  return nullptr;
}

std::vector<Component*> Component::getComponents(
    std::vector<unsigned long long> components_ids,
    bool filter_invalid_ids) const {
  // A temporary vector to store all components with ids in components_ids
  std::vector<Component*> components;
  // Traverse components_ids, and run the getComponent function on each id
  // and add the result to the temporary vector
  // This will give us a vector of all components with ids in components_ids
  for (auto child_id : components_ids) {
    // If filter_invalid_ids is true, only add components that are not nullptr
    // This is default behavior
    if (filter_invalid_ids) {
      Component* component = getComponent(child_id);
      if (component != nullptr) {
        components.push_back(component);
      }
    } else {
      components.push_back(getComponent(child_id));
    }
  }
  return components;
}

// Mutators
bool Component::setParent(Component* parent) {
  // Ensures that parent is not nullptr, to avoid segfaults
  if (parent == nullptr) {
    return false;
  }
  // root_ cannot have a parent
  if (this == root_) {
    return false;
  }
  // A component cannot be its own parent
  if (parent == this) {
    return false;
  }
  // Ensures that parent is not already the parent of this component
  // Not strictly necessary, but prevents unnecessary work
  if (parent == parent_) {
    return false;
  }
  // Ensures that parent is not a descendant of this component
  // thus preventing cyclical hierarchies
  if (parent->isDescendantOf(this)) {
    return false;
  }

  // If this component already has a parent, unregister this component from
  // the parent to avoid it baing in multiple component's component_ vectors
  if (parent_ != nullptr) {
    parent_->unregisterComponent(this);
  }
  parent->registerComponent(this);
  parent_ = parent;

  return true;
}

Component* Component::addComponent(Component* component) {
  // Ensures that component is not nullptr, to avoid segfaults
  if (component == nullptr) {
    return nullptr;
  }
  // root_ cannot be a component of another component
  if (component == root_) {
    return nullptr;
  }
  // Ensures that component is not this component
  if (component == this) {
    return nullptr;
  }
  // Ensures that component is not already a component of this component
  if (component->getParent() == this) {
    return nullptr;
  }
  // Ensures that this this is not a descendant of component
  // thus preventing cyclical hierarchies
  if (isDescendantOf(component)) {
    return nullptr;
  }
  // If registerComponent returns false, the component was not registered
  // and thus this function returns 0 to indicate that the component was not
  // added
  if (!registerComponent(component)) {
    return nullptr;
  }
  // Register the component with in this component's components_ vector
  // and set the component's parent to this component and return the component's
  // id
  component->registerParent(this);
  return component;
}

bool Component::removeComponent(unsigned long long child_id) {
  // Traverse components_ to find a component with id child_id
  for (auto component : components_) {
    if (component->getId() == child_id) {
      // Delete the component, this will also unregister it from this component
      // and delete all of its components
      delete component;
      return true;
    }
  }
  return false;
}

bool Component::removeComponent(Component* component) {
  // Traverse components_ to find component
  for (auto current_component : components_) {
    if (current_component == component) {
      // Remove the component from components_
      unregisterComponent(component);
      // Delete the component
      delete component;
      return true;
    }
  }
  return false;
}

bool Component::removeComponents(std::vector<unsigned long long> components_ids) {
  // Traverse through components_ids
  for (auto child_id : components_ids) {
    // Remove the component with id child_id
    removeComponent(child_id);
  }
  return true;
}

bool Component::removeComponents(std::vector<Component*> components) {
  // Traverse through components
  for (auto component : components) {
    // Remove the component
    removeComponent(component);
  }
  return true;
}

// Queries
bool Component::isDescendantOf(const Component* component) const {
  // Ensures that component is not nullptr, to avoid segfaults
  if (component == nullptr) {
    return false;
  }
  // If parent_ is nullptr, this component cannot be a descendant
  // of any component
  if (parent_ == nullptr) {
    return false;
  }
  // root_ cannot be a descendant of any component
  // Technically this is not necessary, because if parent_ is nullptr then this
  // component is by definition root_, but this is here for clarity
  if (this == root_) {
    return false;
  }
  // If parent_ is the target component, this component is a descendant of
  // the target component
  if (component == parent_) {
    return true;
  }
  // Traverse parents until the target component
  // or the root component is reached
  if (parent_->isDescendantOf(component)) {
    return true;
  }
  return false;
}

// Protected
void Component::setId() {
  // Sets id_ to id_counter and then increments id_counter
  id_ = id_counter_++;
}

bool Component::registerComponent(Component* component) {
  // All these tests also exist in AddComponent, but are repeated here to
  // prevent unforseen cases where this function is used outside of AddComponent
  // Ensures that component is not nullptr, to avoid segfaults
  if (component == nullptr) {
    return false;
  }
  // Ensures that component is not already a component of this component
  if (component->getParent() == this) {
    return false;
  }
  // Ensures that component is not this component
  if (component == this) {
    return false;
  }

  // Actually register the component and return true
  components_.push_back(component);
  return true;
}

bool Component::unregisterComponent(Component* component) {
  // Find component in components_ and remove it from the components_ vector
  auto it = std::find(components_.begin(), components_.end(), component);
  // std::find returns components_.end() if the component is not found
  // thus if it == components_.end() then the component was not found
  // and this function returns false to indicate that the component was not
  // unregistered because there was no component to unregister
  if (it == components_.end()) {
    return false;
  }
  // Otherwise remove the component from components_ and return true to
  // indicate that the component was unregistered
  components_.erase(it);
  return true;
}

// Note: This function whould only be used in the add/removeComponent and
// setParent functions
bool Component::registerParent(Component* parent) {
  // Ensures that parent is not nullptr, to avoid segfaults
  if (parent == nullptr) {
    return false;
  }
  // If we already have a parent, unregister this component from the parent
  // to avoid dangling pointers
  if (parent_ != nullptr) {
    parent_->unregisterComponent(this);
  }
  // Register this component as a component of the parent
  parent_ = parent;
  return true;
}

Component* Component::copy() const {
  return new Component(*this);
}

std::string Component::dbgToString(int num_indent) const {
  #ifdef TBGE_DEBUG_FUNCTIONS
  if (root_ == nullptr) {
    return "Component: root_ is nullptr";
  }
  
  std::string indent = "";
  for (int i = 0; i < num_indent; i++) {
    indent += "  ";
  }

  std::string str = "";
  str +=  indent + "Component:\n";
  str += indent + "  id_: " + std::to_string(id_) + "\n";
  if (parent_ == nullptr) {
    str += indent + "  parent_: nullptr\n";
  } else {
    str += indent + "  parent_: " + std::to_string(parent_->getId()) + "\n";
  }
  str += indent + "  components_:\n";
  for (auto component : components_) {
    str += indent + "  - " + std::to_string(component->getId()) + "\n";
  }
  str += indent + "}";

  return str;
  #else
  return "";
  #endif
}

// Static Variables
Component* Component::root_ = nullptr;
unsigned long long Component::id_counter_ = 1;

}  // namespace tbge