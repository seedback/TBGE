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

#include "src/lib/game_object/game_object.hh"

#include <iostream>

#include "src/lib/global/game_controller.hh"
#include "src/lib/command/command.hh"

namespace tbge {


GameObject::GameObject() {
    assign_id();
    this->set_name(class_name_ + "_" + std::to_string(this->id_));
    register_game_object();
    children_ = std::vector<GameObject*>();
    update_full_name();

    add_valid_action(CommandAction::kLook);
    add_valid_action(CommandAction::kGo);
  }

/**
 * @see tbge::global::GameController
 * @see tbge::global::GameController::get_instance()
 * @see tbge::global::GameController::add_game_object()
 */
void GameObject::register_game_object() {
  tbge::global::GameController& global_singleton =
      global::GameController::get_instance();

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

/**
 * @brief 
 * @param descriptors 
 * @return std::vector<GameObject*> 
 */
std::vector<GameObject*> GameObject::find_objects_by_descriptors(
    std::vector<std::string> descriptors) {
  std::vector<GameObject*> described_objects;
  for (auto& i : descriptors) i = shf::toupper_string(i);

  for (auto& i : descriptors) {
    std::cout << "input descriptors: " << i << std::endl;
    for (auto& n :
        global::GameController::get_instance().get_words_by_alias(i)) {
      std::cout << "aliases: " << n << std::endl;
    }
  }

  for (auto& i : descriptors_) std::cout << ". ." << i << std::endl;

  // For each given descriptor, at least one valid word should match at least
  // one of the object's descriptors.
  bool object_is_described = true;
  for (auto& desc : descriptors) {
    bool desc_is_valid = false;
    for (auto& local_desc : descriptors_) {
      if (global::GameController::get_instance().check_alias_of_word(desc,
          local_desc)) {
        desc_is_valid = true;
      }
    }
    if (!desc_is_valid) {
      object_is_described = false;
    }
  }

  std::cout << object_is_described << std::endl;

  if (object_is_described) {
    std::cout << "described" << std::endl;
    described_objects.push_back(this);
  }

  for (auto& i : children_) {
    std::vector<GameObject*> temp =
        i->find_objects_by_descriptors(descriptors);
    described_objects.insert(described_objects.end(),
        temp.begin(), temp.end());
  }
  return described_objects;
}
}  // namespace tbge
