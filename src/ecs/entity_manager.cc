#include "src/ecs/entity_manager.h"

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <iostream>
#include <queue>
#include <vector>

#include "src/ecs/definitions.h"
namespace ECS {
EntityManager::EntityManager() {
  // TODO: don't preemptively fill the queue, but rather keep track of how many
  // are available, and if/when necessary add more.
}

Entity EntityManager::CreateEntity() {
  // Keeps track of the next entity ID to be used
  static Entity entity_id_counter = 0;
  // If there are no available entities, create one
  if (available_entities_.empty()) {
#ifndef _DEBUG
    CHECK(entity_id_counter < kMaxEntities)
        << "Too many Entities were created.";
#else
    // TODO: Update message to reflect that the config has been made
    // programatic, when this change is made.
    LOG(ERROR) << entity_id_counter << " : " << kMaxEntities;
    CHECK(entity_id_counter < kMaxEntities)
        << "Too many Entities were created. The maximum amount of Entities is "
        << kMaxEntities << ". This maximum can be adjusted in ecs/config.h.";
#endif

    available_entities_.push(entity_id_counter);
    ++entity_id_counter;
  }

  // Take an ID from the front of the queue
  Entity id = available_entities_.front();
  available_entities_.pop();
  ++current_entity_count_;

  return id;
}

EntityManager& EntityManager::DestroyEntity(Entity entity) {
  if (entity >= kMaxEntities) {
#ifndef _DEBUG
    LOG(ERROR) << "Attempted to destroy Entity out of range.";
#else
    LOG(ERROR) << "Attempted to destroy Entity out of range. The maximum "
                  "amount of Entities is "
               << kMaxEntities
               << ". This maximum can be adjusted in ecs/config.h.";
#endif
    return *this;
  }

  // Invalidate the destroyed entity's signature
  signatures_.at(entity).reset();

  // Put the destroyed ID at the back of the queue
  available_entities_.push(entity);
  --current_entity_count_;

  return *this;
}

EntityManager& EntityManager::SetSignature(Entity entity, Signature signature) {
  if (entity >= kMaxEntities) {
#ifndef _DEBUG
    LOG(ERROR) << "Attempted to set signature of Entity out of range.";
#else
    LOG(ERROR) << "Attempted to set signature of Entity out of range. The "
                  "maximum amount of Entities is "
               << kMaxEntities
               << ". This maximum can be adjusted in ecs/config.h.";
#endif
    return *this;
  }

  // Put this entity's signature into the array
  signatures_.at(entity) = signature;

  return *this;
}

Signature EntityManager::GetSignature(Entity entity) {
#ifndef _DEBUG
    CHECK(entity > kMaxEntities) << "Attempted to get signature of Entity out of range.";
#else
    CHECK(entity > kMaxEntities) << "Attempted to get signature of Entity out of range. The "
                  "maximum amount of Entities is "
               << kMaxEntities
               << ". This maximum can be adjusted in ecs/config.h.";
#endif

  // Get this entity's signature from the array
  return signatures_.at(entity);
}
};  // namespace ECS