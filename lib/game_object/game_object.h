/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 * 
 * This is the base class for all game objects in the game eg. locations,
 * location collections, exits, items etc.
 * Includes parent-child tree functionality.
 */

// NOLINT(build/header_guard)
#ifndef TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_
#define TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_

#include <string>
#include <vector>

#include "lib/object/object.h"
#include "lib/game/game.h"
namespace tbge {
class Game;
class GameObject : public Object {
 public:
  /**
   * Default constructor creates a dud-object with name "dud" and id -1.
   * @warning The constructed object must be explicitly deleted to avoid memory
   *          leaks.@n
   *          Unlike other constructors this objects created by this constructor
   *          will not be registered to, and thus cleaned up by, a Game
   *          instance.
   */
  GameObject();
  GameObject(GameObject&);  // TODO(Seedback): implement
  explicit GameObject(Game*);  // TODO(Seedback): implement
  GameObject(Game*, std::string);  // TODO(Seedback): implement
  GameObject(Game*, GameObject*);  // TODO(Seedback): implement
  GameObject(Game*, GameObject*, std::string);  // TODO(Seedback): implement
  GameObject(Game*, std::vector<GameObject*>);  // TODO(Seedback): implement
  // TODO(Seedback): implement
  GameObject(Game*, std::vector<GameObject*>, std::string);
  // TODO(Seedback): implement
  GameObject(Game*, GameObject*, std::vector<GameObject*>);
  GameObject(Game*, GameObject*, std::vector<GameObject*>, std::string);

  ~GameObject() {}

  /**
   * @details Sets @c this.parent_ to @a parent. If @c this.parent_ is already
   *          set it removes @c this instance of GameObject from the parent's
   *          @c children_ list
   * @return GameObject& Reference to @c this to allow for method-chaining
   */
  GameObject& set_parent(GameObject*);
  GameObject* get_parent();  // TODO(Seedback): implement
  GameObject& remove_parent();  // TODO(Seedback): implement

  // TODO(Seedback): implement
  GameObject& set_children(std::vector<GameObject*>);
  int get_num_children();  // TODO(Seedback): implement
  std::vector<GameObject*> get_children();  // TODO(Seedback): implement
  GameObject* get_child_by_index(int);  // TODO(Seedback): implement
  GameObject* get_child_by_id(int);  // TODO(Seedback): implement
  GameObject* get_child_by_name(std::string);  // TODO(Seedback): implement

  GameObject& add_child(GameObject*);
  // TODO(Seedback): implement
  GameObject& add_children(std::vector<GameObject*>);

  GameObject& remove_child(GameObject*);
  GameObject& remove_child_by_index(int);  // TODO(Seedback): implement
  GameObject& remove_child_by_id(int);  // TODO(Seedback): implement
  GameObject& remove_child_by_name(std::string);  // TODO(Seedback): implement

  Game* get_game();

  std::string get_class_name() override;
  /**
   * @brief Returns the full name of the object, which is on the format
   *        @c [parent.full_name].[this.name]
   */
  std::string get_full_name() override;  // TODO(Seedback): implement

 protected:
  Game* game = nullptr;

 private:
  GameObject& remove_parent_actual(bool);
  GameObject& remove_child_actual(GameObject*, bool);

  GameObject* parent_ = nullptr;
  std::vector<GameObject*> children_;

};

}  // namespace tbge


#endif  // TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_
