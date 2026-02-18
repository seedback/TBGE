#ifndef TBGE_SRC_ECS_COORDINATOR_TCC_
#define TBGE_SRC_ECS_COORDINATOR_TCC_

#include <iostream>
#include <type_traits>

#include "src/ecs/component/component.h"
#include "src/ecs/component_manager/component_manager.h"
#include "src/ecs/context/context.h"
#include "src/ecs/coordinator/coordinator.h"
#include "src/ecs/entity_manager/entity_manager.h"
#include "src/ecs/system_manager/system_manager.h"

namespace ECS {
// #####   Component methods   #####
template <typename T>
Coordinator& Coordinator::RegisterComponentType() {
  component_manager_->template RegisterComponentType<T>();

  return *this;
}

template <typename T>
Coordinator& Coordinator::AddComponent(
    Entity entity, T component) {
  // If the component inherits from Component, set its entity ID
  if constexpr (std::is_base_of_v<Component, T>) {
    component.SetEntityId(entity);
  }

  component_manager_->template AddComponent<T>(entity, component);

  Signature signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->template GetComponentTypeId<T>(), true);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename T>
Coordinator& Coordinator::RemoveComponent(
    Entity entity) {
  component_manager_->template RemoveComponent<T>(entity);

  // Grabbing the signature of the entity, resetting the bit corresponding to
  // the component, and setting the signature of the entity to the new one.
  Signature signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->template GetComponentTypeId<T>(), false);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename T>
T& Coordinator::GetComponent(Entity entity) {
  return component_manager_->template GetComponent<T>(entity);
}

template <typename T>
ComponentTypeId Coordinator::GetComponentTypeId() {
  return component_manager_->template GetComponentTypeId<T>();
}

// #####   System methods   #####
template <typename T>
std::shared_ptr<T> Coordinator::RegisterSystem() {
  return system_manager_->template RegisterSystem<T>();
}

template <typename T>
std::shared_ptr<T> Coordinator::GetSystem() {
  return system_manager_->template GetSystem<T>();
}

template <typename T>
Coordinator& Coordinator::SetSystemSignature(
    Signature signature) {
  system_manager_->template SetSignature<T>(signature);
  return *this;
}

template <typename T>
Signature Coordinator::GetSystemSignature() {
  return system_manager_->template GetSignature<T>();
}

template <typename T>
bool Coordinator::EntityIsValidForSystem(Entity entity) {
  auto system_signature = GetSystemSignature<T>();
  auto entity_signature = GetEntitySignature(entity);
  return (system_signature & entity_signature) == system_signature;
}

}  // namespace ECS
#endif  // TBGE_SRC_ECS_COORDINATOR_TCC_