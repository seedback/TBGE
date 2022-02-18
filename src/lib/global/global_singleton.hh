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

namespace tbge {
namespace global {

class GlobalSingleton {
 public:
  static GlobalSingleton& getInstance() {
    static GlobalSingleton instance;  // Guaranteed to be destroyed.
                        // Instantiated on first use.
    return instance;
  }

  GlobalSingleton(GlobalSingleton const&) = delete;
  void operator=(GlobalSingleton const&) = delete;
  // Note: Scott Meyers mentions in his Effective Modern
  //       C++ book, that deleted functions should generally
  //       be public as it results in better error messages
  //       due to the compilers behavior to check accessibility
  //       before deleted status

  /**
  * @brief Setter for command_word_aliases_. Ensures that all entries (both
  *          command-words and command-actions) are all-upper-case.
  * @param command_word_aliases std::multimap containing command-word - alias
  *          pairs to replace the current command_word_aliases_ with.
  */
  void command_word_aliases(
      std::multimap<std::string, std::string> command_word_aliases) {
    std::multimap<std::string, std::string> new_multimap;
    // Iterates through command_word_aliases with the iterator it
    for (std::multimap<std::string, std::string>::iterator it =
         command_word_aliases.begin();
         it != command_word_aliases.end();
         ++it) {
      new_multimap.emplace(shf::toupper_string(it->first),
                           shf::toupper_string(it->second));
    }
    this->command_word_aliases_ = new_multimap;
  }

  /**
  * @brief Getter for command_word_aliases_.
  * @return Complete std::multimap of all command-word - alias pairs.
  */
  std::multimap<std::string, std::string> command_word_aliases() {
    return command_word_aliases_;
  }

  /**
  * @brief Adds a cpmmand-word - alias pair to the list over such pairs
  * @param command_word std::string defining the command-word the
  *          alias belongs to
  * @param alias std::string defining the alias the command-word belongs to
  */
  void add_command_word_alias(std::string command_word, std::string alias) {
    command_word_aliases_.emplace(
        shf::toupper_string(command_word),
        shf::toupper_string(alias));
  }

  /**
  * @brief Finds all aliases for a given command-word
  *          and returns it as a vector.
  * @param command_word std::string defining what command-word's aliases is
  *          to be returned.
  * @return A vector of all aliases of the given command-word.
  */
  std::vector<std::string> get_command_words_by_alias(
      std::string alias) {
    int length;
    std::pair<std::multimap<std::string, std::string>::iterator,
              std::multimap<std::string, std::string>::iterator> range;
    std::vector<std::string> command_words;

    alias = shf::toupper_string(alias);

    length = command_word_aliases_.count(alias);

    if (length) {
      command_words.reserve(length);
      range = command_word_aliases_.equal_range(alias);
      for (std::multimap<std::string, std::string>::iterator it = range.first;
           it != range.second; ++it) {
        command_words.push_back(it->second);
      }
    }
    return command_words;
  }

 private:
  GlobalSingleton() {}  // Constructor? (the {} brackets) are needed here.
  ~GlobalSingleton() {}

  // std::vector<Command> command_master_list;

  /**
   * @brief Holds command-word - command-action pairs of std::strings
   *          all in all-upper-case
   */
  std::multimap<std::string, std::string> command_word_aliases_;
};

// GlobalSingleton& test =  GlobalSingleton::getInstance();

}  // namespace global
}  // namespace tbge

#endif // #ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  //NOLINT
