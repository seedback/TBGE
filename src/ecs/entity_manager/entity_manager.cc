#include "src/ecs/entity_manager/entity_manager.h"

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <limits>
#include <queue>
#include <vector>

#include "src/ecs/context/context.h"

namespace ECS {

Entity EntityManager::CreateEntity() {
  // If there are no available entities, create one
  if (available_entities_.empty()) {
    CHECK(entity_id_counter_ < std::numeric_limits<Entity>::max())
        << "Too many Entities were created. The maximum amount of Entities is "
        << std::numeric_limits<Entity>::max()
        << ". To increase this limit, define ECS_ENTITY_CONFIG to a larger "
           "value "
        << "(8, 16, 32, or 64 bits) before including ECS headers for the first "
           "time.";

    available_entities_.push(entity_id_counter_);
    signatures_.push_back(Signature());
    ++entity_id_counter_;
  }

  // Take an ID from the front of the queue
  Entity id = available_entities_.front();
  available_entities_.pop();
  ++current_entity_count_;

  return id;
}

EntityManager& EntityManager::DestroyEntity(Entity entity) {
#ifndef NDEBUG
  if (entity >= entity_id_counter_) {
    LOG(ERROR) << "Attempted to destroy Entity out of range at Entity ID "
               << entity << ". The current amount of Entities is "
               << entity_id_counter_
               << ". This error usually means that you're trying to access an "
                  "Entity that has not yet been created or has been deleted.";
    return *this;
  }
#endif

  // Invalidate the destroyed entity's signature
  signatures_.at(entity).reset();

  // Put the destroyed ID at the back of the queue
  available_entities_.push(entity);
  --current_entity_count_;

  return *this;
}

bool EntityManager::HasEntity(Entity entity) {
  if (entity > entity_id_counter_) {
    return false;
  }

  bool has_entity = true;

  for (size_t i = 0; i < available_entities_.size(); ++i) {
    if (available_entities_.front() == entity) {
      // If the entity is in the queue it does not currently exist
      has_entity = false;
    }
    available_entities_.push(available_entities_.front());
    available_entities_.pop();
  }

  return has_entity;
}

EntityManager& EntityManager::SetSignature(Entity entity, Signature signature) {
#ifndef NDEBUG
  if (entity >= entity_id_counter_) {
    LOG(ERROR)
        << "Attempted to set signature of Entity out of range at Entity ID "
        << entity << ". The current amount of Entities is "
        << entity_id_counter_
        << ". This error usually means that you're trying to access an "
           "Entity that has not yet been created or has been deleted.";
    return *this;
  }
#endif

  // Put this entity's signature into the array
  signatures_.at(entity) = signature;

  return *this;
}

Signature EntityManager::GetSignature(Entity entity) {
  CHECK(entity < entity_id_counter_)
      << "Attempted to get signature of Entity out of range at Entity ID "
      << entity << ". The current amount of Entities is " << entity_id_counter_
      << ". This error usually means that you're trying to access an "
         "Entity that has not yet been created or has been deleted.";

  // Get this entity's signature from the array
  return signatures_.at(entity);
}

}  // namespace ECS
