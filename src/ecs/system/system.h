/**
 * @file system.h
 * @brief Base class for systems in the Entity Component System.
 *
 * @details
 * Provides the base System class and GenericComponentArray interface that
 * systems inherit from. Systems process entities that match their component
 * requirements.
 */

#ifndef TBGE_ECS_SYSTEM_H_
#define TBGE_ECS_SYSTEM_H_

#include <set>

#include "src/ecs/context/context.h"

namespace tbge::ecs {

/**
 * @class System
 * @brief Base class for systems in the Entity-Component-System (ECS)
 * architecture.
 *
 * @details
 * A System manages a set of entities that match its component requirements.
 * Subclasses can override add_entity() and remove_entity() to respond when
 * entities are added to or removed from the system.
 *
 * The SystemManager automatically maintains the entity set based on entity
 * signatures matching the system's signature requirements.
 */
class System {
 public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes.
   */
  virtual ~System() = default;

  /**
   * @brief Returns the set of entities managed by this system.
   *
   * @return A const reference to the set of entities.
   */
  const std::set<Entity>& get_entities() const { return entities_; }

  /**
   * @brief Checks if the system contains the specified entity.
   *
   * @param entity The entity to check for.
   * @return true if the entity is managed by this system; false otherwise.
   */
  bool has_entity(Entity entity) const { return entities_.count(entity) > 0; }

 protected:
  /**
   * @brief Sets the complete set of entities for this system.
   *
   * @details
   * This is called by the SystemManager to update the system's entity set.
   * Calls remove_entity_() for entities being removed and add_entity_() for
   * entities being added, ensuring child class overloads are invoked.
   *
   * @param entities The new set of entities to manage.
   * @return Reference to this system for method chaining.
   */
  virtual System& set_entities(const std::set<Entity>& entities) {
    // Remove entities no longer in the new set
    for (Entity entity : entities_) {
      if (!entities.contains(entity)) {
        remove_entity_(entity);
      }
    }

    // Add entities in the new set that weren't in the old set
    for (Entity entity : entities) {
      if (!entities_.contains(entity)) {
        add_entity_(entity);
      }
    }

    return *this;
  }

  /**
   * @brief Called when an entity is added to this system.
   *
   * @details
   * Override this method to perform custom logic when an entity enters the
   * system.
   *
   * @param entity The entity that was added.
   * @return Reference to this system for method chaining.
   */
  virtual System& add_entity(Entity entity) { return *this; }

  /**
   * @brief Called when an entity is removed from this system.
   *
   * @details
   * Override this method to perform custom logic when an entity leaves the
   * system.
   *
   * @param entity The entity that was removed.
   * @return Reference to this system for method chaining.
   */
  virtual System& remove_entity(Entity entity) { return *this; }

 private:
  friend class SystemManager;

  /// @brief The set of entities managed by this system.
  std::set<Entity> entities_;

  System& add_entity_(Entity entity) {
    if (!entities_.contains(entity)) {
      entities_.insert(entity);
      add_entity(entity);
    }
    return *this;
  }

  System& remove_entity_(Entity entity) {
    if (entities_.contains(entity)) {
      entities_.erase(entity);
      remove_entity(entity);
    }
    return *this;
  }
};

}  // namespace tbge::ecs

#endif  // TBGE_ECS_SYSTEM_H_