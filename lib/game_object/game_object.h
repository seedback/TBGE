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
  GameObject(GameObject&);
  explicit GameObject(Game*, std::string = "");
  GameObject(Game*, GameObject*, std::string = "");
  GameObject(Game*, std::vector<GameObject*>, std::string = "");
  GameObject(Game*, GameObject*, std::vector<GameObject*>, std::string = "");
  /**
   * @note Ignores @a children_ and @a id_ as these can never be the same
   *       because each game_object can only ever have one parent, and each id
   *       (except -1) is unique.
  */
  bool GameObject::operator== (const GameObject&);
  bool GameObject::operator== (const Object&);

  ~GameObject();

  /**
   * @details Sets @c this.parent_ to @a parent. If @c this.parent_ is already
   *          set it removes @c this instance of GameObject from the parent's
   *          @c children_ list
   * @return GameObject& Reference to @c this to allow for method-chaining
   */
  GameObject& SetParent(GameObject*);
  GameObject* GetParent();
  GameObject& RemoveParent();

  GameObject& SetChildren(std::vector<GameObject*>);
  int GetNumChildren();
  std::vector<GameObject*> GetChildren();
  GameObject* GetChildByIndex(int);
  GameObject* GetChildById(int);
  GameObject* GetChildByName(std::string);

  GameObject& AddChild(GameObject*);
  // TODO(Seedback): implement
  GameObject& AddChildren(std::vector<GameObject*>);

  GameObject& RemoveChild(GameObject*);
  GameObject& RemoveChildByIndex(int);  // TODO(Seedback): implement
  GameObject& RemoveChildById(int);  // TODO(Seedback): implement
  GameObject& RemoveChildByName(std::string);  // TODO(Seedback): implement

  Game* GetGame();

  std::string GetClassName() override;
  /**
   * @brief Returns the full name of the object, which is on the format
   *        @c [parent.full_name].[this.name]
   */
  std::string GetFullName() override;  // TODO(Seedback): implement

 protected:
  Game* game = nullptr;

 private:
  GameObject& RemoveParentActual(bool);
  GameObject& RemoveChildActual(GameObject*, bool);

  GameObject* parent_ = nullptr;
  std::vector<GameObject*> children_;

};

}  // namespace tbge


#endif  // TBGE_LIB_GAMEOBJECT_GAMEOBJECT_H_
