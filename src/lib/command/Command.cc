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

// Defines member functions forthe Command class (see Command.hh) as well as
//   the CommandActions enum

#include "str_to_int/str_to_int.hh"  // from the shf library
#include "toupper_string/toupper_string.hh"  // from the shf library

#include "Command.hh"


namespace tbge {
void Command::action_translate_str_to_command_action_(std::string action_name) {
  action_name = shf::toupper_string(action_name);
  switch (shf::str_to_int(action_name.c_str())) {
  case shf::str_to_int("LOOK"):
    this->action_ = CommandAction::kLook;
    break;
  case shf::str_to_int("INSPECT"):
    this->action_ = CommandAction::kInspect;
    break;
  case shf::str_to_int("GRAB"):
    this->action_ = CommandAction::kGrab;
    break;
  default:
    this->action_ = CommandAction::kInvalidAction;
    break;
  }
}

std::string action_translate_command_action_to_str_(CommandAction action) {
  switch (action) {
  case CommandAction::kLook:
    return "LOOK";
    break;
  case CommandAction::kInspect:
    return "INSPECT";
    break;
  case CommandAction::kGrab:
    return "GRAB";
    break;
  case CommandAction::kInvalidAction:
    return "INVALID_ACTION";
    break;
  default:
    return "UNKNOWN_ACTION";
    break;
  }
}
}  // namespace tbge
