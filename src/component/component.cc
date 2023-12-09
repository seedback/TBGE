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
  if (parent_ != nullptr) {
  }
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
  if (parent_ != nullptr) {
  }
}

// Copy constructor
Component::Component(const Component& component) 
    : Component(component.parent_) {
  // Copy components
  for (auto component : component.components_) {
    new Component(*component);
  }
}

// Destructor
Component::~Component() {
  // Delete all components and since they will also delete their components,
  // all descendants will be deleted
  while (components_.size() > 0) {
    delete components_.back();
    components_.erase(components_.end()-1);
  }
  // If this is the root object, reset the static variables
  if (this == root_) {
    id_counter_ = 0;
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

// TODO: reword all instanves of component to component
Component* Component::getComponent(unsigned long long component_id) const {
  // Traverse components_ to find a component with id child_id
  for (auto component : components_) {
    if (component->getId() == component_id) {
      return component;
    }
  }
  return nullptr;
}

std::vector<Component*> Component::getComponents(
    std::vector<unsigned long long> components_ids) const {
  // A temporary vector to store all components with ids in components_ids
  std::vector<Component*> components;
  // Traverse components_ids
  for (auto child_id : components_ids) {
    components.push_back(getComponent(child_id));
  }
  return components;
}

// Mutators
bool Component::setParent(Component* parent) {
  // Ensures that parent is not nullptr
  if (parent == nullptr) {
    return false;
  }
  // root_cannot have a parent
  if (this == root_) {
    return false;
  }
  // Ensures that parent is not this component
  if (parent == this) {
    return false;
  }
  // Ensures that parent is not already the parent of this component
  if (parent == parent_) {
    return false;
  }
  // Ensures that parent is not a descendant of this component
  // thus preventing cyclical hierarchies
  if (parent->isDescendantOf(this)) {
    return false;
  }

  if (parent_ != nullptr) {
    parent_->unregisterComponent(this);
  }
  parent->registerComponent(this);
  parent_ = parent;

  return true;
}

long long Component::addComponent(Component* component) {
  // Ensures that component is not nullptr
  if (component == nullptr) {
    return -1;
  }
  // root_ cannot be a component of another component
  if (component == root_) {
    return -1;
  }
  // Ensures that component is not this component
  if (component == this) {
    return -1;
  }
  // Ensures that component is not already a component of this component
  if (component->getParent() == this) {
    return -1;
  }
  // Ensures that this this is not a descendant of component
  // thus preventing cyclical hierarchies
  if (isDescendantOf(component)) {
    return -1;
  }

  components_.push_back(component);
  component->registerParent(this);
  return component->getId();
}

bool Component::removeComponent(unsigned long long child_id) {
  // Traverse components_ to find a component with id child_id
  for (auto component : components_) {
    if (component->getId() == child_id) {
      // Remove the component from components_
      unregisterComponent(component);
      // Delete the component
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

bool Component::removeComponents(std::vector<long long> components_ids) {
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
  if (component == nullptr) {
    return false;
  }
  if (parent_ == nullptr) {
    return false;
  }

  if (this == root_) {
    return false;
  }
  // Traverse parents until the target component
  // or the root component is reached
  if (component == parent_) {
    return true;
  }
  if (parent_->isDescendantOf(component)) {
    return true;
  }
  return false;
}

// Protected
void Component::setId() {
  id_ = id_counter_++;
}

void Component::registerComponent(Component* component) {
  components_.push_back(component);
}

void Component::unregisterComponent(Component* component) {
  auto it = std::find(components_.begin(), components_.end(), component);
  if (it != components_.end()) {
    components_.erase(it);
  }
}

void Component::registerParent(Component* parent) {
  if (parent_ != nullptr) {
    parent_->unregisterComponent(this);
  }
  parent_ = parent;
}

std::string Component::dbgToString(int num_indent) const {
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
  str += indent + "}\n";

  return str;
}

// Static Variables
Component* Component::root_ = nullptr;
long long Component::id_counter_ = 0;
}  // namespace tbge