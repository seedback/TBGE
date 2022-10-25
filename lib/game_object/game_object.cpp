/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */
#include <string>
#include <vector>

#include <iostream>

#include "lib/game_object/game_object.h"
#include "lib/game/game.h"

namespace tbge {
class Game;

GameObject::GameObject() {
  game = nullptr;
  set_name(get_class_name() + "_dud");
  _set_id(-1);
}
GameObject::GameObject(GameObject& obj) {
  set_name(obj.get_name());
  game = obj.get_game();
  parent_ = obj.get_parent();
}
GameObject::GameObject(Game* game, std::string name) :
            GameObject(game, nullptr, std::vector<GameObject*>(), name) {}

GameObject::GameObject(Game* game, GameObject* parent, std::string name) :
            GameObject(game, parent, std::vector<GameObject*>(), name) {}

GameObject::GameObject(Game* game,
                       std::vector<GameObject*> children,
                       std::string name) :
            GameObject(game, nullptr, children, name) {}

GameObject::GameObject(Game* game,
                       GameObject* parent,
                       std::vector<GameObject*> children,
                       std::string name) :
            Object(name), game(game) {
  set_parent(parent);
  set_children(children);
  set_name(name);
}

bool GameObject::operator== (const GameObject& rhs) {
  if (!Object::operator==(rhs)) return false;
  if (game != rhs.game) return false;
  if (parent_ != rhs.parent_) return false;
  return true;
}

bool GameObject::operator== (const Object& rhs) {
  if (!Object::operator==(rhs)) return false;
  return true;
}

GameObject::~GameObject() {
  // Game.unregister_game_object(this);
  std::cout << "destructor " << get_name() << " : " << get_id() << std::endl;
  if (get_id() != -1) {
    remove_parent();
    std::cout << "destructor2 " << children_.size() << std::endl;
    while (children_.size() > 0) {
      std::cout << "destructor3 " << children_.at(0)->get_name() << std::endl;
      remove_child(children_.at(0));
    }
  }

  std::cout << "destructor4" << std::endl;
}

GameObject& GameObject::set_parent(GameObject* parent) {
  if (parent_ == parent) {
    return *this;
  }
  if (parent_) {
    parent_->remove_child(this);
  }
  parent_ = parent;
  parent_->add_child(this);
  return *this;
}

GameObject* GameObject::get_parent() {
  return parent_;
}

GameObject& GameObject::remove_parent() {
  std::cout << "Remove parent " << get_name() << std::endl;
  return remove_parent_actual(false);
}

GameObject& GameObject::set_children(std::vector<GameObject*> children) {
  children_.clear();
  for (GameObject* c : children) {
    add_child(c);
  }
  return *this;
}

int GameObject::get_num_children() {
  return children_.size();
}

std::vector<GameObject*> GameObject::get_children() {
  return children_;
}

GameObject* GameObject::get_child_by_index(int index) {
  if (index >= 0 && index < children_.size()) {
    return children_[index];
  }
  return nullptr;
}

GameObject* GameObject::get_child_by_id(int id) {
  for (GameObject* child : children_) {
    if (child->get_id() == id) {
      return child;
    }
  }
  return game->get_dud_game_object();
}

GameObject* GameObject::get_child_by_name(std::string name) {
  for (GameObject* child : children_) {
    if (child->get_name() == name) {
      return child;
    }
  }
  return game->get_dud_game_object();
}

GameObject& GameObject::add_child(GameObject* child) {
  for (GameObject* c : children_) {
    if (child == c) {
      return *this;
    }
  }
  children_.push_back(child);
  child->set_parent(this);
  return *this;
}

GameObject& GameObject::remove_child(GameObject* child) {
  return remove_child_actual(child, false);
}

GameObject& GameObject::remove_child_by_index(int index) {
  if (index >= 0 && index < children_.size()) {
    children_.at(index)->remove_parent_actual(true);
    children_.erase(children_.begin() + index);
  }
  return *this;
}

Game* GameObject::get_game() {
  return game;
}

std::string GameObject::get_class_name() {
  return "GameObject";
}

std::string GameObject::get_full_name() {
  if (parent_) {
    return parent_->get_full_name() + "." + get_name();
  }
  return get_name();
}

GameObject& GameObject::remove_parent_actual(bool isFinal) {
  std::cout << "Remove parent actual " << get_name() << std::endl;
  if (!isFinal && parent_) {
    std::cout << "Remove parent actual1" << std::endl;
    std::cout << parent_ << std::endl;
    std::cout << parent_->get_id() << std::endl;
    std::cout << parent_->get_class_name() << std::endl;
    parent_->remove_child_actual(this, true);
  }
  std::cout << "Remove parent actual2" << std::endl;
  parent_ = nullptr;
  std::cout << "Remove parent actual3" << std::endl;
  return *this;
}

GameObject& GameObject::remove_child_actual(GameObject* child, bool isFinal) {
  std::cout << "Remove child actual " << get_name() << std::endl;
  for (int i = 0; i < children_.size(); i++) {
    if (children_.at(i) == child) {
      std::cout << "Remove child actual2 " << children_.at(i)->get_name() << " : " << children_.size() << std::endl;
      return remove_child_by_index(i);
    }
  }
  std::cout << "Remove child actual3" << std::endl;
  return *this;
}

}  // namespace tbge
