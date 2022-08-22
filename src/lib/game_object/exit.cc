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

#include "src/lib/game_object/exit.hh"

#include "src/lib/global/global_functions.hh"
#include "src/lib/game_object/location.hh"

namespace tbge {

void Exit::go() {
  global::parse_print(description_on_go_);
  global::parse_print(target_->get_description());
  global::GameController::get_instance().set_cur_location(target_);
}

}  // namespace tbge
