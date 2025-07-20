#include "src/ecs/component_manager.h"

#include "src/ecs/definitions.h"

namespace ECS {

ComponentManager& ComponentManager::EntityDestroyed(Entity entity) {
  // Notify each component array that an entity has been destroyed
  // If it has a component for that entity, it will remove it
  for (auto const& [type_name, component] : component_arrays_) {
    component->EntityDestroyed(entity);
  }

  return *this;
}

}  // namespace ECS