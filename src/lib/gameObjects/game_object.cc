// NOLINT(legal/copyright)
/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
*/

#include "src/lib/gameObjects/game_object.hh"

#include <iostream>

#include "src/lib/global/global_singleton.hh"

namespace tbge {

/**
 * @see tbge::global::GlobalSingleton
 * @see tbge::global::GlobalSingleton::get_instance()
 * @see tbge::global::GlobalSingleton::add_game_object()
 */
void GameObject::register_game_object() {
  tbge::global::GlobalSingleton& global_singleton =
      global::GlobalSingleton::get_instance();

  global_singleton.add_game_object(this);
}

/**
 * @param new_parent A pointer to the object to set as the new parent
 * 
 * @see tbge::GameObject::remove_child_by_id();
 * @see tbge::GameObject::add_child();
 * @see tbge::GameObject::update_full_name();
 */
void GameObject::set_parent(GameObject* new_parent) {
  if (parent_ != nullptr) {
    parent_->remove_child_by_id(id_);
  }
  parent_ = new_parent;
  parent_->add_child(this);
  update_full_name();
}
/**
 * @details Passes the reference @a new_parent as a pointer to
 *          @ref set_parent(GameObject*)
 * 
 * @param new_parent A reference to the object to set as the new parent
 * @see tbge::GameObject::set_parent(GameObject*);
 * @see tbge::GameObject::remove_child_by_id();
 * @see tbge::GameObject::add_child();
 * @see tbge::GameObject::update_full_name();
 */
// I chose to put this definition here instead of in the declaration, contrary
// to the styleguides to increase readability
void GameObject::set_parent(GameObject& const new_parent) {
  GameObject::set_parent(&new_parent);
}

/**
 * @details In the case that multiple children has the same @ref name, only the
 *          first will be returned. @n
 *          If you want to access the child of a child, you can prepend the
 *          name of the parent, separated with a <code>.</code>. @n
 *          This works recursively.
 * 
 * @param name Correspons to the @ref name_ property og the child you want to get.
 * @return tgbe::GameObject* pointer to the child
 * @see children_
 */
GameObject* GameObject::get_child_by_name(std::string name) {
  std::string cur_name = "";

  /*
   * Going throug @a name, appending the first character each time onto
   * @a cur_name and deleting it from @a name, until a dot is separating dot
   * is reached.
   */
  while (true) {
    if (name[0] == '.' || name.size() == 0) break;
    cur_name.push_back(name[0]);
    name.erase(name.begin());
  }
  /// Erasing separating dot
  name.erase(name.begin());

  /// Finding the child (if any) which @a name_ attribute is the same as
  /// @a cur_name.
  for (int i = 0; i < this->children_.size(); i++) {
    if (this->children_[i]->name_ == cur_name) {
      /// If this is the last layer needed, return the current child.
      if (name == "") {
        return this->children_[i];
      }
      /// Otherwise recursively run this function on the current child.
      return this->children_[i]->get_child_by_name(name);
    }
  }
  return nullptr;
}
}  // namespace tbge
