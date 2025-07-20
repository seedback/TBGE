#include "src/ecs/entity_manager.h"

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

#include "src/ecs/definitions.h"
namespace ECS {
EntityManager::EntityManager() {
  // Initialize the queue with all possible entity IDs
  for (Entity entity = 0; entity < kMaxEntities; ++entity) {
    available_entities_.push(entity);
  }
}

Entity EntityManager::CreateEntity() {
  assert(current_entity_count_ < kMaxEntities &&
         "Too many entities in existence.");

  // Take an ID from the front of the queue
  Entity id = available_entities_.front();
  available_entities_.pop();
  ++current_entity_count_;

  return id;
}

EntityManager& EntityManager::DestroyEntity(Entity entity) {
  assert(entity < kMaxEntities && "Entity out of range.");

  // Invalidate the destroyed entity's signature
  signatures_[entity].reset();

  // Put the destroyed ID at the back of the queue
  available_entities_.push(entity);
  --current_entity_count_;

  return *this;
}

EntityManager& EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < kMaxEntities && "Entity out of range.");

  // Put this entity's signature into the array
  signatures_[entity] = signature;

  return *this;
}

Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < kMaxEntities && "Entity out of range.");

  // Get this entity's signature from the array
  return signatures_[entity];
}
};  // namespace ECS