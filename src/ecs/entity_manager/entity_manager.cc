#include <absl/log/check.h>
#include <absl/log/log.h>

#include <iostream>
#include <queue>
#include <vector>

#include "src/ecs/context/context.h"
#include "src/ecs/entity_manager/entity_manager.h"

namespace ECS {

Entity EntityManager::CreateEntity() {
  // If there are no available entities, create one
  if (available_entities_.empty()) {
#ifndef _DEBUG
    CHECK(entity_id_counter_ < std::numeric_limits<Entity>::max())
        << "Too many Entities were created.";
#else
    CHECK(entity_id_counter_ < std::numeric_limits<Entity>::max())
        << "Too many Entities were created. The maximum amount of Entities is "
        << std::to_string(std::numeric_limits<Entity>::max())
        << " and has been reached.";
#endif

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

EntityManager& EntityManager::DestroyEntity(
    Entity entity) {
  if (entity >= entity_id_counter_) {
#ifndef _DEBUG
    LOG(ERROR) << "Attempted to destroy Entity out of range.";
#else
    LOG(ERROR) << "Attempted to destroy Entity out of range. The maximum "
                  "amount of Entities is "
               << std::to_string(entity_id_counter_)
               << ". ID that was attempted to be removed is "
               << std::to_string(entity)
               << ".";
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

bool EntityManager::HasEntity(Entity entity) {
  if (entity > entity_id_counter_) {
    return false;
  }

  bool has_entity = true;

  for (int i = 0; i < available_entities_.size(); i++) {
    if (available_entities_.front() == entity) {
      // If the entity is in the queue it does not currently exist
      has_entity = false;
    }
    available_entities_.push(available_entities_.front());
    available_entities_.pop();
  }

  return has_entity;
}

EntityManager& EntityManager::SetSignature(
    Entity entity, Signature signature) {
  if (entity >= entity_id_counter_) {
#ifndef _DEBUG
    LOG(ERROR) << "Attempted to set signature of Entity out of range.";
#else
    LOG(ERROR)
        << "Attempted to set signature of Entity out of range at Entity ID "
        << std::to_string(entity) << ". The current amount of Entities is "
        << std::to_string(entity_id_counter_)
        << ". This error usually means that you're trying to access an "
           "Entity that has not yet been created or has been deleted.";
#endif
    return *this;
  }

  // Put this entity's signature into the array
  signatures_.at(entity) = signature;

  return *this;
}

Signature EntityManager::GetSignature(
    Entity entity) {
#ifndef _DEBUG
  CHECK(entity < entity_id_counter_)
      << "Attempted to get signature of Entity out of range.";
#else
  CHECK(entity < entity_id_counter_)
      << "Attempted to get signature of Entity out of range at Entity ID "
      << std::to_string(entity) << ". The current amount of Entities is "
      << std::to_string(entity_id_counter_)
      << ". This error usually means that you're trying to access an "
         "Entity that has not yet been created or has been deleted.";
#endif

  // Get this entity's signature from the array
  return signatures_.at(entity);
}

}  // namespace ECS
