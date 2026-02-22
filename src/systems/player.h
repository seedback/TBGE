#ifndef TBGE_SYSTEMS_PLAYER_H_
#define TBGE_SYSTEMS_PLAYER_H_

#include "src/ecs/ecs.h"

namespace tbge {
class Player : ecs::System {
 public:
  ecs::Entity get_player_entity();
 private:
  ecs::System& add_entity(ecs::Entity);

  ecs::Entity player_entity_;
};
}  // namespace tbge

#endif  // TBGE_SYSTEMS_PLAYER_H_