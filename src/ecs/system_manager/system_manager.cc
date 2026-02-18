#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>

#include "src/ecs/context/context.h"
#include "src/ecs/system_manager/system_manager.h"

namespace ECS {

SystemManager& SystemManager::EntityDestroyed(
    Entity entity) {
  // Erase a destroyed entity from all system lists
  // entities_ is a set so no check needed
  for (auto const& pair : systems_) {
    auto const& system = pair.second;

    system->remove_entity_(entity);
  }

  return *this;
}

SystemManager& SystemManager::EntitySignatureChanged(
    Entity entity,
    Signature entitySignature) {
  // Notify each system that an entity's signature changed
  for (auto const& pair : systems_) {
    auto const& type = pair.first;
    auto const& system = pair.second;
    auto const& systemSignature = signatures_[type];

    // Entity signature matches system signature - insert into set
    if ((entitySignature & systemSignature) == systemSignature) {
      system->add_entity_(entity);
    }
    // Entity signature does not match system signature - erase from set
    else {
      system->remove_entity_(entity);
    }
  }

  return *this;
}

}  // namespace ECS
