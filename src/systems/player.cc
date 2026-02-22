#include "src/systems/player.h"

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/components/player_component.h"
#include "src/ecs/ecs.h"

namespace tbge {
extern ecs::Coordinator g_coordinator;

ecs::System& Player::add_entity(ecs::Entity entity) {
  if (get_entities().size() > 1) {
    LOG(WARNING) << "Player system rejected entity " << entity
                 << ": only one player entity is allowed.";
    std::set<ecs::Entity> entities = get_entities();
    entities.erase(entity);
    set_entities(entities);
    return *this;
  }
  player_entity_ = entity;
  return *this;
}
}  // namespace tbge