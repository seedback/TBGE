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

// Class definition for the basic interactable object class.
// This class is used for all objects that will react to one or more
//   dynamically generated commands consisting of a command-word and one or
//   more descriptors.
// Is not meant to be used by itself, but to be inherited from.

#ifndef TBGE_LIB_GAME_OBJECT_INTERACTABLE_OBJECT_HH_  // NOLINT
#define TBGE_LIB_GAME_OBJECT_INTERACTABLE_OBJECT_HH_

#include <string>
#include <vector>

#include "src/lib/game_object/game_object.hh"

// #include "lib/command/Command.hh"

namespace tbge {
class InteractableObject : public GameObject{
 public:

 private:

};
}  // namespace tbge

#endif // #ifndef TBGE_LIB_GAME_OBJECT_INTERACTABLE_OBJECT_HH_  //NOLINT