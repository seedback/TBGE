#ifndef TBGE_SRC_ECS_SYSTEM_H_
#define TBGE_SRC_ECS_SYSTEM_H_

#include <set>

#include "src/ecs/context.h"

namespace ECS {

/**
 * @class System
 * @brief Represents a system in the Entity-Component-System (ECS) architecture.
 *
 * The System class manages a set of entities that it operates on.
 * Each system typically processes entities that have a specific set of
 * components.
 */
template <typename Context = ECS::Context<>>
class System {
 public:
  std::set<typename Context::Entity>
      entities_;  // TODO: make this private with set/get functions
};

}  // namespace ECS

#endif  // TBGE_SRC_ECS_SYSTEM_H_