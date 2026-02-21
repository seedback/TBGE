#ifndef TBGE_ECS_SYSTEM_MANAGER_TCC_
#define TBGE_ECS_SYSTEM_MANAGER_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>

#include "src/ecs/context/context.h"
#include "src/ecs/system_manager/system_manager.h"

namespace ecs {

template <typename T>
std::shared_ptr<T> SystemManager::RegisterSystem() {
  static_assert(
      std::is_base_of<System, T>::value,
      "Cannot register a system of type T. Must inherit from ECS::System");
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) != systems_.end()) {
    LOG(WARNING) << "Registering system of typename '" << type_name
                 << "' more than once, returning existing pointer";

    return std::static_pointer_cast<T>(systems_.find(type_name)->second);
  }

  // Create a pointer to the system and return it so it can be used externally
  std::shared_ptr<T> system = std::make_shared<T>();
  systems_.insert({type_name, std::static_pointer_cast<System>(system)});
  return system;
}

template <typename T>
SystemManager& SystemManager::SetSignature(Signature signature) {
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) == systems_.end()) {
    LOG(ERROR) << "Attempted to set signature on system of typename \""
               << type_name
               << "\" before it was registered. No signature will be "
                  "registered, this may lead to bugs and errors down the line.";
    return *this;
  }

  if (signatures_.find(type_name) != signatures_.end()) {
    // If the signature already exists, replace the value.
    signatures_.find(type_name)->second = signature;
  } else {
    // Set the signature for this system
    signatures_.insert({type_name, signature});
  }

  return *this;
}

template <typename T>
Signature SystemManager::GetSignature() {
  const char* type_name = typeid(T).name();

  if (signatures_.find(type_name) == signatures_.end()) {
    LOG(WARNING) << "Signature for system of typename '" << type_name
                 << "' was not set. Returning empty signature.";
    return Signature();
  }

  return signatures_[type_name];
}

// EntityDestroyed and EntitySignatureChanged are implemented in
// system_manager.cc

template <typename T>
std::shared_ptr<T> SystemManager::GetSystem() {
  const char* type_name = typeid(T).name();

  if (systems_.find(type_name) == systems_.end()) {
    LOG(ERROR) << "System of typename \"" << type_name
               << "\" was not registered.";
    return nullptr;
  }

  return std::static_pointer_cast<T>(systems_[type_name]);
}

}  // namespace ECS

#endif  // TBGE_ECS_SYSTEM_MANAGER_TCC_