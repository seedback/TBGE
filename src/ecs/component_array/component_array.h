#ifndef TBGE_SRC_ECS_COMPONENT_ARRAY_H_
#define TBGE_SRC_ECS_COMPONENT_ARRAY_H_

#include <optional>
#include <unordered_map>
#include <vector>

#include "src/ecs/context/context.h"

namespace ECS {

/**
 * @brief Abstract base class for component arrays in an ECS.
 *
 * @details
 * Provides an interface for component arrays, allowing for polymorphic
 * storage and destruction notification when entities are destroyed.
 */
class GenericComponentArray {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~GenericComponentArray() = default;

  /**
   * @brief Notifies the array that an entity has been destroyed.
   *
   * @details
   * Called when an entity is destroyed so that any associated component data
   * can be cleaned up.
   *
   * @param entity The entity that has been destroyed.
   * @return Reference to the current GenericComponentArray for method chaining.
   */
  virtual GenericComponentArray& EntityDestroyed(Entity entity) = 0;
};

/**
 * @brief Stores and manages a packed array of components of type T for an ECS.
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
   * @brief Inserts a component into the component_array_.
   *
   * @details
   * Adds the given component to the component_array_, associating the entity
   * with its index in the entity_to_index_map_ and index_to_entity_map_.
   *
   * @param entity The entity ID representing the component.
   * @param component The component instance to insert.
   * @return Reference to the current ComponentArray for method chaining.
   */
  ComponentArray& InsertData(Entity entity, T component);

  /**
   * @brief Removes a component from the component_array_.
   *
   * @details
   * Removes the component associated with the given entity ID from the
   * component_array_, ensuring it stays packed, and cleans up the
   * entity_to_index_map_ and index_to_entity_map_.
   *
   * @param entity The entity ID to remove from the component_array_.
   * @return Reference to the current ComponentArray for method chaining.
   */
  ComponentArray& RemoveData(Entity entity);

  /**
   * @brief Checks whether the specified entity has associated component data.
   *
   * @param entity The entity to check for associated component data.
   * @return true if the entity has component data; false otherwise.
   */
  bool HasData(Entity entity);

  /**
   * @brief Returns the component associated with the entity ID.
   *
   * @param entity The entity ID to which the component is associated.
   * @return An optional containing the component if found, otherwise
   * std::nullopt.
   */
  T& GetData(Entity entity);

  /**
   * @brief Called when an entity has been destroyed and its data needs to be
   * cleaned up.
   *
   * @param entity The entity ID that has been destroyed.
   * @return Reference to the current ComponentArray for method chaining.
   */
  ComponentArray& EntityDestroyed(Entity entity) override;

  /**
   * @brief Returns the number of valid entries in the array.
   *
   * @return The size of the component array.
   */
  size_t get_size() { return size_; }

 private:
  /// @brief The packed array of components (of generic type T).
  std::vector<T> component_array_;

  /// @brief Map from an entity ID to an array index.
  std::unordered_map<Entity, size_t> entity_to_index_map_;

  /// @brief Map from an array index to an entity ID.
  std::unordered_map<size_t, Entity> index_to_entity_map_;

  /// @brief Total size of valid entries in the array.
  size_t size_ = 0;
};

}  // namespace ECS

#endif  // TBGE_SRC_ECS_COMPONENT_ARRAY_H_

#include "src/ecs/component_array/component_array.tcc"