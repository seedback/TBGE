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

namespace tbge {
enum class CommandAction{
  kInvalidAction = 0,
  kLook,
  kInspect,
  kGrab,
};

class Command {
 public:
  // command_word
  void command_word(std::string command_word) {
    this->command_word_ = command_word;
  }
  std::string command_word() {return this->command_word_;}
  // action
  void action(std::string action_name) {
    action_translate_str_to_command_action_(action_name);
  }
  std::string action() {
    return action_translate_command_action_to_str_(this->action_);
  }

 private:
  // Saves the int-equivalent of `action_name` as defined in CommandActions
  // Eg. `action_name` == "LOOK" would return `CommandActions.kLook`
  // TODO(seedback): function undefined
  void action_translate_str_to_command_action_(std::string action_name);
  // Returns the string-equivalent of `action` as defined in CommandActions.
  // Eg. `action` == `CommandActions.kLook` would return "LOOK"
  // TODO(seedback): function undefined
  std::string action_translate_command_action_to_str_(CommandAction action);

  // Compared to the first word of a player-submitted command to decide that
  //   this command is the one to be run
  // Also allows for aliases defined in the global list of aliases.
  std::string command_word_ = "";
  // An enum defining which command-action to run given the
  //   corrseponding `command-word`
  CommandAction action_ = CommandAction::kInvalidAction;
};
}  // namespace tbge

#endif // #ifndef TBGE_LIB_COMMAND_COMMAND_HH_  // NOLINT