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

// Declares the Command class, which is used to define which command-words
//   correspond to which command-actions
// Also defines the CommandActions enum

#ifndef TBGE_LIB_COMMAND_COMMAND_HH_  // NOLINT
#define TBGE_LIB_COMMAND_COMMAND_HH_

#include <string>
#include <vector>
#include <map>

#include "toupper_string/toupper_string.hh"

#include "src/lib/game_object/game_object.hh"

namespace tbge {
enum CommandAction {
  kNoCommand,
  kGo,
  kLook,
  kTake,
  kUse,
};

/**
 * @class Command
 * @brief Holds a command-word and a command-action.
 *        If the player uses the given command-word on an object this command
 *        is attached to, then the given command-action will be run
 *        on that object.
 */
class Command{
 public:
  Command() {
    command_action_ = CommandAction::kNoCommand;
    command_word_ = "";
  }
  Command(std::string command_word, CommandAction command_action) {
    command_action_ = command_action;
    command_word_ = command_word;
  }
  ~Command() {}

  /**
   * @brief Setter for command_word_.
   * @param command_word std::string
   */
  void set_command_word(std::string command_word) {
    this->command_word_ = shf::toupper_string(command_word);
  }

  /**
   * @brief Getter for command_word_.
   * @return std::string - uppercase representation of this
   *           command's command_word
   */
  std::string get_command_word() {return this->command_word_;}

  /// @todo (Seedback): implement CommandAction class +
  ///                   command_action(CommandAction command_action)
  /// @brief Setter for @ref command_action_
  void set_command_action(CommandAction command_action) {
    command_action_ = command_action;
  }
  /// @brief Getter for @ref command_action_
  CommandAction get_command_action() {
    return command_action_;
  }

  void run_command(GameObject* game_object, CommandAction command_action);
  bool check_command(GameObject* game_object, CommandAction command_action);

 private:
  /**
   * @brief A string defining the command-word (and it's aliases) this command
   *        should be activated by.
   */
  std::string command_word_;
  CommandAction command_action_;  // TODO(Seedback): implement CommandAction class // NOLINT
};
}  // namespace tbge

#endif // #ifndef TBGE_LIB_COMMAND_COMMAND_HH_  // NOLINT