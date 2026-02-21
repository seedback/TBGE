#include "src/ecs/system_manager/system_manager.h"

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>

#include "src/ecs/context/context.h"

namespace tbge::ecs {

/**
 * @brief Notifies all systems that an entity has been destroyed.
 *
 * @details
 * This method iterates through all registered systems and calls their
 * remove_entity_() method to clean up any references to the destroyed entity.
 *
 * @param entity The entity that has been destroyed.
 * @return Reference to this SystemManager for method chaining.
 */
SystemManager& SystemManager::EntityDestroyed(Entity entity) {
  // Erase a destroyed entity from all system lists
  // entities_ is a set so no check needed
  for (auto const& pair : systems_) {
    auto const& system = pair.second;

    system->remove_entity_(entity);
  }

  return *this;
}

/**
 * @brief Notifies systems when an entity's signature has changed.
 *
 * @details
 * Iterates through all systems and adds the entity to systems whose signatures
 * are satisfied by the new entity signature, and removes it from systems that
 * are no longer satisfied.
 *
 * The bitwise AND check `(entitySignature & systemSignature) ==
 * systemSignature` ensures the entity has all components required by the
 * system.
 *
 * @param entity The entity whose signature changed.
 * @param entitySignature The new signature representing the entity's
 * components.
 * @return Reference to this SystemManager for method chaining.
 */
SystemManager& SystemManager::EntitySignatureChanged(
    Entity entity, Signature entitySignature) {
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

}  // namespace tbge::ecs
