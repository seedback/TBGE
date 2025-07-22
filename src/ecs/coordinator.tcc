#ifndef TBGE_SRC_ECS_COORDINATOR_TCC_
#define TBGE_SRC_ECS_COORDINATOR_TCC_

#include "src/ecs/coordinator.h"

namespace ECS
{
// #####   Component methods   #####
template <typename T>
Coordinator& Coordinator::RegisterComponentType() {
  component_manager_->RegisterComponentType<T>();

  return *this;
}

template <typename T>
Coordinator& Coordinator::AddComponent(Entity entity, T component) {
  component_manager_->AddComponent<T>(entity, component);

  auto signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->GetComponentType<T>(), true);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename T>
Coordinator& Coordinator::RemoveComponent(Entity entity) {
  component_manager_->RemoveComponent<T>(entity);

  auto signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->GetComponentType<T>(), false);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename T>
T& Coordinator::GetComponent(Entity entity) {
  return component_manager_->GetComponent<T>(entity);
}

template <typename T>
ComponentType Coordinator::GetComponentType() {
  return component_manager_->GetComponentType<T>();
}

// #####   System methods   #####
template <typename T>
std::shared_ptr<T> Coordinator::RegisterSystem() {
  return system_manager_->RegisterSystem<T>();
}

template <typename T>
Coordinator& Coordinator::SetSystemSignature(Signature signature) {
  system_manager_->SetSignature<T>(signature);

  return *this;
}
} // namespace ECS
#endif  // TBGE_SRC_ECS_COORDINATOR_TCC_