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

// The location class is, along with the exit class the main part of the
// engine. At any one time the player will always be in one location or
// another, and can interract with anny interractable objects in these
// locations, as well as move between locations with an exit.

#ifndef TBGE_LIB_GAME_LOCATION_OBJECT_HH_  // NOLINT
#define TBGE_LIB_GAME_LOCATION_OBJECT_HH_

#include <string>
#include <vector>

#include "src/lib/game_object/game_object.hh"
#include "src/lib/game_object/exit.hh"

namespace tbge {
class Exit;
class Location : public GameObject{
 public:
  Location() : GameObject::GameObject() {}
  explicit Location(std::string name) :
      GameObject::GameObject(name) {}
  Location(std::string name, std::string description) :
      GameObject::GameObject(name, description) {}
  ~Location() {}

  void set_exits(std::vector<tbge::Exit*> exits);
  std::vector<tbge::Exit*> get_exits() {
    return exits_;
  }
  void add_exit(tbge::Exit* new_exit);
  void add_exit(tbge::Exit& const new_exit) {
    add_exit(&new_exit);
  }

 private:
  std::vector<tbge::Exit*> exits_;
};
}  // namespace tbge

#endif  // #ifndef TBGE_LIB_GAME_LOCATION_OBJECT_HH_  // NOLINT
