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

#ifndef TBGE_LIB_GAME_EXIT_OBJECT_HH_  // NOLINT
#define TBGE_LIB_GAME_EXIT_OBJECT_HH_

#include <string>

#include "src/lib/global/game_controller.hh"
#include "src/lib/game_object/interactable_object.hh"
#include "src/lib/game_object/location.hh"

namespace tbge {
class Exit : public GameObject {
 public:
  Exit() : GameObject::GameObject() {}
  explicit Exit(std::string name) :
      GameObject::GameObject(name) {}
  Exit(std::string name, std::string description) :
      GameObject::GameObject(name, description) {}
  Exit(std::string name, std::string description,
      std::string description_on_go) :
      GameObject::GameObject(name, description) {
    description_on_go_ = description_on_go;
  }
  ~Exit() {}

  void set_target(tbge::Location* new_target) {
    target_ = new_target;
  }
  void set_target(tbge::Location& const new_target) {
    target_ = &new_target;
  }

  void set_description_on_go(std::string new_description_on_go) {
    description_on_go_ = new_description_on_go;
  }
  std::string get_description_on_go() {
    return description_on_go_;
  }

  void go();

 private:
  tbge::Location* target_ = nullptr;

  std::string description_on_go_;
};
}  // namespace tbge

#endif  // #ifndef TBGE_LIB_GAME_EXIT_OBJECT_HH_  // NOLINT

