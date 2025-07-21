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

      << "The \033[31m_DEBUG\033[0m preprocessor definition has been detected"
      << std::endl
      << "\033[33m######################## ECS ########################\033[0m"
      << std::endl
      << "ECS (Entity Component System) is curently configured like this:"
      << std::endl
      << "The \033[34mEntity\033[0m datatype alias is represented by \033[36m("
      << sizeof(Entity) * 8 << " bit) " << typeid(Entity).name() << "\033[0m"
      << std::endl
      << "The \033[34mComponentType\033[0m datatype alias is represented by "
         "\033[36m("
      << sizeof(ComponentType) * 8 << " bit) " << typeid(ComponentType).name()
      << "\033[0m" << std::endl
      << "The \033[34mSignature\033[0m datatype alias is represented by "
         "\033[36m"
      << typeid(Signature).name() << "\033[0m" << std::endl
      << "The maximum number of \033[34mentities\033[0m is \033[36m"
      << kMaxEntities << "\033[0m" << std::endl
      << "The maximum number of \033[34mcomponent\033[0m types is \033[36m"
      << kMaxComponentTypes << "\033[0m" << std::endl
      << std::endl
      << "NOTE: The datatypes used for the \033[34mEntity\033[0m and "
         "\033[34mComponentType\033[0m aliases "
      << std::endl
      << "can be changed in \033[90mecs/config.h\033[0m by setting the "
      << std::endl
      << "\033[90mECS_ENTITY_DATATYPE\033[0m and "
         "\033[90mECS_COMPONENT_TYPE_DATATYPE\033[0m "
      << std::endl
      << "preprocessor definitions to the desired datatype." << std::endl
      << std::endl
      << "NOTE: Likewise the size of the \033[34mSignature\033[0m bitset, as "
         "well as the "
      << std::endl
      << "maximum number of \033[34mEntity\033[0m and "
         "\033[34mComponentType\033[0m objects can be "
      << std::endl
      << "adjusted by setting the \033[90mECS_MAX_ENTITIES\033[0m and "
      << std::endl
      << "\033[90mECS_MAX_COMPONENT_TYPES\033[0m preprocessor definitions."
      << std::endl
      << "\033[33m#####################################################\033[0m"
      << std::endl
      << std::endl;
}
#endif

}  // namespace ECS