#ifndef TBGE_ECS_COMPONENT_MANAGER_TCC_
#define TBGE_ECS_COMPONENT_MANAGER_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "src/ecs/component_array/component_array.h"
#include "src/ecs/component_manager/component_manager.h"
#include "src/ecs/context/context.h"

namespace ECS {

template <typename T>
ComponentManager& ComponentManager::RegisterComponentType() {
  const char* type_name = typeid(T).name();

  if (component_types_.find(type_name) != component_types_.end()) {
    LOG(WARNING) << "Registering component type more than once. Component type "
                    "registered twice has typeid \""
                 << type_name << "\". Operation ignored.";
    return *this;
  }

  // Add this component type to the component type map
  component_types_.insert({type_name, next_component_type_});

  // Create a ComponentArray pointer and add it to the component arrays map
  component_arrays_.insert({type_name, std::make_shared<ComponentArray<T>>()});

  // Increment the value so that the next component registered will be different
  ++next_component_type_;

  return *this;
}

template <typename T>
ComponentTypeId ComponentManager::GetComponentTypeId() {
  const char* type_name = typeid(T).name();

  CHECK(component_types_.find(type_name) != component_types_.end())
      << "Component of type " << type_name << " not registered before use.";

  // Return this component's type - used for creating signatures
  return component_types_[type_name];
}

template <typename T>
ComponentManager& ComponentManager::AddComponent(Entity entity, T component) {
  // Add a component to the array for an entity
  get_component_array<T>()->InsertData(entity, component);

  return *this;
}

template <typename T>
ComponentManager& ComponentManager::RemoveComponent(Entity entity) {
  // Remove a component from the array for an entity
  get_component_array<T>()->RemoveData(entity);

  return *this;
}

template <typename T>
bool ComponentManager::HasComponent(Entity entity) {
  return get_component_array<T>()->HasData(entity);
}

template <typename T>
T& ComponentManager::GetComponent(Entity entity) {
  // Get a reference to a component from the array for an entity
  return get_component_array<T>()->GetData(entity);
}

// #########################
// #        PRIVATE        #
// #########################
template <typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::get_component_array() {
  const char* type_name = typeid(T).name();

  if (component_types_.find(type_name) == component_types_.end()) {
    LOG(WARNING) << "Component with typename \"" << std::string(type_name)
                 << "\" not registered before access. Registering now.";
    RegisterComponentType<T>();
  }

  return std::static_pointer_cast<ComponentArray<T>>(
      component_arrays_[type_name]);
}

}  // namespace ECS

#endif  // TBGE_ECS_COMPONENT_MANAGER_TCC_