#ifndef TBGE_SRC_ECS_COMPONENT_MANAGER_TCC_
#define TBGE_SRC_ECS_COMPONENT_MANAGER_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "src/ecs/component_array.h"
#include "src/ecs/component_manager.h"
#include "src/ecs/context.h"

namespace ECS {

template <typename Context>
template <typename T>
ComponentManager<Context>& ComponentManager<Context>::RegisterComponentType() {
  const char* type_name = typeid(T).name();

  if (component_types_.find(type_name) != component_types_.end()) {
    LOG(WARNING) << "Registering component type more than once.";
    return *this;
  }

  // Add this component type to the component type map
  component_types_.insert({type_name, next_component_type_});

  // Create a ComponentArray pointer and add it to the component arrays map
  component_arrays_.insert(
      {type_name, std::make_shared<ComponentArray<Context, T>>()});

  // Increment the value so that the next component registered will be different
  ++next_component_type_;

  return *this;
}

template <typename Context>
template <typename T>
typename Context::ComponentType ComponentManager<Context>::GetComponentType() {
  const char* type_name = typeid(T).name();

  CHECK(component_types_.find(type_name) == component_types_.end())
      << "Component not registered before use.";

  // Return this component's type - used for creating signatures
  return component_types_[type_name];
}

template <typename Context>
template <typename T>
ComponentManager<Context>& ComponentManager<Context>::AddComponent(
    Context::Entity entity, T component) {
  // Add a component to the array for an entity
  GetComponentArray<T>()->InsertData(entity, component);

  return *this;
}

template <typename Context>
template <typename T>
ComponentManager<Context>& ComponentManager<Context>::RemoveComponent(
    Context::Entity entity) {
  // Remove a component from the array for an entity
  GetComponentArray<T>()->RemoveData(entity);

  return *this;
}

template <typename Context>
template <typename T>
T& ComponentManager<Context>::GetComponent(Context::Entity entity) {
  // Get a reference to a component from the array for an entity
  return GetComponentArray<T>()->GetData(entity);
}

template <typename Context>
ComponentManager<Context>& ComponentManager<Context>::EntityDestroyed(
    Context::Entity entity) {
  // Notify each component array that an entity has been destroyed
  // If it has a component for that entity, it will remove it
  for (auto const& [type_name, component] : component_arrays_) {
    component->EntityDestroyed(entity);
  }

  return *this;
}

// #########################
// #        PRIVATE        #
// #########################
template <typename Context>
template <typename T>
std::shared_ptr<ComponentArray<Context, T>>
ComponentManager<Context>::GetComponentArray() {
  const char* type_name = typeid(T).name();

  CHECK(component_types_.find(type_name) == component_types_.end())
      << "Component not registered before use.";

  return std::static_pointer_cast<ComponentArray<Context, T>>(
      component_arrays_[type_name]);
}

}  // namespace ECS

#endif  // TBGE_SRC_ECS_COMPONENT_MANAGER_TCC_