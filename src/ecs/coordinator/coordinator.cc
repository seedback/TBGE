#include <iostream>
#include <absl/log/log.h>

#include "src/ecs/component/component.h"
#include "src/ecs/component_manager/component_manager.h"
#include "src/ecs/context/context.h"
#include "src/ecs/coordinator/coordinator.h"
#include "src/ecs/entity_manager/entity_manager.h"
#include "src/ecs/system_manager/system_manager.h"

namespace ECS {

// #####   Constructors   #####
Coordinator::Coordinator() {
  Init();
}

// #####   Entity methods   #####
Entity Coordinator::CreateEntity() {
  return entity_manager_->CreateEntity();
}

Coordinator& Coordinator::DestroyEntity(
    Entity entity) {
  entity_manager_->DestroyEntity(entity);
  component_manager_->EntityDestroyed(entity);
  system_manager_->EntityDestroyed(entity);

  return *this;
}

Signature Coordinator::GetEntitySignature(
    Entity entity) {
  return entity_manager_->GetSignature(entity);
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
  LOG(INFO)
      << "The _DEBUG preprocessor definition has been detected\n"
      << "######################## ECS ########################\n"
      << "ECS (Entity Component System) is currently configured like this:\n"
      << "The Entity datatype alias is represented by ("
      << sizeof(Entity) * 8 << " bit) "
      << typeid(Entity).name() << "\n"
      << "The ComponentType datatype alias is represented by ("
      << sizeof(ComponentTypeId) * 8 << " bit) "
      << typeid(ComponentTypeId).name() << "\n"
      << "The Signature datatype alias is represented by "
      << typeid(Signature).name() << "\n"
      << "The maximum number of component types is "
      << kMaxComponentTypes << "\n"
      << "\n"
      << "NOTE: The datatypes used for the Entity and ComponentType aliases\n"
      << "can be changed by defining ECS_CONFIG_64BIT\n"
      << "preprocessor definition.\n"
      << "\n"
      << "NOTE: Likewise the size of the Signature bitset can be\n"
      << "adjusted by changing kMaxComponentTypes.\n"
      << "#####################################################\n"
      << std::endl;
}
#endif

}  // namespace ECS
