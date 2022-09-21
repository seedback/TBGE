/*
 * _____________________________
 *    _____ ____   ____ _____
 *   |_   _| __ ) / ___| ____|
 *     | | |  _ \| |  _|  _|
 *     | | | |_) | |_| | |___
 *     |_| |____/ \____|_____|
 * _____________________________
 */

// Implements GlobalSingleton

#include "include\global\global_singleton.h";
#include "include\game_object\game_object.h"

namespace tbge {
namespace global {

GlobalSingleton& global = GlobalSingleton::get_instance();

GlobalSingleton& GlobalSingleton::register_game_object(
    GameObject* game_object) {
  game_objects_.push_back(game_object);
  return get_instance();
}

GlobalSingleton& GlobalSingleton::unregister_game_object(
    GameObject* game_object) {
  for (int i = 0; i < game_objects_.size(); i++) {
    if (game_objects_.at(i) == game_object) {
      game_objects_.erase(game_objects_.begin() + i);
      break;
    }
  }
  return GlobalSingleton::get_instance();
}

GlobalSingleton& GlobalSingleton::unregister_game_object_by_id(int id) {
  for (int i = 0; i < game_objects_.size(); i++) {
    if (game_objects_.at(i)->get_id() == id) {
      game_objects_.erase(game_objects_.begin() + i);
      break;
    }
  }
  return GlobalSingleton::get_instance();
}

GlobalSingleton& GlobalSingleton::unregister_game_object_by_name(
    std::string name) {
  for (int i = 0; i < game_objects_.size(); i++) {
    if (game_objects_.at(i)->get_name() == name) {
      game_objects_.erase(game_objects_.begin() + i);
      break;
    }
  }
  return GlobalSingleton::get_instance();
}

GlobalSingleton& GlobalSingleton::unregister_game_object_by_full_name(
    std::string full_name) {
  for (int i = 0; i < game_objects_.size(); i++) {
    if (game_objects_.at(i)->get_full_name() == full_name) {
      game_objects_.erase(game_objects_.begin() + i);
      break;
    }
  }
  return GlobalSingleton::get_instance();
}
}  // namespace global
}  // namespace tbge
