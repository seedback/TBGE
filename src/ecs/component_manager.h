#ifndef TBGE_SRC_ECS_COMPONENT_MANAGER_H_
#define TBGE_SRC_ECS_COMPONENT_MANAGER_H_

#include <memory>
#include <unordered_map>

#include "src/ecs/component_array.h"
#include "src/ecs/context.h"

namespace ECS {

/**
 * @class ComponentManager
 * @brief Manages registration, storage, and retrieval of components in this ECS
 * (Entity Component System) architecture.
 * 
 * @tparam Context The Context that holds configuration data and data types.
 *
 * @details
 * The ComponentManager is responsible for:
 * - Registering new component types and assigning unique component type IDs.
 * - Adding, removing, and retrieving components for entities.
 * - Managing the lifecycle of components when entities are destroyed.
 * - Providing type-safe access to component arrays.
 */
template <typename Context = ECS::Context<>>
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
  ComponentManager<Context>& RegisterComponentType();

  /**
   * @brief Returns the component's type. This is used for creating signatures.
   *
   * @tparam T The datatype of the component type
   * @return Reference to the current ECS::ComponentManager for method chaining.
   */
  template <typename T>
  Context::ComponentType GetComponentType();

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
  ComponentManager<Context>& AddComponent(Context::Entity entity, T component);

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
  ComponentManager<Context>& RemoveComponent(Context::Entity entity);

  /**
   * @brief Returns the component associated with Entity ID
   *
   * @tparam T The type of the component.
   * @param entity The Entity ID of the component that is being retrieved.
   * @return The component of type T
   */
  template <typename T>
  T& GetComponent(Context::Entity entity);

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
  ComponentManager<Context>& EntityDestroyed(Context::Entity entity);

 private:
  /// @brief Map from type string pointer to a component type
  std::unordered_map<const char*, typename Context::ComponentType>
      component_types_{};

  /// @brief Map from type string pointer to a component array
  std::unordered_map<const char*,
                     std::shared_ptr<GenericComponentArray<Context>>>
      component_arrays_{};

  /// @brief The component type to be assigned to the next registered component
  /// - starting at 0
  Context::ComponentType next_component_type_{};

  /// @brief Convenience function to get the statically casted pointer to the
  /// ComponentArray of type T.
  template <typename T>
  std::shared_ptr<ComponentArray<Context, T>> GetComponentArray();
};

}  // namespace ECS

#include "src/ecs/component_manager.tcc"
#endif  // TBGE_SRC_ECS_COMPONENT_MANAGER_H_