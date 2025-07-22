#ifndef TBGE_SRC_ECS_ENTITY_MANAGER_H_
#define TBGE_SRC_ECS_ENTITY_MANAGER_H_

#include <queue>
#include <vector>

#include "src/ecs/definitions.h"

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
 * @note The maximum number of entities is limited by kMaxEntities.
 * @note Entity IDs are recycled after destruction.
 *
 * @see kMaxEntities
 */
class EntityManager {
 public:
  /**
   * @brief Constructs an EntityManager and initializes the pool of available
   * entity IDs.
   *
   * @details
   * This constructor fills the queue of available entities with all possible
   * entity IDs, ranging from 0 to kMaxEntities - 1. This allows for efficient
   * allocation and recycling of entity IDs during the lifetime of the
   * EntityManager.
   */
  EntityManager();

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
  Entity CreateEntity();

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
  EntityManager& DestroyEntity(Entity entity);

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
  EntityManager& SetSignature(Entity entity, Signature signature);

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
  Signature GetSignature(Entity entity);

 private:
  /// Queue of unused entity IDs
  std::queue<Entity> available_entities_{};

  /// Array of signatures where the index corresponds to the entity ID
  std::vector<Signature> signatures_{};

  /// Total living entities - used to keep limits on how many exist
  Entity current_entity_count_ = 0;
};
}  // namespace ECS

#endif  // TBGE_SRC_ECS_ENTITY_MANAGER_H_