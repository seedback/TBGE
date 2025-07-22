#ifndef TBGE_SRC_ECS_COMPONENT_ARRAY_H_
#define TBGE_SRC_ECS_COMPONENT_ARRAY_H_

#include <unordered_map>
#include <vector>

#include "src/ecs/definitions.h"

namespace ECS {
class GenericComponentArray {
 public:
  virtual ~GenericComponentArray() = default;
  virtual GenericComponentArray& EntityDestroyed(Entity entity) = 0;
};

/**
 * @class ComponentArray
 * @brief Stores and manages a packed array of components of type T for an ECS
 * (Entity Component System).
 *
 * @details
 * This class provides efficient insertion, removal, and retrieval of components
 * associated with entities. It maintains a packed array of components and maps
 * between entities and their corresponding indices in the array.
 *
 * @tparam T The type of component stored in the array.
 *
 * @note Inherits from GenericComponentArray to allow for storage of all
 * ComponentArrays in a single list.
 */
template <typename T>
class ComponentArray : public GenericComponentArray {
 public:
  /**
   * @brief Inserts a component into the ::component_array_.
   *
   * @details
   * Adds the given component to the ::component_array_, associating the entity
   * with its index in the two maps ::entity_to_index_map_ and
   * ::index_to_entity_map_.
   *
   * @param entity The ::Entity ID representing the component.
   * @param component The component instance to insert.
   * @return Reference to the current ECS::ComponentArray for method chaining.
   */
  ComponentArray& InsertData(Entity entity, T component);

  /**
   * @brief Removes a component from the ::component_array_.
   *
   * @details
   * Removes the component associated with the given ::Entity ID from the
   * ::component_array, ensuring it stays packed, and cleans up the two maps
   * ::entity_to_index_map_ and ::index_to_entity_map_.
   *
   * @param entity The ::Entity ID to remove from the ::component_array_.
   * @return Reference to the current ECS::ComponentArray for method chaining.
   */
  ComponentArray& RemoveData(Entity entity);

  ComponentArray& ClearData(Entity entity);

  /**
   * @brief Returns the component associated with the ::Entity ID.
   *
   * @param entity The ::Entity ID to which the component is associated.
   * @return The component.
   */
  T& GetData(Entity entity);

  /**
   * @brief Called when a component has been destroyed and its data needs to be
   * cleaned up.
   *
   * @param entity The ::Entity ID that has been destroyed.
   * @return Reference to the current ECS::ComponentArray for method chaining.
   */
  ComponentArray& EntityDestroyed(Entity entity) override;

 private:
  /// @brief The packed array of components (of generic type T),
  std::vector<T> component_array_;

  /// @brief Map from an entity ID to an array index.
  std::unordered_map<Entity, size_t> entity_to_index_map_;

  /// @brief Map from an array index to an entity ID.
  std::unordered_map<size_t, Entity> index_to_entity_map_;

  /// @brief Total size of valid entries in the array.
  size_t size_ = 0;
};

}  // namespace ECS

#include "src/ecs/component_array.tcc"
#endif  // TBGE_SRC_ECS_COMPONENT_ARRAY_H_