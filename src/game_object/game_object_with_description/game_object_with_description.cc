#include "src/game_object/game_object_with_description/game_object_with_description.h"

#include <string>
#include <iostream>

#include "src/game_object/game_object.h"

namespace tbge {

GameObjectWithDescription::GameObjectWithDescription()
    : GameObjectWithDescription("", "", "", {}, {}, nullptr, {}) {}

GameObjectWithDescription::GameObjectWithDescription(
    const std::string& name,
    GameObject* parent,
    const std::vector<GameObject*> children)
    : GameObjectWithDescription(name, "", "", {}, {}, parent, children) {}

GameObjectWithDescription::GameObjectWithDescription(
    const std::string& name,
    const std::vector<std::string> descriptors,
    const std::vector<Command> commands,
    GameObject* parent,
    const std::vector<GameObject*> children)
    : GameObjectWithDescription(name, "", "", descriptors, commands, parent, children) {}

GameObjectWithDescription::GameObjectWithDescription(
    const std::string& name,
    const std::vector<GameObject*> children)
    : GameObjectWithDescription(name, "", "", {}, {}, nullptr, children) {}

GameObjectWithDescription::GameObjectWithDescription(
    const std::string& name,
    const std::string description,
    const std::string short_description,
    const std::vector<std::string> descriptors,
    const std::vector<Command> commands,
    GameObject* parent,
    const std::vector<GameObject*> children)
    : GameObjectWithCommands(name, descriptors, commands, parent, children),
      description_(description),
      short_description_(short_description) {}

GameObjectWithDescription::GameObjectWithDescription(
    const GameObjectWithDescription& game_object_with_description) {
  setId();
  setName(game_object_with_description.getName());
  setDescriptors(game_object_with_description.getDescriptors());
  setCommands(game_object_with_description.getCommands());
  setParent(game_object_with_description.getParent());
  setChildren(game_object_with_description.getChildren());
  setDescription(game_object_with_description.getDescription());
  setShortDescription(game_object_with_description.getShortDescription());
}

GameObjectWithDescription::~GameObjectWithDescription() {}

// Accessors
/**
 * @brief Returns the description of the game object.
 * 
 * If the description is empty, it checks if the short description is empty.
 * If the short description is also empty, it returns an empty string.
 * Otherwise, it returns the short description.
 * 
 * @return The description of the game object.
 */
const std::string GameObjectWithDescription::getDescription() const {
  if (description_.empty()) {
    if (short_description_.empty()) {
      return "";
    }
    return short_description_;
  }
  return description_;
}

/**
 * @brief Get the short description of the game object.
 * 
 * If the short description is empty, it will return the description.
 * If both the short description and the description are empty, it will return an empty string.
 * 
 * @return std::string The short description of the game object.
 */
const std::string GameObjectWithDescription::getShortDescription() const {
  if (short_description_.empty()) {
    if (description_.empty()) {
      return "";
    }
    return description_;
  }
  return short_description_;
}

// Mutators
/**
 * @brief Sets the description of the game object.
 * 
 * @param description The new description of the game object.
 */
void GameObjectWithDescription::setDescription(const std::string& description) {
  description_ = description;
}

/**
 * @brief Sets the short description of the game object.
 * 
 * @param short_description The new short description.
 */
void GameObjectWithDescription::setShortDescription(const std::string& short_description) {
  short_description_ = short_description;
}

// Commands
/**
 * @brief Prints the description of the game object.
 * 
 */
void GameObjectWithDescription::printDescription() const {
  std::cout << getDescription() << std::endl;
}

/**
 * @brief Prints the short description of the game object.
 * 
 */
void GameObjectWithDescription::printShortDescription() const {
  std::cout << getShortDescription() << std::endl;
}

}  // namespace tbge
