/**
 * @file component.h
 * @brief Base class for ECS components.
 *
 * @details
 * Provides an optional base class for components that need access to their
 * owning entity's ID. Components inheriting from this class will have their
 * entity_id_ automatically populated when added to an entity.
 */

#ifndef TBGE_ECS_COMPONENT_H_
#define TBGE_ECS_COMPONENT_H_

#include "src/ecs/context/context.h"

namespace ecs {

// Forward declaration
class Coordinator;

/**
 * @brief Optional base class for ECS components.
 *
 * @details
 * Components can optionally inherit from this class to have their associated
 * Entity ID automatically maintained. When a component is added to an entity
 * via the Coordinator, the entity_id_ field will be automatically populated
 * by calling SetEntityId().
 *
 * @note This class is purely optional. Components do not need to inherit
 * from this class to work with the ECS, but inheriting provides convenient
 * access to the owning entity's ID.
 */
class Component {
 public:
  friend class Coordinator;
  /**
   * @brief Default constructor.
   */
  Component() = default;

  /**
   * @brief Virtual destructor.
   */
  virtual ~Component() = default;

  /**
   * @brief Gets the Entity ID this component is associated with.
   *
   * @return The Entity ID, or -1 if not yet assigned to an entity.
   */
  const Entity get_entity_id() const { return entity_id_; }

 protected:
  /**
   * @brief Sets the Entity ID this component is associated with.
   *
   * @details
   * This is automatically called by the Coordinator when the component
   * is added to an entity.
   *
   * @param entity_id The Entity ID to associate with this component.
   */
  void set_entity_id(Entity entity_id) { entity_id_ = entity_id; }

 private:
  /// @brief The Entity ID this component is associated with.
  Entity entity_id_ = static_cast<Entity>(-1);
};

}  // namespace ecs

#endif  // TBGE_ECS_COMPONENT_H_
