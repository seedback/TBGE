#ifndef TBGE_SRC_ECS_SYSTEM_H_
#define TBGE_SRC_ECS_SYSTEM_H_

#include <absl/log/log.h>

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
  System& set_entities(std::set<typename Context::Entity> entities) {
    // Do I need safety on this? Checking wether all entities are valid?
    // TODO: Contemplate the question above and action it.
    entities_ = entities;

    return *this;
  }

  std::set<typename Context::Entity> get_entities() { return entities_; }

  System& add_entity(typename Context::Entity entity) {
    // Do I need safety on this? Checking wether all entities are valid?
    // TODO: Contemplate the question above and action it.
    entities_.insert(entity);

    return *this;
  }

  System& remove_entity(typename Context::Entity entity) {
    entities_.erase(entity);
    return *this;
  }

  bool has_entity(typename Context::Entity entity) {
    return entities_.count(entity) > 0;
  }

 private:
  // TODO: make this private with set/get functions
  std::set<typename Context::Entity> entities_;
};

}  // namespace ECS

#endif  // TBGE_SRC_ECS_SYSTEM_H_