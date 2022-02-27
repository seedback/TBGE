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

namespace tbge {
/**
 * @class Command
 * @brief Holds a command-word and a command-action.
 *        If the player uses the given command-word on an object this command
 *        is attached to, then the given command-action will be run
 *        on that object.
 */
class Command{
 public:
  Command();
  //Command(std::string command_word, CommandAction command_action);  // TODO(Seedback): implement CommandAction class + this function// NOLINT
  ~Command();

  /**
   * @brief Setter for command_word_.
   * @param command_word std::string
   */
  void command_word(std::string command_word) {
    this->command_word_ = shf::toupper_string(command_word);
  }

  /**
   * @brief Getter for command_word_.
   * @return std::string - uppercase representation of this
   *           command's command_word
   */
  std::string command_word() {return this->command_word_;}

  //void command_action(CommandAction command_action);  // TODO(Seedback): implement CommandAction class + this function// NOLINT
  //CommandAction command_action();  // TODO(Seedback): implement CommandAction class + this function// NOLINT

 private:
  std::string command_word_;
  //CommandAction command_action;  // TODO(Seedback): implement CommandAction class // NOLINT
};
}  // namespace tbge







////enum class CommandAction{
////  kInvalidAction = 0,

////  kLook,
////  kInspect,

////  kGo,

////  kTake,
////  kUse,

////  kOpen,
////  kClose,
////};

//class Command {
//  public:

//  private:

//  //std::map<std::string, int> 

//// public:
////  Command() {}
////  explicit Command(const std::string command_word,
////                   const std::string action = "") {
////    this->command_word(command_word);
////    this->action(action);
////  }
////  Command(const Command& command) {*this = command;}
////  ~Command() {}

////  // command_word
////  void command_word(std::string command_word) {
////    this->command_word_ = shf::toupper_string(command_word.c_str());
////  }
////  std::string command_word() {return this->command_word_;}
////  // action
////  void action(std::string action_name) {
////    this->action_ = action_translate_str_to_command_action_(action_name);
////  }
////  std::string action() {
////    return action_translate_command_action_to_str_(this->action_);
////  }

//// private:
////  // Saves the int-equivalent of `action_name` as defined in CommandActions
////  // Eg. `action_name` == "LOOK" would return `CommandActions.kLook`
////  // TODO(seedback): function undefined
////  CommandAction action_translate_str_to_command_action_(
////      std::string action_name);
////  // Returns the string-equivalent of `action` as defined in CommandActions.
////  // Eg. `action` == `CommandActions.kLook` would return "LOOK"
////  // TODO(seedback): function undefined
////  std::string action_translate_command_action_to_str_(CommandAction action);

////  // Compared to the first word of a player-submitted command to decide that
////  //   this command is the one to be run
////  // Also allows for aliases defined in the global list of aliases.
////  std::string command_word_ = "";
////  // An enum defining which command-action to run given the
////  //   corrseponding `command-word`
////  CommandAction action_ = CommandAction::kInvalidAction;
//};
//}  // namespace tbge

#endif // #ifndef TBGE_LIB_COMMAND_COMMAND_HH_  // NOLINT