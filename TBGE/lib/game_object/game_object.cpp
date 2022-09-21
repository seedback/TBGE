#include "include\game_object\game_object.h"

namespace tbge {
GameObject::GameObject() {
  GameObject::GameObject("", (GameObject*)nullptr, std::vector<GameObject*>());
}

GameObject::GameObject(GameObject& game_object) {
  this->id_ = game_object.get_id();
  this->name_ = game_object.get_name();
  this->parent_ = game_object.get_parent();
  this->children_ = game_object.get_children();
}

GameObject::GameObject(std::string name, GameObject* parent,
                       std::vector<GameObject*> children) {
  assign_id();
  if (name != "") {
    set_name(name);
  } else {
    assign_default_name();
  }

  set_parent(parent);
  set_children(children);
}

std::string GameObject::get_full_name() {
  if (this->parent_) {
    return this->parent_->get_full_name() + "." + this->name_;
  }
  return this->name_;
}

GameObject& GameObject::set_name(std::string name) {
  name_ = name;
  return *this;
}

GameObject& GameObject::set_parent(GameObject* parent) {
  throw 
}
}  // namespace tbge