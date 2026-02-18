#include <absl/log/check.h>
#include <absl/log/log.h>

#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "src/ecs/component_array/component_array.h"
#include "src/ecs/component_manager/component_manager.h"
#include "src/ecs/context/context.h"

namespace ECS {

ComponentManager& ComponentManager::EntityDestroyed(
    Entity entity) {
  // Notify each component array that an entity has been destroyed
  // If it has a component for that entity, it will remove it
  for (auto const& [type_name, component] : component_arrays_) {
    component->EntityDestroyed(entity);
  }

  return *this;
}

}  // namespace ECS
