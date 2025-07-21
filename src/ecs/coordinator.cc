#include "src/ecs/coordinator.h"

#include <iostream>

#include "src/ecs/component_manager.h"
#include "src/ecs/definitions.h"
#include "src/ecs/entity_manager.h"
#include "src/ecs/system_manager.h"

namespace ECS {

// #####   Entity methods   #####
Entity Coordinator::CreateEntity() { return entity_manager_->CreateEntity(); }

Coordinator& Coordinator::DestroyEntity(Entity entity) {
  entity_manager_->DestroyEntity(entity);

  component_manager_->EntityDestroyed(entity);

  system_manager_->EntityDestroyed(entity);

  return *this;
}

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

// #####   Private methods   #####
Coordinator& Coordinator::Init() {
// Write a warning message when in debug mode about the limitations of the
// system and how to configure it
#ifdef _DEBUG
  this->debug_warning();
#endif

  // Create pointers to each manager
  component_manager_ = std::make_unique<ComponentManager>();
  entity_manager_ = std::make_unique<EntityManager>();
  system_manager_ = std::make_unique<SystemManager>();
  return *this;
}

#ifdef _DEBUG
void Coordinator::debug_warning() {
  std::cout

      << "The _DEBUG preprocessor definition has been detected" << std::endl
      << std::endl
      << "######################## ECS ########################" << std::endl
      << "ECS (Entity Component System) is curently configured like this:"
      << std::endl
      << "The Entity datatype alias is represented by (" << sizeof(Entity) * 8
      << " bit) " << typeid(Entity).name() << std::endl
      << "The ComponentType datatype alias is represented by ("
      << sizeof(ComponentType) * 8 << " bit) " << typeid(ComponentType).name()
      << std::endl
      << "The Signature datatype alias is represented by "
      << typeid(Signature).name() << std::endl
      << "The maximum number of entities is " << kMaxEntities << std::endl
      << "The maximum number of component types is " << kMaxComponentTypes
      << std::endl
      << std::endl
      << "NOTE: The datatypes used for the Entity and ComponentType aliases "
      << std::endl
      << "can be changed in ecs/config.h by setting the " << std::endl
      << "ECS_ENTITY_DATATYPE and ECS_COMPONENT_TYPE_DATATYPE " << std::endl
      << "preprocessor definitions to the desired datatype." << std::endl
      << std::endl
      << "NOTE: Likewise the size of the Signature bitset, as well as the "
      << std::endl
      << "maximum number of Entity and ComponentType objects can be "
      << std::endl
      << "adjusted by setting the ECS_MAX_ENTITIES and " << std::endl
      << "ECS_MAX_COMPONENT_TYPES preprocessor definitions." << std::endl
      << "#####################################################" << std::endl
      << std::endl;
}
#endif

}  // namespace ECS