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

// GameObject is the base class for all objects used in a game.
// This class in itself is really simple, only containing a few properties,
//   and can by default only be LOOKed at, but can still be scripted.

// List of properties:
// * test
// * id:           A unique string used to access the element. In case multiple
//                   objects have the same id the parents id can be prefixed,
//                   seperated with a dot (eg. parentObject.thisObject).

// These parts are to be moved to interactable_game_object
// * Commands:     A list of command objects defining command-word-aliases and
//                   their associated command actions.
// * Descriptors:  A list of descriptors used to decide which object is being
//                   affected by any given command call, in case two or more
//                   objects fulfill all descriptors a question will be posed to
//                   the player asking them to choose.
//                   Optionally: If too many objects fulfill the descriptors, a
//                   message saying the program did not understand the command
//                   may come up. This is dependent on the
//                   options>max_described_objects property in the
//                   game-declaration file.
// * Description:  A string that is output when the LOOK command action is used
//                   on this object
// * Script:       A script to be run on this object, can be used to define
//                   custom command effects among other things.

#ifndef TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_  // NOLINT
#define TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_

#include <string>
#include <vector>

#include "src/lib/global/global_singleton.hh"
#include "src/lib/command/command.hh"

// Forward declarations to fix cyclic references
namespace tbge {
namespace global {
class GlobalSingleton;
}
}

namespace tbge {
/**
 * @brief The base class for all objects in the game.
 * 
 * @details This class only conains an auto-assigned @ref id_ and a @ref name_
 *          that can be used to access the object through
 *          tbge::global::GlobalSingleton::get_object_by_name(std::string)
 */

/// @todo make test for tbge::GameObject
/// @todo update accessors and mutators to set_some_var() and get_some_var()
///       except when only an accessor exists
class GameObject {
 public:
  /**
   * @brief Construct a new Game Object object. @n
   *        Automatically generates a name based on @ref class_name_ and
   *        @ref id_.  @n
   *        Automatically assigns a unique integer ID. @n
   *        Automatically registers this object in
   *        @ref tbge::global::globalSingleton::game_objects_
   */
  GameObject() {
    assign_id();
    this->set_name(class_name_ + "_" + std::to_string(this->id_));
    register_game_object();
    children_ = std::vector<GameObject*>();
    update_full_name();
  }
  /** 
   * @brief Constructs a new Game Object object with a defined name instead of
   *        automatically generating it. @n
   *        Automatically assigns a unique integer ID. @n
   *        Automatically registers this object in
   *        @ref tbge::global::globalSingleton::game_objects_
   */
  // Note: inherits from default constructor to reuse the same code
  explicit GameObject(const std::string name) : GameObject() {
    set_name(name);
  }
  /// Copy constructor
  GameObject(const GameObject& game_object) {
    *this = game_object;
    assign_id();
    children_ = std::vector<GameObject*>();
  }
  /// Destructor
  ~GameObject() {}

  /// Getter for @ref id_
  int get_id() {
    return this->id_;
  }

  /// Getter for @ref class_name_
  std::string get_class_name() {
    return this->class_name_;
  }

  /// Setter for @ref name_
  void set_name(const std::string name) {
    this->name_ = name;
    update_full_name();
  }
    /// Getter for @ref name_
  std::string get_name() {
    return this->name_;
  }

  /// Getter for @ref full_name_
  std::string get_full_name() {
    return this->full_name_;
  }

  /// Setter for @ref parent_
  void set_parent(GameObject* parent);
  /// Setter for @ref parent_
  void set_parent(GameObject& const parent);
  /// Getter for @ref parent_
  GameObject* get_parent() {
    return this->parent_;
  }

  /// Getter for @ref children_
  std::vector<GameObject*> get_children() {
    return this->children_;
  }
  /**
   * @brief Gets the child-object whose @ref name_ equals @a name
   */
  GameObject* get_child_by_name(std::string name);

 protected:
  /// @brief Adds @a new_child to @ref children_
  /// @see children_
  void add_child(GameObject* new_child) {
    children_.push_back(new_child);
  }
  /// Removes the child with the defined ID from @ref children_
  void remove_child_by_id(int id) {
    for (int i = 0; i < this->children_.size(); i++) {
      if (this->children_[i]->id_ == id) {
        children_.erase(children_.begin() + i);
      }
    }
  }

 private:
  /**
   * @brief Assigns a unique ID to every object.
   * @details Uses a static int to store and increment the ID to use.
   * 
   * @see id_
   */
  void assign_id() {
    static int id_counter;
    this->id_ = id_counter;
    id_counter++;
  }

  /**
   * @brief Updates @ref full_name_ to equal the parent's @ref full_name_ +
   *        <code>.</code> + this object's @ref name_
   *        Then recursively updates the full-names of all its children.
   * 
   * @see name_
   * @see full_name_
   * @see children_
   * @see parent_
   * @see get_full_name()
   */
  void update_full_name() {
    if (parent_ == nullptr) {
      full_name_ = name_;
    } else {
      full_name_ = parent_->get_full_name() + "." + name_;
      for (int i = 0; i < children_.size(); i++) {
        children_[i]->update_full_name();
      }
    }
  }

  /// @brief Registers this object in
  ///        tbge::global::GlobalSingleton::game_objects_
  void register_game_object();

  /// @brief An automatically assigned ID, each ID is unique @n
  ///        <b>Not mutable</b>
  /// @see get_id()
  int id_;

  /**
   * @brief Used to generate automatic object names. If no name is defined in
   *        the constructor's arguments the object will be named by the format:
   *        @ref class_name_ + "_" + @ref id_ @n
   *        <b>Not Mutable</b>
   * @see get_class_name()
   */
  std::string class_name_ = "GameObject";

  /**
   * @brief A name for the object used for accessing the object through
   *        commands. In the case of multiple objects having the same name, the
   *        object can be accessed through the object's full-name. Only the end
   *        of the full-name is nessecary, up until it is unique. @n
   *        @b Example:
   *        <code>parents_parent_name.parent_name.object_name</code> @n
   *        @b Example: <code>parent_name.object_name</code>
   * @see get_name()
   * @see set_name(std::string)
   */
  std::string name_;

  /** 
   * @brief Stores the full name of the object. This is the name of the object
   *        prepended by the full-name of its parent, separated with a "." @n
   *        @b Example:
   *        <code>parents_parent_name.parent_name.object_name</code>
   * @see get_full_name()
   */
  std::string full_name_;

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
  std::vector<GameObject*> children_;
};
}  // namespace tbge

#endif  // #ifndef TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_  // NOLINT
