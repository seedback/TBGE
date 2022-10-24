#include <string>
#include <vector>

#include <iostream>

#include "lib/game_object/game_object.h"
#include "lib/game/game.h"

namespace tbge {
  
GameObject::GameObject(Game* game) :
            GameObject(game, nullptr, std::vector<GameObject*>(), "") {}
GameObject::GameObject(Game* game, std::string name) : 
            GameObject(game, nullptr, std::vector<GameObject*>(), name) {}
GameObject::GameObject(Game* game,
                       GameObject* parent,
                       std::vector<GameObject*> children,
                       std::string name) : 
            Object(name), game(game) {
  set_parent(parent);
  set_children(children);
  set_name(name);
}

GameObject& GameObject::set_parent(GameObject* parent) {
  if(parent_) {
    parent_->remove_child(this);
  }
  parent_ = parent;
  return *this;
}

GameObject* GameObject::get_parent() {
  return parent_;
}

GameObject& GameObject::remove_parent() {
  return remove_parent_actual(false);
}

GameObject& GameObject::remove_parent_actual(bool isFinal) {
  if (!isFinal) {
    parent_->remove_child_actual(this, true);
  }
  parent_ = nullptr;
  return *this;
}

GameObject& GameObject::set_children(std::vector<GameObject*> children) {
  children_.clear();
  for (GameObject* c : children) {
    add_child(c);
  }
  return *this;
}

std::vector<GameObject*> GameObject::get_children() {
  return children_;
}

GameObject* GameObject::get_child_by_index(int index) {
  std::cout << children_[index] << std::endl << (index >= 0 && index < children_.size()) << std::endl;
  if (index >= 0 && index < children_.size()) {
    std::cout << "true" << std::endl;
    return children_[index];
  }
  return nullptr;
}

GameObject& GameObject::add_child(GameObject* child) {
  for(GameObject* c : children_) {
    if (child == c) {
      return *this;
    }
  }
  children_.push_back(child);
  return *this;
}

GameObject& GameObject::remove_child(GameObject* child) {
  return remove_child_actual(child, false);
}

GameObject& GameObject::remove_child_actual(GameObject* child, bool isFinal) {
  for(int i = 0; i < children_.size(); i++) {
    if(children_.at(i) == child){
      children_.at(i)->remove_parent_actual(true);
      remove_child_by_index(i);
      return *this;
    }
  }
  return *this;
}

GameObject& GameObject::remove_child_by_index(int index) {
  if(index > 0 && index < children_.size()) {
    children_.at(index)->remove_parent();
    children_.erase(children_.begin() + index);
  }
  return *this;
}

std::string GameObject::get_full_name() {
  if (parent_) {
    return parent_->get_full_name() + "." + get_name();
  }
  return get_name();
};

} // namespace tbge
