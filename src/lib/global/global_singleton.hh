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
  * @brief Setter for command word aliases.
  * @param command_word_aliases std::multimap containing command-word - alias
  *          pairs to replace the current command_word_aliases_ with.
  */
  void command_word_aliases(
      std::multimap<std::string, std::string> command_word_aliases) {
    this->command_word_aliases_ = command_word_aliases;
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
    command_word_aliases_.insert(
        std::pair<std::string, std::string>(command_word, alias));
  }

  /**
  * @brief Finds all aliases for a given command-word
  *          and returns it as a vector.
  * @param command_word std::string defining what command-word's aliases is
  *          to be returned.
  * @return A vector of all aliases of the given command-word.
  */
  std::vector<std::string> get_aliases_by_command_word(
      std::string command_word) {
    int length;
    std::pair<std::multimap<std::string, std::string>::iterator,
              std::multimap<std::string, std::string>::iterator> range;
    std::vector<std::string> aliases;

    length = command_word_aliases_.count(command_word);
    if (length) {
      aliases.reserve(length);
      range = command_word_aliases_.equal_range(command_word);
      for (std::multimap<std::string, std::string>::iterator it = range.first;
           it != range.second; ++it) {
        aliases.push_back(it->second);
      }
    }
  }

 private:
  GlobalSingleton() {}  // Constructor? (the {} brackets) are needed here.
  ~GlobalSingleton() {}

  // std::vector<Command> command_master_list;

  std::multimap<std::string, std::string> command_word_aliases_;
};

}  // namespace global
}  // namespace tbge

#endif // #ifndef TBGE_SRC_LIB_GLOBAL_GLOBAL_HH_  //NOLINT
