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

#include "src/lib/command/command.hh"  // NOLINT(build/include)

#include "str_to_int/str_to_int.hh"  // from the shf library
#include "toupper_string/toupper_string.hh"  // from the shf library


namespace tbge {
//CommandAction Command::action_translate_str_to_command_action_(
//    std::string action_name) {
//  action_name = shf::toupper_string(action_name);

//  switch (shf::str_to_int(action_name.c_str())) {
//    case shf::str_to_int("LOOK"):
//      return action_ = CommandAction::kLook;
//      break;
//    case shf::str_to_int("INSPECT"):
//      return action_ = CommandAction::kInspect;
//      break;
//    case shf::str_to_int("GO"):
//      return action_ = CommandAction::kGo;
//      break;
//    case shf::str_to_int("TAKE"):
//      return action_ = CommandAction::kTake;
//      break;
//    case shf::str_to_int("USE"):
//      return action_ = CommandAction::kUse;
//      break;
//    case shf::str_to_int("OPEN"):
//      return action_ = CommandAction::kOpen;
//      break;
//    case shf::str_to_int("CLOSE"):
//      return action_ = CommandAction::kClose;
//      break;
//    default:
//      return action_ = CommandAction::kInvalidAction;
//      break;
//  }
//}


//std::string Command::action_translate_command_action_to_str_(
//    CommandAction action) {
//  switch (action) {
//    case CommandAction::kLook:
//      return "LOOK";
//      break;
//    case CommandAction::kInspect:
//      return "INSPECT";
//      break;
//      case CommandAction::kGo:
//      return "GO";
//      break;
//    case CommandAction::kTake:
//      return "TAKE";
//      break;
//    case CommandAction::kUse:
//      return "USE";
//      break;
//    case CommandAction::kOpen:
//      return "OPEN";
//      break;
//    case CommandAction::kClose:
//      return "CLOSE";
//      break;
//    case CommandAction::kInvalidAction:
//      return "INVALID_ACTION";
//      break;
//    default:
//      // This should actually never happen as it should get caught by the
//      //   compiler, but I'll leave this as a just-in-case
//      return "UNKNOWN_ACTION";
//      break;
//  }
//}
}  // namespace tbge
