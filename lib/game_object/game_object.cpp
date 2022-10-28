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
  SetName(GetClassName() + "_dud");
  SetId(-1);
}
GameObject::GameObject(GameObject& obj) {
  SetName(obj.GetName());
  game = obj.GetGame();
  parent_ = obj.GetParent();
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
  SetParent(parent);
  SetChildren(children);
  SetName(name);
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
  // TODO(Seedback): Add registering and unregister game objects in tbge::Game
  // Game.unregister_game_object(this);
  if (GetId() != -1) {
    RemoveParent();
    while (children_.size() > 0) {
      RemoveChild(children_.at(0));
    }
  }
}

GameObject& GameObject::SetParent(GameObject* parent) {
  if (parent_ == parent) {
    return *this;
  }
  if (parent_) {
    parent_->RemoveChild(this);
  }
  parent_ = parent;
  parent_->AddChild(this);
  return *this;
}

GameObject* GameObject::GetParent() {
  return parent_;
}

GameObject& GameObject::RemoveParent() {
  return RemoveParentActual(false);
}

GameObject& GameObject::SetChildren(std::vector<GameObject*> children) {
  children_.clear();
  for (GameObject* c : children) {
    AddChild(c);
  }
  return *this;
}

int GameObject::GetNumChildren() {
  return children_.size();
}

std::vector<GameObject*> GameObject::GetChildren() {
  return children_;
}

GameObject* GameObject::GetChildByIndex(int index) {
  if (index >= 0 && index < children_.size()) {
    return children_[index];
  }
  return game->GetDudGameObject();
}

GameObject* GameObject::GetChildById(int id) {
  for (GameObject* child : children_) {
    if (child->GetId() == id) {
      return child;
    }
  }
  return game->GetDudGameObject();
}

GameObject* GameObject::GetChildByName(std::string name) {
  for (GameObject* child : children_) {
    if (child->GetName() == name) {
      return child;
    }
  }
  return game->GetDudGameObject();
}

GameObject& GameObject::AddChild(GameObject* child) {
  for (GameObject* c : children_) {
    if (child == c) {
      return *this;
    }
  }
  children_.push_back(child);
  child->SetParent(this);
  return *this;
}

GameObject& GameObject::AddChildren(std::vector<GameObject*> children) {
  for (GameObject* child : children) {
    AddChild(child);
  }
  return *this;
}

GameObject& GameObject::RemoveChild(GameObject* child) {
  return RemoveChildActual(child, false);
}

GameObject& GameObject::RemoveChildByIndex(int index) {
  if (index >= 0 && index < children_.size()) {
    children_.at(index)->RemoveParentActual(true);
    children_.erase(children_.begin() + index);
  }
  return *this;
}

Game* GameObject::GetGame() {
  return game;
}

std::string GameObject::GetClassName() {
  return "GameObject";
}

std::string GameObject::GetFullName() {
  if (parent_) {
    return parent_->GetFullName() + "." + GetName();
  }
  return GetName();
}

GameObject& GameObject::RemoveParentActual(bool isFinal) {
  if (!isFinal && parent_) {
    parent_->RemoveChildActual(this, true);
  }
  parent_ = nullptr;
  return *this;
}

GameObject& GameObject::RemoveChildActual(GameObject* child, bool isFinal) {
  for (int i = 0; i < children_.size(); i++) {
    if (children_.at(i) == child) {
      return RemoveChildByIndex(i);
    }
  }
  return *this;
}

}  // namespace tbge
