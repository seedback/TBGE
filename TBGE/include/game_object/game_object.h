/*
 * _____________________________
 *    _____ ____   ____ _____
 *   |_   _| __ ) / ___| ____|
 *     | | |  _ \| |  _|  _|
 *     | | | |_) | |_| | |___
 *     |_| |____/ \____|_____|
 * _____________________________
 */

// Defines the base class for all game objects

#include <string>
#include <vector>

#pragma once
namespace tbge {

class GameObject {
 public:
  
  GameObject();
  GameObject(GameObject& game_object);
  GameObject(std::string name); 
  GameObject(std::string name, GameObject* parent,
             std::vector<GameObject*> children);

  // Getters
  int get_id() { return id_; }
  std::string get_class_name() { return class_name_; }
  std::string get_name() { return name_; }
  std::string get_full_name();
  GameObject* get_parent() { return parent_; }
  std::vector<GameObject*> get_children() { return children_; }

  // Setters
  GameObject& set_name(std::string name);
  GameObject& set_parent(GameObject* parent);
  GameObject& set_children(std::vector<GameObject*> children);

  // Adders
  GameObject& add_child(GameObject* child);
  GameObject& add_children(std::vector<GameObject*> children);

  // Removers
  GameObject& remove_parent();
  GameObject& remove_child(GameObject* child);

 private:
  GameObject& AssignId();
  GameObject& AssignDefaultName();

  int FindIndexOfChild(GameObject* child);

  /**
   * @brief An automatically assigned ID, each ID is unique @n
   *        @b Effectively const
   * @see get_id()
   */
  int id_;

  /**
   * @brief Used to generate automatic object names. If no name is passed to the
   *        constructor the object will be named by this format:
   *        @ref class_name_ + "_" + @ref id_ @n
   * @see get_class_name()
   */
  const std::string class_name_ = "GameObject";

  /**
   * @brief A name for the object used for accessing the object through
   *        commands. In the case of multiple objects having the same name, the
   *        object can be accessed through the object's full-name. Only the end
   *        of the full-name is nessecary, up until it is unique. @n
   *        @b Example:
   *        <code>grandparent_name.parent_name.object_name</code> @n
   *        @b Example: <code>parent_name.object_name</code>
   * @see get_name()
   * @see set_name(std::string)
   */
  std::string name_;

  /**
   * @brief Pointer to the parent of the object
   *
   * @see get_parent()
   * @see set_parent(GameObject*)
   */
  GameObject* parent_ = nullptr;

  /**
   * @brief A list of pointers to the child-objects of this object @n
   *        Is automatically updated when the parent of a child is changed.
   *
   * @see get_children()
   * @see add_child(GameObject*)
   * @see set_parent(GameObject*)
   */
  std::vector<GameObject*> children_ = std::vector<GameObject*>();
};

}  // namespace tbge
