/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
* game_object.cc
*/

#include "game_object.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "src/global/global.h"
#include "src/command/command.h"

namespace tbge {
namespace global {
  class Global;
}
// Public
// Constructors
// Default constructor
GameObject::GameObject() : GameObject("") {}

// Constructor with name, parent, and children
GameObject::GameObject(const std::string& name, 
                       GameObject* parent, 
                       const std::vector<GameObject*> children) {
  setId();
  setName(name);
  setParent(parent);
  setChildren(children);
  global::Global::registerGameObject(this);
}

// Constructor with name and children
GameObject::GameObject(const std::string& name,
                       const std::vector<GameObject*> children)
    : GameObject(name, nullptr, children) {}

// Copy constructor
GameObject::GameObject(const GameObject& game_object) {
  setId();
  setName(game_object.getName());
  setParent(game_object.getParent());
  setChildren(game_object.getChildren());
}

// GameObject::GameObject(const GameObject& game_object)
//     : GameObject(game_object.getName(),
//                  game_object.getParent(),
//                  game_object.getChildren()) {}

// Destructor
// Removes all children and parent from the GameObject.
GameObject::~GameObject() {
  removeChildren();
  removeParent();
  global::Global::unregisterGameObject(this);
}

// Accessors
int GameObject::getId() const { return id_; }

const std::string GameObject::getClassName() const { return CLASS_NAME; }

const std::string GameObject::getName() const { return name_; }

// Returns the full name of the GameObject, which is the name of the GameObject,
// prepended by the full name of its parent, separated by a period.
const std::string GameObject::getFullName() const {
  return full_name_;
}

GameObject* GameObject::getParent() const { return parent_; }

const std::vector<GameObject*> GameObject::getChildren() const { return children_; }

// Returns the component of type T.
// If the GameObject does not have a component of type T, nullptr is returned.
// If the GameObject has multiple components of type T, the first component of
// type T is returned.
template <typename T>
T* GameObject::getComponent() const {
  // Iterate over the components_ vector
  for (Component* component : components_) {
    // If the component is of type T, return the component
    T* cast_component = dynamic_cast<T*>(component);
    if (cast_component != nullptr) {
      return cast_component;
    }
  }
  // Otherwise, return nullptr
  return nullptr;
}

// Returns a vector of all components of type T.
template <typename T>
const std::vector<T*> GameObject::getComponents() const {
  // Create a vector of type T
  std::vector<T*> components;
  // Iterate over the components_ vector
  for (Component* component : components_) {
    // If the component is of type T, add the component to the vector
    T* cast_component = dynamic_cast<T*>(component);
    if (cast_component != nullptr) {
      components.push_back(cast_component);
    }
  }
  // Return the vector
  return components;
}

// Mutators
// Sets the name_ of the GameObject. if name is empty, the name_ is set to the
// default name, which is the class name, followed by the id of the GameObject,
// separated by an underscore.
GameObject& GameObject::setName(const std::string& name) {
  if (name.empty()) {
    name_ = std::string(CLASS_NAME) + "_" + std::to_string(id_);
    updateFullName();
    return *this;
  }
  name_ = name;
  updateFullName();
  return *this;
}

// Sets the parent_ of the GameObject.
// If the parent_ is not nullptr, the GameObject is removed from the parent's
// children_ vector.
// If the parent is not nullptr, the GameObject is added to the parent's
// children_ vector.
GameObject& GameObject::setParent(GameObject* parent) {
  if (parent_ != parent && parent != nullptr) {
    parent->disconnectChild(this);
  }
  removeParent();
  connectParent(parent);
  if (parent_ != nullptr) {
    parent_->connectChild(this);
  }
  return *this;
}

// Removes the GameObject from the parent's children_ vector and sets parent_ to
// nullptr.
GameObject& GameObject::removeParent() {
  if (parent_ != nullptr) {
    parent_->disconnectChild(this);
    disconnectParent();
  }
  return *this;
}

// Sets the children_ of the GameObject. Ensures all pre-existing children are
// disconnected from the GameObject.
// If the child is not nullptr and not already in the children_ vector, the
// child is added to the children_ vector and connected to the GameObject.
GameObject& GameObject::setChildren(const std::vector<GameObject*> children) {
  removeChildren();
  for (GameObject* child : children) {
    if(child != nullptr){
      addChild(child);
    }
  }
  return *this;
}

// Adds a child to the GameObject.
// If the child is not nullptr and not already in the children_ vector, the
// child is added to the children_ vector and connected to the GameObject.
GameObject& GameObject::addChild(GameObject* child) {
  if (child != nullptr && !hasChild(child)) {
    connectChild(child);
    child->setParent(this);
  }
  return *this;
}

// Removes all children from the GameObject.
GameObject& GameObject::removeChildren() {
  if (!hasChildren()) {
    return *this;
  }
  try
  {
    while(children_.size() > 0) {
      removeChild(children_.at(0));
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  return *this;
}

// Removes a child from the GameObject.
// If the child is not nullptr, and is in the children_ vector, the child is
// removed from the children_ vector and disconnected from the GameObject.
GameObject& GameObject::removeChild(GameObject* child) {
  if (child != nullptr) {
    child->disconnectParent();
    disconnectChild(child);
  }
  return *this;
}

// Adds a component to the GameObject.
template <typename T>
T& GameObject::addComponent() {
  // Ensure T is a subclass of Component
  static_assert(std::is_base_of<Component, T>::value,
                "T must be a subclass of Component");
  // Create a new component of type T
  // pasing this to the constructor to set the parent of the component
  T* component = new T(this);
  // Add the component to the components_ vector
  components_.push_back(component);
  return component;
}

// Removes a component from the GameObject based on the component's type.
template <typename T> 
GameObject& GameObject::removeComponent() {
  // Ensure T is a subclass of Component
  static_assert(std::is_base_of<Component, T>::value,
                "T must be a subclass of Component");
  // Iterate over the components_ vector
  for (Component* component : components_) {
    // Attempt to cast the component to type T
    T* cast_component = dynamic_cast<T*>(component);
    // If the cast is successful, we have a component of type T
    if (cast_component != nullptr) {
      // Remove the component from the components_
      components_.erase(std::remove(
                            components_.begin(),
                            components_.end(),
                            component),
                        components_.end());
      delete component;
      return *this;
    }
  }
  return *this;
}

// Removes the Component from the GameObject
GameObject& GameObject::removeComponent(Component* component) {
  // Remove the component from the components_
  components_.erase(std::remove(
                        components_.begin(),
                        components_.end(),
                        component),
                    components_.end());
  delete component;
  return *this;
}

// Removes all components of type T from the GameObject.
template <typename T>
GameObject& GameObject::removeComponents() {
  // Ensure T is a subclass of Component
  static_assert(std::is_base_of<Component, T>::value,
                "T must be a subclass of Component");
  // Iterate over the components_ vector
  for (Component* component : components_) {
    // Attempt to cast the component to type T
    T* cast_component = dynamic_cast<T*>(component);
    // If the cast is successful, we have a component of type T
    if (cast_component != nullptr) {
      // Remove the component from the components_
      components_.erase(std::remove(
                            components_.begin(),
                            components_.end(),
                            component),
                        components_.end());
      delete component;
    }
  }
  return *this;
}

// Removes all components from the GameObject.
GameObject& GameObject::clearComponents() {
  // Iterate over the components_ vector and delete them
  for (Component* component : components_) {
    delete component;
  }
  components_.clear();
  return *this;
}

// Removes a child from the GameObject based on the child's id.
// If the child is not nullptr, and is in the children_ vector, the child is
// removed from the children_ vector and disconnected from the GameObject.
GameObject& GameObject::removeChild(const int id) {
  for (GameObject* child : children_) {
    if (child->getId() == id) {
      removeChild(child);
      return *this;
    }
  }
  return *this;
}

// Removes a child from the GameObject based on the child's name.
// If the child is not nullptr, and is in the children_ vector, the child is
// removed from the children_ vector and disconnected from the GameObject.
GameObject& GameObject::removeChild(const std::string& name) {
  for (GameObject* child : children_) {
    if (child->getName() == name) {
      removeChild(child);
      return *this;
    }
  }
  return *this;
}

// Adds a component to the GameObject.

// Queries
const bool GameObject::hasChildren() const { return !children_.empty(); }

const bool GameObject::hasParent() const { return parent_ != nullptr; }

const bool GameObject::hasChild(const GameObject* child) const {
  return std::find(children_.begin(), children_.end(), child) 
                   != children_.end();
}

const bool GameObject::hasChild(const int id) const {
  for (GameObject* child : children_) {
    if (child->getId() == id) {
      return true;
    }
  }
  return false;
}

const bool GameObject::hasChild(const std::string& name) const {
  for (GameObject* child : children_) {
    if (child->getName() == name) {
      return true;
    }
  }
  return false;
}

// Returns true if the GameObject has a component of type T.
template <typename T>
const bool GameObject::hasComponent() const {
  // Iterate over the components_ vector
  for (Component* component : components_) {
    // Attempt to cast the component to type T
    T* cast_component = dynamic_cast<T*>(component);
    // If the cast is successful, we have a component of type T
    if (cast_component != nullptr) {
      return true;
    }
  }
  return false;
}

// Protected
// Mutators
// Connects the parent to the GameObject.
GameObject& GameObject::connectParent(GameObject* parent) {
  parent_ = parent;
  updateFullName();
  return *this;
}

// Disconnects the parent from the GameObject.
GameObject& GameObject::disconnectParent() {
  parent_ = nullptr;
  updateFullName();
  return *this;
}

// Connects the child to the GameObject.
GameObject& GameObject::connectChild(GameObject* child) {
  children_.push_back(child);
  return *this;
}

// Disconnects the child from the GameObject.
GameObject& GameObject::disconnectChild(GameObject* child) {
  children_.erase(std::remove(children_.begin(), children_.end(), child),
                  children_.end());
  return *this;
}

void GameObject::setId() {
  static int id_counter_ = 0;
  id_ = id_counter_++;
}

void GameObject::updateFullName() {
  if (hasParent()) {
    full_name_ = parent_->getFullName() + "." + name_;
    return;
  }
  full_name_ = name_;
}

}  // namespace tbge