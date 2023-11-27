#include "global.h"

#include <iostream>

#include "src/game_object/game_object.h"

namespace tbge {
namespace global {

// Public
/**
 * Returns the singleton instance of the Global class.
 * 
 * @return The singleton instance of the Global class.
 */
Global& Global::getInstance() {
  static Global instance;
  return instance;
}

/**
 * Returns a vector of pointers to all game objects in the game.
 *
 * @return A vector of pointers to all game objects in the game.
 */
const std::vector<GameObject*> Global::getGameObjects() {
  return Global::getInstance().game_objects_;
}

/**
 * Returns a pointer to the GameObject with the specified ID.
 * If no GameObject with the specified ID is found, returns nullptr.
 *
 * @param id The ID of the GameObject to retrieve.
 * @return A pointer to the GameObject with the specified ID, or nullptr if no such GameObject exists.
 */
const GameObject* Global::getGameObject(int id) {
  for (const GameObject* game_object : getInstance().game_objects_) {
    if (game_object->getId() == id) {
      return game_object;
    }
  }
  return nullptr;
}


/**
 * @brief Splits a full name into a vector of individual names.
 * 
 * Given a full name as a string, this function splits the name into individual
 * names and returns them as a vector of strings. The full name is assumed to be
 * in the format "First Middle Last", where Middle is optional.
 * 
 * @param name The full name to split.
 * @return A vector of individual names.
 */
const std::vector<std::string> createNameListFromFullName (const std::string& name) {
  std::vector<std::string> name_list;
  std::string name_copy = name;

  while (name_copy.find(".") != std::string::npos) {
    name_list.push_back(name_copy.substr(0, name_copy.find(".")));
    name_copy = name_copy.substr(name_copy.find(".") + 1);
  }
  name_list.push_back(name_copy);
  return name_list;
}

/**
 * Seperates name by periods and searches through all game objects for a game
 * object whose full name list ends with the created vector. If multiple game
 * objects are found, the first one is returned. If no game object is found,
 * nullptr is returned.
 * 
 * @param name The name to search for.
 * @return A pointer to the GameObject, or nullptr if no such GameObject is
 * found.
 */
const GameObject* Global::getGameObject(const std::string& name) {
  std::vector<std::string> name_list = createNameListFromFullName(name);

  for (const GameObject* game_object : getInstance().game_objects_) {
    std::vector<std::string> full_name_list =
        createNameListFromFullName(game_object->getFullName());
    if (full_name_list.size() >= name_list.size() &&
        std::equal(full_name_list.end() - name_list.size(), full_name_list.end(),
                   name_list.begin())) {
      return game_object;
    }
  }
  return nullptr;
}

/**
 * Returns a vector of all GameObjects with the given name.
 * 
 * This allows for a hierarchical search through any gameObject and its parents.
 * 
 * @param name The name to search for.
 * @return A vector of GameObject pointers.
 */
const std::vector<GameObject*> Global::getAllGameObjectsWithName(const std::string& name) {
  std::vector<GameObject*> game_objects;
  for (const GameObject* game_object : getInstance().game_objects_) {
    std::string full_name = game_object->getFullName();
    if (full_name.length() >= name.length()) {
      if (full_name.substr(full_name.length() - name.length()) == name) {
        game_objects.push_back(const_cast<GameObject*>(game_object));
      }
    }
  }
  return game_objects;
}

/**
 * Checks if a game object with the given ID exists.
 * @param id The ID of the game object to check.
 * @return True if a game object with the given ID exists, false otherwise.
 */
const bool Global::hasGameObject(int id) {
  return getGameObject(id) != nullptr;
}

/**
 * Checks if a game object with the given name exists in the global game object map.
 * 
 * Searches through all game objects for a game object whose full name ends with the given name.
 * 
 * @param name The name of the game object to check for.
 * @return True if a game object with the given name exists, false otherwise.
 */
const bool Global::hasGameObject(const std::string& name) {
  return getGameObject(name) != nullptr;
}

/**
 * Adds an alias for a command word.
 * 
 * @param command The command word to add an alias for.
 * @param alias The alias to add for the command word.
 */
const void Global::addCommandWordAlias(const std::string& command, const std::string& alias) {
  if (getInstance().command_word_aliases_.find(command) == getInstance().command_word_aliases_.end()) {
    getInstance().command_word_aliases_[command] = std::vector<std::string>();
  }
  for (std::string alias_in_vector : getInstance().command_word_aliases_[command]) {
    if (alias_in_vector == alias) {
      return;
    }
  }
  getInstance().command_word_aliases_[command].push_back(alias);
}

/**
 * Returns a map of command words to their aliases.
 *
 * @return A map of command words to their aliases.
 */
const std::map<std::string, std::vector<std::string>> Global::getCommandWordAliases() {
  return getInstance().command_word_aliases_;
}

/**
 * Returns the command word associated with the given alias.
 * @param alias The alias to search for.
 * @return The command word associated with the given alias.
 */
const std::string Global::getCommandWordFromAlias(const std::string& alias) {
  for (std::map<std::string, std::vector<std::string>>::iterator it = getInstance().command_word_aliases_.begin();
       it != getInstance().command_word_aliases_.end(); ++it) {
    for (std::string alias_in_vector : it->second) {
      if (alias_in_vector == alias) {
        return it->first;
      }
    }
  }
  return "";
}

/**
 * Adds an alias to an existing command descriptor.
 * The alias is only added if it does not already exist.
 * 
 * @param command The command descriptor to add the alias to.
 * @param alias The alias to add to the command descriptor.
 */
const void Global::addDescriptorAlias(const std::string& command, const std::string& alias) {
  if (getInstance().descriptor_aliases_.find(command) == getInstance().descriptor_aliases_.end()) {
    getInstance().descriptor_aliases_[command] = std::vector<std::string>();
  }
  for (std::string alias_in_vector : getInstance().descriptor_aliases_[command]) {
    if (alias_in_vector == alias) {
      return;
    }
  }
  getInstance().descriptor_aliases_[command].push_back(alias);
}

/**
 * Returns a map of descriptor aliases.
 * The keys are descriptor names and the values are vectors of alias names.
 *
 * @return A map of descriptor aliases.
 */
const std::map<std::string, std::vector<std::string>> Global::getDescriptorAliases() {
  return getInstance().descriptor_aliases_;
}

/**
 * Returns the descriptor associated with the given alias, or an empty string if no such alias exists.
 *
 * @param alias The alias to look up.
 * @return The descriptor associated with the given alias, or an empty string if no such alias exists.
 */
const std::string Global::getDescriptorFromAlias(const std::string& alias) {
  for (std::map<std::string, std::vector<std::string>>::iterator it = getInstance().descriptor_aliases_.begin();
       it != getInstance().descriptor_aliases_.end(); ++it) {
    for (std::string alias_in_vector : it->second) {
      if (alias_in_vector == alias) {
        return it->first;
      }
    }
  }
  return "";
}

// Protected
/**
 * @brief Constructor for the Global class.
 * 
 * Initializes the game_objects_ vector and command_word_aliases_ map.
 */
Global::Global() {
  game_objects_ = std::vector<GameObject*>();
  command_word_aliases_ = std::map<std::string, std::vector<std::string>>();
}

/**
 * @brief Destructor for the Global class.
 * 
 * This destructor deletes all the GameObjects in the game_objects_ vector.
 * 
 */
Global::~Global() {
  for (GameObject* game_object : game_objects_) {
    delete game_object;
  }
}

/**
 * Registers a new game object to the global instance of the game.
 * @param game_object A pointer to the game object to be registered.
 */
void Global::registerGameObject(GameObject* game_object) {
  Global::getInstance().game_objects_.push_back(game_object);
}

/**
 * @brief Unregisters a game object from the global game object list.
 * 
 * @param game_object Pointer to the game object to be unregistered.
 */
void Global::unregisterGameObject(GameObject* game_object) {
  for (std::vector<tbge::GameObject *>::iterator it = Global::getInstance().game_objects_.begin();
       it != Global::getInstance().game_objects_.end(); ++it) {
    if (*it == game_object) {
      Global::getInstance().game_objects_.erase(it);
      break;
    }
  }
}

/**
 * @brief Clears all command word and descriptor aliases.
 * 
 */
void Global::clearAliases() {
  getInstance().command_word_aliases_.clear();
  getInstance().descriptor_aliases_.clear();
}

// Private

}  // namespace global
}  // namespace tbge