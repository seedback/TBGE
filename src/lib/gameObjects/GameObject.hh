// Copyright 2022 Chr. Alexander B. Bøhler
/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
*/

// GameObject is the base class for all objects used in a game.
// This class in itself is really simple, only containing a few properties,
//   and can by default only be LOOKed at, but can still be scripted.

// List of properties:
// * test
// * id:          A unique string used to access the element. In case multiple
//                  objects have the same id the parents id can be prefixed,
//                  seperated with a dot (eg. parentObject.thisObject).
// * Commands:    A list of command objects defining command-word-aliases and
//                  their associated command actions.
// * Descriptors:  A list of descriptors used to decide which object is being
//                  affected by any given command call, in case two or more
//                  objects fulfill all descriptors a question will be posed to
//                  the player asking them to choose.
//                  Optionally: If too many objects fulfill the descriptors, a
//                  message saying the program did not understand the command
//                  may come up. This is dependent on the
//                  options>max_described_objects property in the
//                  game-declaration file.
// * Description:  A string that is output when the LOOK command action is used
//                  on this object
// * Script:      A script to be run on this object, can be used to define
//                  custom command effects among other things.

#ifndef TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_  // NOLINT
#define TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_

#include <string>
#include <vector>

namespace tbge {
class GameObject {
 public:
  GameObject();
  explicit GameObject(const std::string id) {this->id_ = id;}
  GameObject(const GameObject& game_object) {*this = game_object;}
  ~GameObject() {}

  // id
  void id(const std::string id) {this->id_ = id;}
  std::string id() {return this->id_;}
  // commands
  //NOLINT//void commands(std::vector<TBGE::Command>);
  //NOLINT//std::vector<TBGE::Command> commands()
  //NOLINT//void add_command(TBGE::Command);
  //NOLINT//TBGE::Command get_command_by_action(std::string);
  //NOLINT//TBGE::Command get_command_by_alias(std::string);
  // descriptors
  void descriptors(std::vector<std::string> descriptors) {
    this->descriptors_ = descriptors;
  }
  std::vector<std::string> descriptors() {return descriptors_;}
  void add_descriptor(std::string descriptor) {
    this->descriptors_.push_back(descriptor);
  }
  // description
  void description(std::string desc) {this->description_ = desc;}
  std::string description() {return this->description_;}
  // script
  void script(std::string);
  std::string script();

 private:
  std::string id_ = "";
  //NOLINT//std::vector<TBGE::Command> commands;
  std::vector<std::string> descriptors_;
  std::string description_ = "";
  std::string script_;
};
}  // namespace tbge

#endif  // #ifndef TBGE_LIB_GAMEOBJECTS_GAMEOBJECT_HH_  // NOLINT
