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
//   object types as well as aliases.
//
// NOTE: This file should not, under ANY CIRCUMSTANCES, be included directly into a project

#ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  // NOLINT
#define TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <iostream>

#include "toupper_string/toupper_string.hh"

// Forward declarations to fix cyclic references
namespace tbge {
class GameObject;
class GameObject;
class Location;
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
 *          GameController::get_instance().
 */

/// @todo (Seedback) update test suite
class GameController {
 public:
 /**
  * @brief Get @b the instance of the GameController.@n
  *        This allways returns the same instance of GameController so only one
  *        object of this class can ever exist.
  * 
  * @return @a The instance of GameController.@n
  *         (there can only ever be one)
  */
  static GameController& get_instance() {
    static GameController instance;  // Guaranteed to be destroyed.
                                      // Instantiated on first use.
    return instance;
  }

  /// @brief @b Deleted to avoid having multiple instances of the
  /// GameController.
  GameController(GameController const&) = delete;

  /// @brief @b Deleted to avoid having multiple instances of the
  /// GameController.
  void operator=(GameController const&) = delete;
  // Note: Scott Meyers mentions in his Effective Modern
  //       C++ book, that deleted functions should generally
  //       be public as it results in better error messages
  //       due to the compilers behavior to check accessibility
  //       before deleted status

  /// @brief Setter for @ref aliases_.
  void set_aliases(
      std::multimap<std::string, std::string> new_aliases);

  /**
  * @brief Getter for @ref aliases_.
  * @return Complete `std::multimap<std::string, std::string>` of all
  *         @a word - @a alias pairs.
  */
  std::multimap<std::string, std::string> get_aliases() {
    return this->aliases_;
  }

  /**
  * @brief Adds a @a word - @a alias pair @ref aliases_
  * @param word An @c std::string defining the @a word the
  *        @a alias belongs to.
  * @param alias An @c std::string defining the @a alias the @a word
  *        belongs to.
  */
  void add_alias(std::string word, std::string alias) {
    if (aliases_.count(word) == 0) {
      aliases_.emplace(shf::toupper_string(word), shf::toupper_string(word));
    }
    aliases_.emplace(shf::toupper_string(alias), shf::toupper_string(word));
  }

  /// @brief Finds all @a words for a given @a alias
  ///        and returns them as a @c std::vector<std::string>.
  std::vector<std::string> get_words_by_alias(std::string alias);

  /// @brief accessor for @ref game_objects_
  std::vector<GameObject*> get_game_objects() {
    return this->game_objects_;
  }

  /// @brief adds a tbge::GameObject to game_objects_
  void add_game_object(GameObject* game_object) { //NOLINT
    game_objects_.push_back(game_object);
  }

  void set_cur_location(Location* new_cur_location) {
    cur_location_ = new_cur_location;
  }
  void set_cur_location(Location& const new_cur_location) {
    cur_location_ = &new_cur_location;
  }
  Location* get_cur_location() {
    return cur_location_;
  }

  /// @brief One round of the internal game logic, allowing for the player to
  ///        input a command and the game to react.
  bool game_tick();
  void game_loop();

  bool check_alias_of_word(std::string alias, std::string word) {
    GameController& inst = get_instance();
    alias = shf::toupper_string(alias);

    for (auto& i : get_words_by_alias(word)) {
      if (alias == i) return true;
    }
    return false;
  }

 private:
  /// @brief Private constructor to avoid multiple objects of GameController.
  GameController() {}


  /// @brief Private destructor to ensure the object is only ever destroyed at
  ///        program termination.
  ~GameController() {}


  /// @brief Holds @a word - @a alias pairs of @c std::strings
  ///        all in all-upper-case.
  std::multimap<std::string, std::string> aliases_;

  /**
   *  @brief Holds a comprehensive list of all @a GameObjects used in the
   *         current game, this is done to avoid memory leaks between games
   *         launched in the same session.
   */
  std::vector<GameObject*> game_objects_;

  Location* cur_location_;

  // std::vector<Command> command_master_list;
};

}  // namespace global
}  // namespace tbge

#endif // #ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  //NOLINT
