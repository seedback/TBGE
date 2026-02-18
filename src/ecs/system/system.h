#ifndef TBGE_SRC_ECS_SYSTEM_H_
#define TBGE_SRC_ECS_SYSTEM_H_

#include <absl/log/log.h>

#include <set>

#include "src/ecs/context/context.h"

namespace ECS {

/**
 * @class System
 * @brief Represents a system in the Entity-Component-System (ECS) architecture.
 *
 * The System class manages a set of entities that it operates on.
 * Each system typically processes entities that have a specific set of
 * components.
 */
class System {
 public:
  std::set<Entity> get_entities() { return entities_; }

  bool has_entity(Entity entity) {
    return entities_.count(entity) > 0;
  }

 protected:
  virtual System& set_entities(std::set<Entity> entities) {
    // Do I need safety on this? Checking wether all entities are valid?
    // TODO: Contemplate the question above and action it.
    entities_ = entities;

    return *this;
  }

  virtual System& add_entity(Entity entity) {return *this;}

  virtual System& remove_entity(Entity entity) {return *this;}

 private:
  friend class SystemManager;

  std::set<Entity> entities_;

  System& add_entity_(Entity entity) {
    // Do I need safety on this? Checking wether all entities are valid?
    // TODO: Contemplate the question above and action it.
    if (!entities_.contains(entity)) {
      entities_.insert(entity);
      add_entity(entity);
    }

    return *this;
  }

  System& remove_entity_(Entity entity) {
    if (!entities_.contains(entity)) {
      entities_.erase(entity);
      remove_entity(entity);
    }
    return *this;
  }
};

}  // namespace ECS

#endif  // TBGE_SRC_ECS_SYSTEM_H_