/**
 * @file system_manager.h
 * @brief Manages system registration, signatures, and entity notifications.
 *
 * @details
 * Handles registration of systems, assignment of component signatures to
 * systems, and notification of systems when entities are created, destroyed,
 * or their signatures change.
 */

#ifndef TBGE_ECS_SYSTEM_MANAGER_H_
#define TBGE_ECS_SYSTEM_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "src/ecs/context/context.h"
#include "src/ecs/system/system.h"

namespace ECS {

/**
 * @class SystemManager
 * @brief Manages the registration and signature assignment of systems in
 * this ECS (Entity Component System) architecture.
 *
 * @details
 * The SystemManager is responsible for:
 * - Registering new systems and associating them with unique type identifiers.
 * - Assigning and tracking signatures for each system, which define the set of
 * components a system is interested in.
 * - Notifying systems when entities are destroyed or when their signatures
 * change, allowing systems to update their internal entity lists accordingly.
 *
 * @note This class is a core part of this Entity-Component-System (ECS)
 * architecture.
 */
class SystemManager {
 public:
  /**
   * @brief Virtual destructor for proper cleanup.
   */
  virtual ~SystemManager() = default;

  /**
   * @brief Registers a new system of type T and returns a shared pointer to it.
   *
   * This function creates and registers a system of the specified type T within
   * the system manager.
   *
   * @tparam T The type of the system to register. Must inherit from the base
   * System class.
   * @return std::shared_ptr<T> A shared pointer to the registered system
   * instance.
   *
   * @note
   * Asserts that a system of the given type has not already been registered.
   */
  template <typename T>
  std::shared_ptr<T> RegisterSystem();

  /**
   * @brief Sets the signature for the system.
   *
   * This method assigns a specific signature to the system, which determines
   * the set of component types that the system will operate on.
   *
   * @param signature The signature to associate with the system.
   * @return Reference to the current SystemManager instance for method
   * chaining.
   *
   * @note
   * Asserts that the system has been registered before being given a signature.
   */
  template <typename T>
  SystemManager& SetSignature(Signature signature);

  /**
   * @brief Gets the signature for a system of type T.
   *
   * @tparam T The type of the system.
   * @return The signature associated with the system type.
   *
   * @note
   * Asserts that the system has been registered.
   */
  template <typename T>
  Signature GetSignature();

  /**
   * @brief Notifies all Systems that an entity has been destroyed.
   *
   * This function should be called whenever an entity is removed from the ECS.
   * It ensures that all systems are updated accordingly and any references to
   * the destroyed entity are cleaned up.
   *
   * @param entity The entity that has been destroyed.
   * @return Reference to the current SystemManager instance for method
   * chaining.
   */
  SystemManager& EntityDestroyed(Entity entity);

  /**
   * @brief Notifies the SystemManager that an entity's signature has changed.
   *
   * This function should be called whenever an entity's component signature is
   * updated. It allows the SystemManager to update its internal tracking of
   * which systems should process the entity based on the new signature.
   *
   * @param entity The entity whose signature has changed.
   * @param entitySignature The new signature representing the entity's
   * components.
   * @return Reference to the current SystemManager instance for method
   * chaining.
   */
  SystemManager& EntitySignatureChanged(Entity entity,
                                        Signature entitySignature);

  template <typename T>
  std::shared_ptr<T> GetSystem();

  /**
   * @brief Returns the map of system signatures.
   *
   * @return A const reference to the map from system type names to signatures.
   */
  const std::unordered_map<const char*, Signature>& get_signatures() const {
    return signatures_;
  }

  /**
   * @brief Returns the map of registered systems.
   *
   * @return A const reference to the map from system type names to system
   * pointers.
   */
  const std::unordered_map<const char*, std::shared_ptr<System>>& get_systems()
      const {
    return systems_;
  }

 private:
  /// @brief Map from system type string pointer to a signature
  std::unordered_map<const char*, Signature> signatures_{};

  /// @brief Map from system type string pointer to a system pointer
  std::unordered_map<const char*, std::shared_ptr<System>> systems_{};
};

}  // namespace ECS

#endif  // TBGE_ECS_SYSTEM_MANAGER_H_

#include "src/ecs/system_manager/system_manager.tcc"
