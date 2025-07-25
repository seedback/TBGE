#ifndef TBGE_SRC_ECS_ENTITY_MANAGER_H_
#define TBGE_SRC_ECS_ENTITY_MANAGER_H_

#include <queue>
#include <vector>

#include "src/ecs/context.h"

namespace ECS {
/**
 * @class EntityManager
 * @brief Manages creation, destruction, and signature assignment of entities in
 * this ECS (Entity Component System) architecture.
 *
 * @details
 * The EntityManager is responsible for:
 * - Allocating and recycling unique entity IDs.
 * - Tracking the number of active entities.
 * - Managing entity signatures, which represent the set of components
 * associated with each entity.
 *
 * Usage:
 * - Use CreateEntity() to obtain a new entity ID.
 * - Use DestroyEntity() to remove an entity and recycle its ID.
 * - Use SetSignature() and GetSignature() to manage the component signature of
 * an entity.
 * 
 * @tparam Context The Context that holds configuration data and data types.
 *
 * @tparam Context The Context that holds configuration data and data types.
 *
 * @note The maximum number of entities is limited by kMaxEntities.
 * @note Entity IDs are recycled after destruction.
 *
 * @see kMaxEntities
 */
template <typename Context = Context<>>
class EntityManager {
 public:
  EntityManager() {
    current_entity_count_ = 0;
    signatures_.clear();
    while (!available_entities_.empty()) {
      available_entities_.pop();
    }
  }
  /**
   * @brief Creates a new entity and returns its unique identifier.
   *
   * @details
   * It retrieves an available entity ID from the front of the queue, increments
   * the current entity count, and returns the new entity ID.
   *
   * @return Entity The unique identifier for the newly created entity.
   * @throws Assertion failure if the maximum number of entities is exceeded.
   *
   * @note Asserts that the maximum number of entities has not been exceeded.
   */
  Context::Entity CreateEntity();

  /**
   * @brief Destroys the specified entity and recycles its ID.
   *
   * @details
   * This function invalidates the signature of the given entity, effectively
   * removing all of its associated components. The entity's ID is then placed
   * back into the pool of available entities for future reuse. The total count
   * of active entities is decremented accordingly.
   *
   * @param entity The entity to be destroyed. Must be within the valid range.
   * @return Reference to the current EntityManager instance for method
   * chaining.
   *
   * @note Asserts that the entity is within the valid range.
   */
  EntityManager<Context>& DestroyEntity(Context::Entity entity);

  /**
   * @brief Checks if the specified entity exists in the manager.
   *
   * @note This operation gets really expensive the more destroyed entities
   * exist that has not yet been reused as it bases itself on which entities are
   * currently in the available_entities_ queue, and as such has to go through
   * the whole queue to verify if it is in use or not.
   * This is mostly meant to be a debug tool.
   *
   * @param entity The entity to check for existence.
   * @return true if the entity exists, false otherwise.
   */
  bool HasEntity(Context::Entity entity);

  /**
   * @brief Sets the signature for a given entity.
   *
   * @details
   * Associates the specified signature with the provided entity in the internal
   * signature array.
   *
   * @param entity The entity whose signature is to be set.
   * @param signature The signature to associate with the entity.
   * @return Reference to the current EntityManager instance for method
   * chaining.
   *
   * @note Asserts that the entity is within the valid range.
   */
  EntityManager<Context>& SetSignature(Context::Entity entity,
                                       Context::Signature signature);

  /**
   * @brief Retrieves the signature associated with a given entity.
   *
   * This function returns the signature for the specified entity, which
   * represents the set of components that the entity possesses.
   *
   * @param entity The entity whose signature is to be retrieved.
   * @return Signature The signature corresponding to the given entity.
   * @throws Assertion failure if the entity is out of range.
   *
   * @note Asserts that the entity identifier is within the valid range.
   */
  Context::Signature GetSignature(Context::Entity entity);

  Context::Entity get_current_entity_count() { return current_entity_count_; }
  Context::Entity get_entity_id_counter() { return entity_id_counter_; }

 private:
  /// Queue of unused entity IDs
  std::queue<typename Context::Entity> available_entities_{};

  /// Array of signatures where the index corresponds to the entity ID
  std::vector<typename Context::Signature> signatures_{};

  /// Total living entities - used to keep limits on how many exist
  Context::Entity current_entity_count_ = 0;

  /// Keeps track of the next Entity ID to be used when creating a new one.
  Context::Entity entity_id_counter_ = 0;
};
}  // namespace ECS

#include "src/ecs/entity_manager.tcc"

#endif  // TBGE_SRC_ECS_ENTITY_MANAGER_H_