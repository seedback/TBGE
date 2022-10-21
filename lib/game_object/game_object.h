/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 * 
 * This is the base class for all game objects in the game eg. locations,
 * location collections, exits, items etc.
 * Includes parent-child tree functionality.
 */

#ifndef TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_
#define TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_

#include <string>
#include <vector>

#include "lib/object/object.h"
#include "lib/game/game.h"
namespace tbge {

class GameObject : public Object {
 public:
  GameObject() = delete; // GameObjects has to exist in a Game
  GameObject(GameObject&); // TODO: implement
  GameObject(Game*); // TODO: implement
  GameObject(Game*, std::string); // TODO: implement
  GameObject(Game*, GameObject*); // TODO: implement
  GameObject(Game*, GameObject*, std::string); // TODO: implement
  GameObject(Game*, GameObject*, std::vector<GameObject*>); // TODO: implement
  GameObject(Game*, GameObject*, std::vector<GameObject*>, std::string);

  ~GameObject(){}

  GameObject& set_parent(GameObject*);
  GameObject* get_parent(); // TODO: implement
  GameObject& remove_parent(); // TODO: implement

  GameObject& set_children(std::vector<GameObject*>); // TODO: implement

  int get_num_children(); // TODO: implement
  std::vector<GameObject*> get_children(); // TODO: implement
  GameObject* get_child_by_index(int); // TODO: implement
  GameObject* get_child_by_id(int); // TODO: implement
  GameObject* get_child_by_name(std::string); // TODO: implement

  GameObject& add_child(GameObject*); // TODO: implement
  GameObject& add_children(std::vector<GameObject*>); // TODO: implement

  GameObject& remove_child(GameObject*);
  GameObject& remove_child_by_index(int); // TODO: implement
  GameObject& remove_child_by_id(int); // TODO: implement
  GameObject& remove_child_by_name(std::string); // TODO: implement

  std::string get_full_name() override; // TODO: implement

  const Game* game;

 private:
  GameObject& remove_parent_actual(bool);
  GameObject& remove_child_actual(GameObject*, bool);

  GameObject* parent_ = nullptr;
  std::vector<GameObject*> children_;
};
  
} // namespace tbg


#endif  // TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_