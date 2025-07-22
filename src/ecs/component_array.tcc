#ifndef TBGE_SRC_ECS_COMPONENT_ARRAY_TCC_
#define TBGE_SRC_ECS_COMPONENT_ARRAY_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <unordered_map>
#include <vector>
#include <iostream>

#include "src/ecs/component_array.h"
#include "src/ecs/definitions.h"

namespace ECS {

template <typename T>
ComponentArray<T>& ComponentArray<T>::InsertData(Entity entity, T component) {
  if (entity_to_index_map_.find(entity) != entity_to_index_map_.end()) {
    LOG(WARNING) << "Component added to same entity more than once.";
    return *this;
  }
  // Put new entry at end and update the maps
  size_t new_index = size_;

  entity_to_index_map_[entity] = new_index;
  index_to_entity_map_[new_index] = entity;
  if (new_index >= component_array_.size()) {
    component_array_.push_back(component);
  } else {
    component_array_.at(new_index) = component;
  }
  ++size_;

  return *this;
}

template <typename T>
ComponentArray<T>& ComponentArray<T>::RemoveData(Entity entity) {
  if (entity_to_index_map_.find(entity) == entity_to_index_map_.end()) {
    LOG(WARNING) << "Removing non-existent component.";
    return *this;
  }

  // Copy element at end into deleted element's place to maintain density
  size_t index_of_removed_entity = entity_to_index_map_[entity];
  size_t index_of_last_element = size_ - 1;
  component_array_.at(index_of_removed_entity) =
      component_array_.at(index_of_last_element);

  // Update map to point to moved spot
  Entity entity_of_last_element = index_to_entity_map_[index_of_last_element];
  entity_to_index_map_[entity_of_last_element] = index_of_removed_entity;
  index_to_entity_map_[index_of_removed_entity] = entity_of_last_element;

  entity_to_index_map_.erase(entity);
  index_to_entity_map_.erase(index_of_last_element);

  --size_;

  return *this;
}

template <typename T>
ComponentArray<T>& ComponentArray<T>::ClearData(Entity entity) {
  for(int i = 0; i < component_array_.size(); ++i) {
    RemoveData(entity);
  }
  return *this;
}

template <typename T>
T& ComponentArray<T>::GetData(Entity entity) {
  CHECK(entity_to_index_map_.find(entity) != entity_to_index_map_.end())
      << "Retrieving non-existent component.";

  // Return a reference to the entity's component
  return component_array_.at(entity_to_index_map_[entity]);
}

template <typename T>
ComponentArray<T>& ComponentArray<T>::EntityDestroyed(Entity entity) {
  if (entity_to_index_map_.find(entity) != entity_to_index_map_.end()) {
    // Remove the entity's component if it existed
    RemoveData(entity);
  }
  return *this;
}
}  // namespace ECS

#endif  // TBGE_SRC_ECS_COMPONENT_ARRAY_TCC_
