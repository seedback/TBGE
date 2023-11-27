#include "src/game_object/game_object_with_commands/game_object_with_commands.h"

#include <algorithm>
#include <string>
#include <vector>

#include "src/command/command.h"
#include "src/game_object/game_object.h"
#include "src/global/global.h"

namespace tbge {

// Constructor with name, parent, and children
GameObjectWithCommands::GameObjectWithCommands(
    const std::string& name, 
    GameObject* parent, 
    const std::vector<GameObject*> children)
    : GameObject(name, parent, children) {}

// Constructor with name, descriptors, commands, parent, and children
GameObjectWithCommands::GameObjectWithCommands(
    const std::string& name,
    std::vector<std::string> descriptors,
    std::vector<Command> commands, 
    GameObject* parent, 
    std::vector<GameObject*> children) {
  setId();
  setName(name);
  setDescriptors(descriptors);
  setCommands(commands);
  setParent(parent);
  setChildren(children);
  global::Global::registerGameObject(
      static_cast<GameObject*>(this));
}

// Constructor with name and children
GameObjectWithCommands::GameObjectWithCommands(
    const std::string& name,
    const std::vector<GameObject*> children)
    : GameObject(name, nullptr, children) {}

// Copy constructor
GameObjectWithCommands::GameObjectWithCommands(
    const GameObjectWithCommands& game_object_with_commands)
    : GameObjectWithCommands(
          game_object_with_commands.getName(),
          game_object_with_commands.getDescriptors(),
          game_object_with_commands.getCommands(),
          game_object_with_commands.getParent(),
          game_object_with_commands.getChildren()) {}

// Destructor
// Removes all children and parent from the GameObject.
GameObjectWithCommands::~GameObjectWithCommands() {
  removeChildren();
  removeParent();
  global::Global::unregisterGameObject(
      static_cast<GameObject*>(this));
}

// Accessors
const std::vector<Command> GameObjectWithCommands::getCommands() const {
  return commands_;
}

const std::vector<std::string> GameObjectWithCommands::getDescriptors() const {
  return descriptors_;
}

// Queries
// Returns true if the GameObject has all descriptors in the descriptors vector
const bool GameObjectWithCommands::isDescribed(
    std::vector<std::string> descriptors) const {
  for (std::string descriptor : descriptors) {
    if (std::find(descriptors_.begin(), descriptors_.end(), descriptor) ==
        descriptors_.end()) {
      return false;
    }
  }
  return true;
}

// Mutators
GameObjectWithCommands& GameObjectWithCommands::setCommands(
    std::vector<Command> commands) {
  commands_ = commands;
  return *this;
}

GameObjectWithCommands& GameObjectWithCommands::setDescriptors(
    std::vector<std::string> descriptors) {
  descriptors_ = descriptors;
  return *this;
}

GameObjectWithCommands& GameObjectWithCommands::addCommand(Command command) {
  commands_.push_back(command);
  return *this;
}

GameObjectWithCommands& GameObjectWithCommands::addDescriptor(
    std::string descriptor) {
  descriptors_.push_back(descriptor);
  return *this;
}

GameObjectWithCommands& GameObjectWithCommands::removeCommand(
    Command command) {
  commands_.erase(
      std::remove(commands_.begin(), commands_.end(), command),
      commands_.end());
  return *this;
}

GameObjectWithCommands& GameObjectWithCommands::removeDescriptor(
    std::string descriptor) {
  descriptors_.erase(
      std::remove(descriptors_.begin(), descriptors_.end(), descriptor),
      descriptors_.end());
  return *this;
}

// Commands
// Executes the command with the given command_word and arguments.
void GameObjectWithCommands::executeCommand(
    std::string command_word, std::vector<std::string> arguments) const {
  for (Command command : commands_) {
    if (command.getCommandWord() == command_word) {
      command.execute(arguments);
      return;
    }
  }
}

}  // namespace tbge
