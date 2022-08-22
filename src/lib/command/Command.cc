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

#include "src/lib/command/command.hh"

//#include "str_to_int/str_to_int.hh"  // from the shf library
#include "toupper_string/toupper_string.hh"  // from the shf library

#include "src/lib/global/global_functions.hh"
#include "src/lib/game_object/game_object.hh"


namespace tbge {

void Command::run_command(GameObject* game_object, CommandAction command_action) {
  if (check_command(game_object, command_action)) {
    switch (command_action) {
    case CommandAction::kGo :
      std::cout << "Going somewhere" << std::endl;
      break;
    case CommandAction::kLook :
      global::parse_print(game_object->get_description());
    default:
      break;
    }
  }
}

bool Command::check_command(GameObject* game_object,
                          CommandAction command_action) {
  for (auto& i : game_object->get_valid_actions()) {
    if (i = command_action) {
      return true;
    }
  }
  return false;
}

}  // namespace tbge
