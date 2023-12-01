#include "component.h"

#include "src/game_object/game_object.h"

#include <vector>
#include <stdexcept>

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

Component::Component(Component* parent)
    : parent_(parent) {
  setId();
  parent->addChild(this);
}

// Copy constructor
Component::Component(const Component& component) 
    : Component(component.parent_) {
  // Copy children
  for (auto child : component.children_) {
    new Component(*child);
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

template <typename T> Component* Component::getChild() const {
  // Ensures that T is a Component subclass
  static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
  // Traverse children_ to find a child of type T
  for (auto child : children_) {
    if (typeid(*child) == typeid(T)) {
      return child;
    }
  }
  return nullptr;
}

Component* Component::getChild(unsigned long long child_id) const {
  // Traverse children_ to find a child with id child_id
  for (auto child : children_) {
    if (child->getId() == child_id) {
      return child;
    }
  }
  return nullptr;
}

template <typename T> std::vector<Component*> Component::getChildren() const {
  // Ensures that T is a Component subclass
  static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
  // A temporary vector to store all children that are of type T
  std::vector<Component*> children;
  // Traverse children_ to find children of type T
  // and add them to the temporary vector
  for (auto child : children_) {
    if (typeid(*child) == typeid(T)) {
      children.push_back(child);
    }
  }
  return children;
}

std::vector<Component*> Component::getChildren(
    std::vector<unsigned long long> children_ids) const {
  // A temporary vector to store all children with ids in children_ids
  std::vector<Component*> children;
  // Traverse children_ids
  for (auto child_id : children_ids) {
    children.push_back(getChild(child_id));
  }
  return children;
}

// Protected
void Component::setId() {
  id_ = Component::getId();
}

void Component::addChild(Component* child) {
  // Ensures that child is not nullptr and that child is not already a child of
  // this component
  if (child == nullptr || std::find(children_.begin(),
                                    children_.end(),
                                    child)
                              != children_.end()) {
    return;
  }
  children_.push_back(child);
}

template <typename T> bool Component::removeChild() {
  // Ensures that T is a Component subclass
  static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
  // Traverse children_ to find a child of type T
  for (auto child : children_) {
    if (typeid(*child) == typeid(T)) {
      // Remove the child from children_
      children_.erase(std::remove(children_.begin(), children_.end(), child),
                      children_.end());
      // Delete the child
      delete child;
      return true;
    }
  }
  return
}

bool Component::removeChild(unsigned long long child_id) {
  // Traverse children_ to find a child with id child_id
  for (auto child : children_) {
    if (child->getId() == child_id) {
      // Remove the child from children_
      children_.erase(std::remove(children_.begin(), children_.end(), child),
                      children_.end());
      // Delete the child
      delete child;
      return true;
    }
  }
  return false;
}

bool Component::removeChild(Component* child) {
  // Ensures that child is not nullptr
  if (child == nullptr) {
    return false;
  }
  // Traverse children_ to find child
  for (auto child : children_) {
    if (child == child) {
      // Remove the child from children_
      children_.erase(std::remove(children_.begin(), children_.end(), child),
                      children_.end());
      // Delete the child
      delete child;
      return true;
    }
  }
  return false;
}

template <typename T> bool Component::removeChildren() {
  // Ensures that T is a Component subclass
  static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
  // Temporary variable to store whether or not a child was removed
  bool removed = false;
  // Repeats until no children of type T are left
  while (true) {
    // If at least one child of type T was removed,
    // the function should return true
    if (removeChild<T>() == true) {
      removed = true;
    // If no children of type T were removed, stop repeating.
    } else {
      break;
    }
  }
  // If at least one child of type T was removed, removed will be true
  // Otherwise, removed will be false
  return removed;
}

bool Component::removeChildren(std::vector<unsigned long long> children_ids) {
  // Traverse through children_ids
  for (auto child_id : children_ids) {
    // Remove the child with id child_id
    removeChild(child_id);
  }
  return true;
}

bool Component::removeChildren(std::vector<Component*> children) {
  // Traverse through children
  for (auto child : children) {
    // Remove the child
    removeChild(child);
  }
  return true;
}
}  // namespace tbge