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

#include "src/lib/game_object/location.hh"

#include "src/lib/game_object/exit.hh"


namespace tbge {

void Location::add_exit(tbge::Exit* new_exit) {
  add_child(new_exit);
  exits_.push_back(new_exit);
}

}  // namespace tbge
