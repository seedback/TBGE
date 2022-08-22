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

// Defines functions for the global singleton holding global data, like master
//   lists for all object types as well as command-word-aliases.

#include "src/lib/global/game_controller.hh"

#include <map>
#include <string>

#include "toupper_string/toupper_string.hh"

#include "src/lib/game_object/location.hh"

namespace tbge {
namespace global {
/**
  * @details
  *   Ensures that all entries (both @a command-words and @a aliases) are
  *   @b all-upper-case.
  * @param command_word_aliases An `std::map<std::string, std::string>`
  *          containing command-word - alias pairs to replace the current
  *          @ref command_word_aliases_.
  */
void GameController::set_aliases(
      std::multimap<std::string, std::string> new_command_word_aliases) {
    std::multimap<std::string, std::string> new_multimap;
    // Iterates through command_word_aliases with the iterator it
    for (std::multimap<std::string, std::string>::iterator it =
         new_command_word_aliases.begin(); it != new_command_word_aliases.end();
         ++it) {
      new_multimap.emplace(shf::toupper_string(it->first),
                           shf::toupper_string(it->second));
    }
    this->aliases_ = new_multimap;
  }

/**
 * @details Finding all entries in the `std::multimap<std::string,
 *            std::string>` @ref command_word_aliases_ with a key that equals
 *            @a alias and pushes the corresponding values to an
 *            `std::vector<std::string>` which is then returned.
 * @param alias `std::string` defining what @a alias' @a command-words is
 *          to be returned.
 * @return A `std::vector<std::string>` of all command-words of the given alias.
 */
std::vector<std::string> GameController::get_words_by_alias(
    std::string alias) {
  int length;
  std::pair<std::multimap<std::string, std::string>::iterator,
            std::multimap<std::string, std::string>::iterator> range;
  std::vector<std::string> command_words;

  alias = shf::toupper_string(alias);
  length = aliases_.count(alias);

  // Goes through all entries of `command_word_aliases_`, and finds those where
  //   the key (alias) matches `alias` and grabs the value (command-words), and
  //   saves them in `command_words`.
  if (length) {
    command_words.reserve(length);
    range = aliases_.equal_range(alias);
    for (std::multimap<std::string, std::string>::iterator it = range.first;
          it != range.second; ++it) {
      command_words.push_back(it->second);
    }
  }
  return command_words;
}

void GameController::game_loop() {
  std::cout << cur_location_->get_description();
  while (game_tick()) {}
}

bool GameController::game_tick() {
  static int count;

  // Take some input and act upon it


  // Just to make sure during testing this doesn't go infinitely
  count++;

  if (count >= 100) return false;
  return true;
}
}  // namespace global
}  // namespace tbge
