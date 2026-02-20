/**
 * @file component_manager.h
 * @brief Manages component types and component data for entities.
 *
 * @details
 * Handles registration of component types, addition/removal of components
 * from entities, and component lifecycle management.
 */

#ifndef TBGE_ECS_COMPONENT_MANAGER_H_
#define TBGE_ECS_COMPONENT_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "src/ecs/component_array/component_array.h"
#include "src/ecs/context/context.h"

namespace ecs {

/**
 * @class ComponentManager
 * @brief Manages registration, storage, and retrieval of components in this ECS
 * (Entity Component System) architecture.
 *
 * @details
 * The ComponentManager is responsible for:
 * - Registering new component types and assigning unique component type IDs.
 * - Adding, removing, and retrieving components for entities.
 * - Managing the lifecycle of components when entities are destroyed.
 * - Providing type-safe access to component arrays.
 */
class ComponentManager {
 public:
  /**
   * @brief Registers a new component type.
   *
   * @note This should only be done once per component type.
   *
   * @tparam T The datatype of the new component type
   * @return Reference to the current ECS::ComponentManager for method chaining.
   */
  template <typename T>
  ComponentManager& RegisterComponentType();

  /**
   * @brief Returns the component type ID for the given component type.
   *
   * @tparam T The datatype of the component type
   * @return The component type ID assigned to this component type.
   */
  template <typename T>
  ComponentTypeId GetComponentTypeId();

  /**
   * @brief Adds a component to the correct ComponentArray based on the type.
   *
   * @tparam T The type deciding which ComponentArray the component should be
   * added to
   * @param entity The Entity ID the component should be associated with
   * @param component The component to be added
   * @return Reference to the current ECS::ComponentManager for method chaining.
   */
  template <typename T>
  ComponentManager& AddComponent(Entity entity, T component);

  /**
   * @brief Removes a component from the correct ComponentArray based on the
   * type.
   *
   * @tparam T The type deciding which ComponentArray the component should be
   * removed from
   * @param entity The Entity ID the component is associated with
   * @return Reference to the current ECS::ComponentManager for method chaining.
   */
  template <typename T>
  ComponentManager& RemoveComponent(Entity entity);

  /**
   * @brief Checks if an entity has a component of the given type.
   *
   * @tparam T The type of the component to check for
   * @param entity The Entity ID to check
   * @return true if the entity has a component of type T; false otherwise.
   */
  template <typename T>
  bool HasComponent(Entity entity);

  /**
   * @brief Returns the component associated with Entity ID
   *
   * @tparam T The type of the component.
   * @param entity The Entity ID of the component that is being retrieved.
   * @return The component of type T
   */
  template <typename T>
  T& GetComponent(Entity entity);

  /**
   * @brief Retrieves the entity associated with a component instance.
   *
   * @tparam T The type of the component.
   * @param component The component instance to search for.
   * @return The Entity ID associated with the component.
   */
  template <typename T>
  Entity GetEntity(T component);

  /**
   * @brief To be called whenever a component has been destroyed.
   *
   * @details
   * Notifies all ComponentArrays that an entity has been destroyed.
   * The ComponentArray that holds that entity will then remove it.
   *
   * @param entity The Entity ID of the component that has been destroyed
   * @return Reference to the current ECS::ComponentManager for method chaining.
   */
  ComponentManager& EntityDestroyed(Entity entity);

  /**
   * @brief Retrieves the mapping of component type names to their corresponding
   * component types.
   *
   * @return An unordered map where the key is a C-string representing the
   * component type name, and the value is the associated component type as
   * defined in the Context.
   */
  const std::unordered_map<const char*, ComponentTypeId>& get_component_types()
      const {
    return component_types_;
  }

  /// @brief Convenience function to get the statically casted pointer to the
  /// ComponentArray of type T.
  template <typename T>
  std::shared_ptr<ComponentArray<T>> get_component_array();

 private:
  /// @brief Map from typename to a component type
  std::unordered_map<const char*, ComponentTypeId> component_types_{};

  /// @brief Map from typename to a component array
  std::unordered_map<const char*, std::shared_ptr<GenericComponentArray>>
      component_arrays_{};

  /// @brief The component type to be assigned to the next registered component
  /// - starting at 0
  ComponentTypeId next_component_type_{};
};

}  // namespace ECS
#endif  // TBGE_ECS_COMPONENT_MANAGER_H_

#include "src/ecs/component_manager/component_manager.tcc"