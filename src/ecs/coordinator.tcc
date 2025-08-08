#ifndef TBGE_SRC_ECS_COORDINATOR_TCC_
#define TBGE_SRC_ECS_COORDINATOR_TCC_

#include <iostream>

#include "src/ecs/component_manager.h"
#include "src/ecs/context.h"
#include "src/ecs/coordinator.h"
#include "src/ecs/entity_manager.h"
#include "src/ecs/system_manager.h"

namespace ECS {
// #####   Constructors   #####
template <typename Context>
Coordinator<Context>::Coordinator() {
  Init();
}

// #####   Entity methods   #####
template <typename Context>
typename Context::Entity Coordinator<Context>::CreateEntity() {
  return entity_manager_->CreateEntity();
}

template <typename Context>
Coordinator<Context>& Coordinator<Context>::DestroyEntity(
    typename Context::Entity entity) {
  entity_manager_->DestroyEntity(entity);
  component_manager_->EntityDestroyed(entity);
  system_manager_->EntityDestroyed(entity);

  return *this;
}

// #####   Component methods   #####
template <typename Context>
template <typename T>
Coordinator<Context>& Coordinator<Context>::RegisterComponentType() {
  component_manager_->template RegisterComponentType<T>();

  return *this;
}

template <typename Context>
template <typename T>
Coordinator<Context>& Coordinator<Context>::AddComponent(
    typename Context::Entity entity, T component) {
  component_manager_->template AddComponent<T>(entity, component);

  typename Context::Signature signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->template GetComponentTypeId<T>(), true);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename Context>
template <typename T>
Coordinator<Context>& Coordinator<Context>::RemoveComponent(
    typename typename Context::Entity entity) {
  component_manager_->template RemoveComponent<T>(entity);

  // Grabbing the signature of the entity, resetting the bit corresponding to
  // the component, and setting the signature of the entity to the new one.
  typename Context::Signature signature = entity_manager_->GetSignature(entity);
  signature.set(component_manager_->template GetComponentTypeId<T>(), false);
  entity_manager_->SetSignature(entity, signature);

  system_manager_->EntitySignatureChanged(entity, signature);

  return *this;
}

template <typename Context>
template <typename T>
T& Coordinator<Context>::GetComponent(typename
                                      typename Context::Entity entity) {
  return component_manager_->template GetComponent<T>(entity);
}

template <typename Context>
template <typename T>
typename typename Context::ComponentTypeId
Coordinator<Context>::GetComponentTypeId() {
  return component_manager_->template GetComponentTypeId<T>();
}

// #####   System methods   #####
template <typename Context>
template <typename T>
std::shared_ptr<T> Coordinator<Context>::RegisterSystem() {
  return system_manager_->template RegisterSystem<T>();
}

template <typename Context>
template <typename T>
Coordinator<Context>& Coordinator<Context>::SetSystemSignature(
    typename Context::Signature signature) {
  system_manager_->template SetSignature<T>(signature);

  return *this;
}

// #####   Private methods   #####
template <typename Context>
Coordinator<Context>& Coordinator<Context>::Init() {
// Write a warning message when in debug mode about the limitations of the
// system and how to configure it
#ifdef _DEBUG
  this->debug_warning();
#endif

  // Create pointers to each manager
  component_manager_ = std::make_unique<ComponentManager<Context>>();
  entity_manager_ = std::make_unique<EntityManager<Context>>();
  system_manager_ = std::make_unique<SystemManager<Context>>();
  return *this;
}

#ifdef _DEBUG
template <typename Context>
void Coordinator<Context>::debug_warning() {
  LOG(INFO)
      << "The _DEBUG preprocessor definition has been detected\n"
      << "######################## ECS ########################\n"
      << "ECS (Entity Component System) is currently configured like this:\n"
      << "The Entity datatype alias is represented by ("
      << sizeof(typename Context::Entity) * 8 << " bit) "
      << typeid(typename Context::Entity).name() << "\n"
      << "The ComponentType datatype alias is represented by ("
      << sizeof(typename Context::ComponentTypeId) * 8 << " bit) "
      << typeid(typename Context::ComponentTypeId).name() << "\n"
      << "The Signature datatype alias is represented by "
      << typeid(typename Context::Signature).name() << "\n"
      << "The maximum number of entities is " << Context::kMaxEntities << "\n"
      << "The maximum number of component types is "
      << Context::kMaxComponentTypes << "\n"
      << "\n"
      << "NOTE: The datatypes used for the Entity and ComponentType aliases\n"
      << "can be changed in the ecs/Context by setting the\n"
      << "ECS_ENTITY_DATATYPE and ECS_COMPONENT_TYPE_DATATYPE\n"
      << "preprocessor definitions to the desired datatype.\n"
      << "\n"
      << "NOTE: Likewise the size of the Signature bitset, as well as the\n"
      << "maximum number of Entity and ComponentType objects can be\n"
      << "adjusted by setting the ECS_MAX_ENTITIES and\n"
      << "ECS_MAX_COMPONENT_TYPES preprocessor definitions.\n"
      << "#####################################################\n"
      << std::endl;
}
#endif
}  // namespace ECS
#endif  // TBGE_SRC_ECS_COORDINATOR_TCC_