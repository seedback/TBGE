/*
 * _____________________________
 *    _____ ____   ____ _____
 *   |_   _| __ ) / ___| ____|
 *     | | |  _ \| |  _|  _|
 *     | | | |_) | |_| | |___
 *     |_| |____/ \____|_____|
 * _____________________________
 */

// Defines the global singleton holding global data, like master lists for all
//   object types as well as command-word-aliases.

#pragma once
#include <string>
#include <vector>

#include "include\game_object\game_object.h"

namespace tbge {
class GameObject;
}

namespace tbge {
namespace global {

class GlobalSingleton {
 public:
  /**
   * @brief Get the instance of the GlobalSingleton.@n
   *        This allways returns the same instance of GlobalSingleton so only
   *        one instance of this class can ever exist.
   *
   * @return @a The instance of GlobalSingleton.@n
   *         (there can only ever be one)
   */
  static GlobalSingleton& get_instance() {
    static GlobalSingleton instance;  // Guaranteed to be destroyed.
                                      // Instantiated on first use.
    return instance;
  }

  /// @brief Deleted to avoid having multiple instances of the
  /// GlobalSingleton.
  GlobalSingleton(GlobalSingleton const&) = delete;

  /// @brief Deleted to avoid having multiple instances of the
  /// GlobalSingleton.
  void operator=(GlobalSingleton const&) = delete;
  // Note: Scott Meyers mentions in his Effective Modern
  //       C++ book, that deleted functions should generally
  //       be public as it results in better error messages
  //       due to the compilers behavior to check accessibility
  //       before deleted status

  /**
   * @brief Registers a game object to the master-list.
   * @param @a game_object A pointer to the GameObject to be deleted.
   * @return The instance of GlobalSingleton to allow method-chaining.
   */
  GlobalSingleton& register_game_object(GameObject* game_object);

  /**
   * @brief Unregisters the game object pointed to from the master-list.
   * @param @a game_object The GameObject to be unregistered.
   * @return The instance of GlobalSingleton to allow method-chaining.
   */
  GlobalSingleton& unregister_game_object(GameObject* game_object);

  /**
   * @brief Unregisters a game object from the master-list based on its id.
   * @param @a id The full name of the object to be unregistered.
   * @return The instance of GlobalSingleton to allow method-chaining.
   */
  GlobalSingleton& unregister_game_object_by_id(int id);

  /**
   * @brief Unregisters a game object from the master-list based on its name.
   * @param @a name The full name of the object to be unregistered.
   * @return The instance of GlobalSingleton to allow method-chaining.
   */
  GlobalSingleton& unregister_game_object_by_name(std::string name);

  /**
   * @brief Unregisters a game object from the master-list based on its full
   * name.
   * @param full_name The full name of the object to be unregistered.
   * @return The instance of GlobalSingleton to allow method-chaining.
   */
  GlobalSingleton& unregister_game_object_by_full_name(std::string full_name);

 private:
  /// @brief Private constructor to avoid multiple objects of GlobalSingleton.
  GlobalSingleton() {}

  /// @brief Private destructor to ensure the object is only ever destroyed at
  ///        program termination.
  ~GlobalSingleton() {}

  std::vector<GameObject*> game_objects_;
};

extern GlobalSingleton& global;

}  // namespace global
}  // namespace tbge