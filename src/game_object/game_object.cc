//  _________ __    _______ ______ _____  
// |  _   _  |_ \  |_   __ \   __ \ __  | 
// |_/ | | \_|_) |   | |__) | |__) |  \_| 
//     | | |  __'.   |  __ /|  ___/  ____ 
//    _| |_| |__) | _| |  \ \_|\ '.___]  |
//   |_____|_____/ |____| |___||'._____.' 
//	

#include <vector>

#include "src/game_object/game_object.hh"

namespace tbge {
  // Constructors
  GameObject::GameObject() {
    set_id();
  }

  // Accessors
  void GameObject::set_id() {
    static int id_counter = 0;
    id_ = id_counter++;
  }

  int GameObject::get_id() {
    return id_;
  }

  void GameObject::set_parent(GameObject* parent) {
    parent_ = parent;
    if (!parent_->has_child(this)){
      parent_->add_child(this);
    }
  }

  GameObject* GameObject::get_parent() {
    return parent_;
  }

  bool GameObject::has_child(GameObject* child) {
    for (GameObject* c : children_) {
      if(c == child) {
        return true;
      }
    }
    return false;
  }
  
  void GameObject::set_children(std::vector<GameObject*>) {
    throw "not implemented error";
  }
  void GameObject::add_child(GameObject* child) {
    children_.push_back(child);
    if (child->get_parent() != this) {
      child->set_parent(this);
    }
  }
  void GameObject::remove_child(GameObject*) {
    throw "not implemented error";
  }
  void GameObject::remove_child_by_index(int) {
    throw "not implemented error";
  }
  void GameObject::remove_child_by_id(int) {
    throw "not implemented error";
  }
  void GameObject::remove_child_by_name(int) {
    throw "not implemented error";
  }
  std::vector<GameObject*> GameObject::get_children() {
    throw "not implemented error";
  }
  GameObject* GameObject::get_child_by_index(int) {
    throw "not implemented error";
  }
  GameObject* GameObject::get_child_by_id(int) {
    throw "not implemented error";
  }
  GameObject* GameObject::get_child_by_name(int) {
    throw "not implemented error";
  }
}