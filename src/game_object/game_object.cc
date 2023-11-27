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

// Queries
const bool GameObject::hasChildren() const { return !children_.empty(); }

const bool GameObject::hasParent() const { return parent_ != nullptr; }

const bool GameObject::hasChild(const GameObject* child) const {
  return std::find(children_.begin(), children_.end(), child) != children_.end();
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