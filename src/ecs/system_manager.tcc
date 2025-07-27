#ifndef TBGE_SRC_ECS_SYSTEM_MANAGER_TCC_
#define TBGE_SRC_ECS_SYSTEM_MANAGER_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>

#include "src/ecs/context.h"
#include "src/ecs/system_manager.h"

namespace ECS {

template <typename Context>
template <typename T>
std::shared_ptr<T> SystemManager<Context>::RegisterSystem() {
  static_assert(
      std::is_base_of<System<Context>, T>::value,
      "Cannot register a system of type T. Must inherit from ECS::System");
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) != systems_.end()) {
    LOG(WARNING) << "Registering system of typename "
                 << std::string(typeid(T).name())
                 << " more than once, returning existing pointer";

    return std::static_pointer_cast<T>(systems_.find(type_name)->second);
  }

  // Create a pointer to the system and return it so it can be used externally
  std::shared_ptr<T> system = std::make_shared<T>();
  systems_.insert(
      {type_name, std::static_pointer_cast<System<Context>>(system)});
  return system;
}

template <typename Context>
template <typename T>
SystemManager<Context>& SystemManager<Context>::SetSignature(
    typename Context::Signature signature) {
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) == systems_.end()) {
    LOG(ERROR) << "Attempted to set signature on system of typename "
               << type_name
               << " before it was registered. No signature will be registered, this may lead to bugs and errors down the line.";
    return *this;
  }

  if (signatures_.find(type_name) != signatures_.end()) {
    // If the signature already exists, replace the vlaue.
    signatures_.find(type_name)->second = signature;
  } else {
    // Set the signature for this system
    signatures_.insert({type_name, signature});
  }

  return *this;
}

template <typename Context>
SystemManager<Context>& SystemManager<Context>::EntityDestroyed(
    typename Context::Entity entity) {
  // Erase a destroyed entity from all system lists
  // entities_ is a set so no check needed
  for (auto const& pair : systems_) {
    auto const& system = pair.second;

    system->remove_entity(entity);
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
      system->add_entity(entity);
    }
    // Entity signature does not match system signature - erase from set
    else {
      system->remove_entity(entity);
    }
  }

  return *this;
}

}  // namespace ECS

#endif  // TBGE_SRC_ECS_SYSTEM_MANAGER_TCC_