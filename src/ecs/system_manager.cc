#include "src/ecs/system_manager.h"

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>

#include "src/ecs/context.h"

namespace ECS {

template <typename Context>
template <typename T>
std::shared_ptr<T> SystemManager<Context>::RegisterSystem() {
  static_assert(
      std::is_base_of<System<Context>, T>::value,
      "Cannot register a system of type T. Must inherit from ECS::System");
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) != systems_.end()) {
    LOG(WARNING)
        << "Registering system more than once, returning existing pointer";
    return systems_.find(type_name);
  }

  // Create a pointer to the system and return it so it can be used externally
  auto system = std::make_shared<T>();
  systems_.insert({type_name, system});
  return system;
}

template <typename Context>
template <typename T>
SystemManager<Context>& SystemManager<Context>::SetSignature(
    typename Context::Signature signature) {
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) == systems_.end()) {
    LOG(ERROR) << "Attempted to set signature on system before it was "
                  "registered. No signature will be registered, this may lead "
                  "to bugs and errors down the line.";
    return *this;
  }

  // Set the signature for this system
  signatures_.insert({type_name, signature});

  return *this;
}

template <typename Context>
SystemManager<Context>& SystemManager<Context>::EntityDestroyed(
    typename Context::Entity entity) {
  // Erase a destroyed entity from all system lists
  // entities_ is a set so no check needed
  for (auto const& pair : systems_) {
    auto const& system = pair.second;

    system->entities_.erase(entity);
  }

  return *this;
}

template <typename Context>
SystemManager<Context>& SystemManager<Context>::EntitySignatureChanged(
    typename Context::Entity entity,
    typename Context::Signature entitySignature) {
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