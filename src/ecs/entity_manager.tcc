#ifndef TBGE_SRC_ECS_ENTITY_MANAGER_TCC_
#define TBGE_SRC_ECS_ENTITY_MANAGER_TCC_

#include <absl/log/check.h>
#include <absl/log/log.h>

#include <iostream>
#include <queue>
#include <vector>

#include "src/ecs/context.h"
#include "src/ecs/entity_manager.h"

namespace ECS {

template <typename Context>
typename Context::Entity EntityManager<Context>::CreateEntity() {
  // If there are no available entities, create one
  if (available_entities_.empty()) {
#ifndef _DEBUG
    CHECK(entity_id_counter_ < Context::kMaxEntities)
        << "Too many Entities were created.";
#else
    // TODO: Update message to reflect that the config has been made
    // programatic, when this change is made.
    CHECK(entity_id_counter_ < Context::kMaxEntities)
        << "Too many Entities were created. The maximum amount of Entities is "
        << std::to_string(Context::kMaxEntities)
        << " and has been reached. This maximum can be adjusted in the "
           "Context.";
#endif

    available_entities_.push(entity_id_counter_);
    signatures_.push_back(typename Context::Signature());
    ++entity_id_counter_;
  }

  // Take an ID from the front of the queue
  typename Context::Entity id = available_entities_.front();
  available_entities_.pop();
  ++current_entity_count_;

  return id;
}

template <typename Context>
EntityManager<Context>& EntityManager<Context>::DestroyEntity(
    typename Context::Entity entity) {
  if (entity >= entity_id_counter_) {
#ifndef _DEBUG
    LOG(ERROR) << "Attempted to destroy Entity out of range.";
#else
    LOG(ERROR) << "Attempted to destroy Entity out of range. The maximum "
                  "amount of Entities is "
               << std::to_string(entity_id_counter_)
               << ". ID that was attempted to be removed is "
               << std::to_string(entity)
               << ". This maximum can be adjusted in the Context.";
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

template <typename Context>
bool EntityManager<Context>::HasEntity(typename Context::Entity entity) {
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

template <typename Context>
EntityManager<Context>& EntityManager<Context>::SetSignature(
    typename Context::Entity entity, typename Context::Signature signature) {
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

template <typename Context>
Context::Signature EntityManager<Context>::GetSignature(
    typename Context::Entity entity) {
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
};  // namespace ECS

#endif  // TBGE_SRC_ECS_ENTITY_MANAGER_TCC_