#include "src/ecs/system_manager.h"

#include <cassert>
#include <memory>
#include <typeinfo>

namespace ECS {

template <typename T>
std::shared_ptr<T> SystemManager::RegisterSystem() {
  static_assert(std::is_base_of<System, T>::value,
                "T must inherit from System");
  const char* type_name = typeid(T).name();

  assert(systems_.find(type_name) == systems_.end() &&
         "Registering system more than once.");

  // Create a pointer to the system and return it so it can be used externally
  auto system = std::make_shared<T>();
  systems_.insert({type_name, system});
  return system;
}

template <typename T>
SystemManager& SystemManager::SetSignature(Signature signature) {
  const char* type_name = typeid(T).name();

  assert(systems_.find(type_name) != systems_.end() &&
         "System used before registered.");

  // Set the signature for this system
  signatures_.insert({type_name, signature});

  return *this;
}

SystemManager& SystemManager::EntityDestroyed(Entity entity) {
  // Erase a destroyed entity from all system lists
  // entities_ is a set so no check needed
  for (auto const& pair : systems_) {
    auto const& system = pair.second;

    system->entities_.erase(entity);
  }

  return *this;
}

SystemManager& SystemManager::EntitySignatureChanged(
    Entity entity, Signature entitySignature) {
  // Notify each system that an entity's signature changed
  for (auto const& pair : systems_) {
    auto const& type = pair.first;
    auto const& system = pair.second;
    auto const& systemSignature = signatures_[type];

    // Entity signature matches system signature - insert into set
    if ((entitySignature & systemSignature) == systemSignature) {
      system->entities_.insert(entity);
    }
    // Entity signature does not match system signature - erase from set
    else {
      system->entities_.erase(entity);
    }
  }

  return *this;
}

}  // namespace ECS