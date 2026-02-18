#ifndef TBGE_SRC_ECS_COMPONENT_H_
#define TBGE_SRC_ECS_COMPONENT_H_

#include "src/ecs/context/context.h"

namespace ECS {

/**
 * @brief Optional base class for ECS components.
 *
 * @details
 * Components can optionally inherit from this class to automatically track
 * the Entity ID they are associated with. When a component is added to an
 * entity via the Coordinator, the entity_id_ field will be automatically
 * populated.
 *
 * @note This class is purely optional. Components do not need to inherit
 * from this class to work with the ECS, but inheriting provides convenient
 * access to the owning entity's ID.
 */
class Component {
 public:
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
  Entity get_entity_id() const { return entity_id_; }

  /**
   * @brief Sets the Entity ID this component is associated with.
   *
   * @details
   * This is automatically called by the Coordinator when the component
   * is added to an entity.
   *
   * @param entity_id The Entity ID to associate with this component.
   */
  void SetEntityId(Entity entity_id) {
    entity_id_ = entity_id;
  }

 protected:
  /// @brief The Entity ID this component is associated with.
  Entity entity_id_ = static_cast<Entity>(-1);
};

}  // namespace ECS

#endif  // TBGE_SRC_ECS_COMPONENT_H_
