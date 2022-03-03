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

// Declares the global singleton holding global data, like master lists for all
//   object types as well as command-word-aliases.

#ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  // NOLINT
#define TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <iostream>

#include "toupper_string/toupper_string.hh"

#include "src\lib\game_object\game_object.hh"

// Forward declarations to fix cyclic references
namespace tbge {
class GameObject;
}

namespace tbge {
namespace global {

/**
 * @brief A global singleton holding, among other things, master lists of all
 *        objects used in any given game.
 * 
 * @details This is to help deal with memory leaks as most objects are accessed
 *          through pointers so they can be reused elsewhere to save space.@n
 *          As this is a singleton class you cannot make new objects of the
 *          class, but you can access the one single existing instance through
 *          GlobalSingleton::get_instance().
 */

/// @todo (Seedback) update test suite
class GlobalSingleton {
 public:
 /**
  * @brief Get @b the instance of the GlobalSingleton.@n
  *        This allways returns the same instance of GlobalSingleton so only one
  *        object of this class can ever exist.
  * 
  * @return @a The instance of GlobalSingleton.@n
  *         (there can only ever be one)
  */
  static GlobalSingleton& get_instance() {
    static GlobalSingleton instance;  // Guaranteed to be destroyed.
                                      // Instantiated on first use.
    return instance;
  }


  /// @brief @b Deleted to avoid having multiple instances of the
  /// GlobalSingleton.
  GlobalSingleton(GlobalSingleton const&) = delete;

  /// @brief @b Deleted to avoid having multiple instances of the
  /// GlobalSingleton.
  void operator=(GlobalSingleton const&) = delete;
  // Note: Scott Meyers mentions in his Effective Modern
  //       C++ book, that deleted functions should generally
  //       be public as it results in better error messages
  //       due to the compilers behavior to check accessibility
  //       before deleted status

  /// @brief Setter for @ref command_word_aliases_.
  void set_command_word_aliases(
      std::multimap<std::string, std::string> new_command_word_aliases);

  /**
  * @brief Getter for @ref command_word_aliases_.
  * @return Complete `std::multimap<std::string, std::string>` of all
  *         @a command-word - @a alias pairs.
  */
  std::multimap<std::string, std::string> get_command_word_aliases() {
    return this->command_word_aliases_;
  }

  /**
  * @brief Adds a @a command-word - @a alias pair @ref command_word_aliases_
  * @param command_word An @c std::string defining the @a command_word the
  *        @a alias belongs to.
  * @param alias An @c std::string defining the @a alias the @a command-word
  *        belongs to.
  */
  void add_command_word_alias(std::string command_word, std::string alias) {
    this->command_word_aliases_.emplace(shf::toupper_string(command_word),
                                  shf::toupper_string(alias));
  }

  /// @brief Finds all @a command-words for a given @a alias
  ///        and returns them as a @c std::vector<std::string>.
  std::vector<std::string> get_command_words_by_alias(std::string alias);

  /// @brief accessor for @ref game_objects_
  std::vector<GameObject*> get_game_objects() {
    return this->game_objects_;
  }

  /// @brief adds a tbge::GameObject to game_objects_
  void add_game_object(GameObject* game_object) { //NOLINT
    game_objects_.push_back(game_object);
  }

 private:
  /// @brief Private constructor to avoid multiple objects of GlobalSingleton.
  GlobalSingleton() {}


  /// @brief Private destructor to ensure the object is only ever destroyed at
  ///        program termination.
  ~GlobalSingleton() {}


  /// @brief Holds @a command-word - @a alias pairs of @c std::strings
  ///        all in all-upper-case.
  std::multimap<std::string, std::string> command_word_aliases_;

  /**
   *  @brief Holds a comprehensive list of all @a GameObjects used in the
   *         current game, this is done to avoid memory leaks between games
   *         launched in the same session.
   */
  std::vector<GameObject*> game_objects_;

  // std::vector<Command> command_master_list;
};

}  // namespace global
}  // namespace tbge

#endif // #ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  //NOLINT
