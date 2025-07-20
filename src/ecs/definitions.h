/**
 * @file ecs.h
 * @brief Defines core types and aliases for the ECS (Entity Component System)
 * module.
 *
 * @details
 * This header provides the basic type definitions for entities and component
 * types used within the ECS framework.
 * Entities and Component Types are represented as 32-bit unsigned integers and
 * 16-bit unsigned integers, respectively, by default.
 * The maximum number of entities and component types defaults to the maximum
 * value of the underlying datatype
 *
 * Key features:
 * - Allows overriding the underlying data types for entities and component
 * types via ECS_ENTITY_DATATYPE and ECS_COMPONENT_TYPE_DATATYPE.
 * - Supports customizing the maximum number of entities and component types via
 * ECS_MAX_ENTITIES and ECS_MAX_COMPONENT_TYPES.
 * - Uses std::bitset to represent entity signatures for efficient component
 * queries.
 *
 * @note
 * - The default entity type is std::uint32_t, supporting up to 4,294,967,295
 * entities.
 * - The default component type is std::uint16_t, supporting up to 65,535
 * component types.
 * - Changing the maximums via preprocessor definitions can save memory but may
 * cause errors if set below the number of existing entities or component types.
 *
 * @copyright
 * This implementation is based on the writeup by Austin Morlan at
 * https://austinmorlan.com/posts/entity_component_system/
 */
#ifndef TBGE_SRC_ECS_DEFINITIONS_H_  // Header guard
#define TBGE_SRC_ECS_DEFINITIONS_H_

#include <bitset>
#include <cstdint>
#include <limits>

#include "src/ecs/config.h"

// Fallback in case the config.h doesn't define it
#ifndef ECS_ENTITY_DATATYPE
#define ECS_ENTITY_DATATYPE std::uint16_t
#endif  // ECS_ENTITY_DATATYPE

// Fallback in case the config.h doesn't define it
#ifndef ECS_COMPONENT_TYPE_DATATYPE
#define ECS_COMPONENT_TYPE_DATATYPE std::uint16_t
#endif  // ECS_COMPONENT_TYPE_DATATYPE

namespace ECS {
/**
 * @brief Type alias representing a unique identifier for an entity within the
 * ECS (Entity Component System).
 * @details Each Entity is represented as an unsigned integer, defaulting to
 * std::uint32_t allowing for 4294967295 Entities.
 *
 * @note
 * The datatype for this can be changed by setting the preprocessor definition
 * ECS_ENTITY_DATATYPE to the desired datatype. The preprocessor definition must
 * happen before inclusion of this file.
 *
 * @note
 * A 32 bit datatype is used by default as this gives ample room for most
 * projects. Going up to 64 bit datatypes and the queues and bitsets will get
 * unreasonably large. On smaller projects 16 or maybe even 8 bit datatypes are
 * viable.
 */
using Entity = ECS_ENTITY_DATATYPE;  // default std::uint32_t

/**
 * @brief The maximum number of entities supported by the ECS.
 * @details This defaults to the maximum value of the Entity alias, but can be
 * manually defined by setting the preprocessor definition ECS_MAX_ENTITIES to
 * the max amount you want. This may save some memory when the number of
 * existing Entities is significantly less than the default max.
 *
 * @note
 * Changing ECS_MAX_ENTITIES can lead to problems and errors if it's set to less
 * than the amount of existing Entities
 *
 * @see Entity
 */
#ifdef ECS_MAX_ENTITIES
constexpr Entity kMaxEntities = ECS_MAX_ENTITIES;
#else   // Fallback in case config.h is gone
constexpr Entity kMaxEntities = std::numeric_limits<Entity>::max();
#endif  // ECS_MAX_ENTITIES

// Expect this to be double indented because the autoformatter is whack
/**
 * @brief Type alias representing a unique identifier for a Component Type
 * within the ECS (Entity Component System).
 * @details Each Component Type is represented as an unsigned integer,
 * defaulting to std::uint16_t allowing for 65535 Component Type.
 *
 * @note
 * The datatype for this can be changed by setting the preprocessor
 * definition ECS_COMPONENT_TYPE_DATATYPE to the desired datatype. The
 * preprocessor definition must happen before inclusion of this file.
 *
 * @note
 * A 16 bit datatype is used by default as this gives ample room for most
 * projects. Going up to 64 bit datatypes and the queues and bitsets will
 * get unreasonably large. On smaller projects 8 bit datatypes are
 * viable.
 */
using ComponentType = ECS_COMPONENT_TYPE_DATATYPE;  // default std::uint16_t

/**
 * @brief The maximum number of Component Types supported by the ECS.
 * @details This defaults to the maximum value of the ComponentType alias, but
 * can be manually defined by setting the preprocessor definition
 * ECS_MAX_COMPONENT_TYPES to the max amount you want. This may save some memory
 * when the number of existing Component Types is significantly less than the
 * default max.
 *
 * @note
 * Changing ECS_MAX_COMPONENT_TYPES can lead to problems and errors if it's set
 * to less than the amount of existing Component Types
 *
 * @see ComponentType
 */
#ifdef ECS_MAX_COMPONENT_TYPES
constexpr ComponentType kMaxComponentTypes = ECS_MAX_COMPONENT_TYPES;
#else
constexpr ComponentType kMaxComponentTypes =
    std::numeric_limits<ComponentType>::max();
#endif  // ECS_MAX_COMPONENT_TYPES

// Expect this to be double indented because the autoformatter is whack
/**
 * @brief Type alias representing a set of component types associated with
 * an entity.
 * @details Signature is implemented as a std::bitset sized to the maximum
 * number of supported component types (kMaxComponentTypes). Each bit in the
 * Signature corresponds to a specific component type, indicating whether an
 * entity possesses that component. This is used internally by the ECS to
 * efficiently query and match entities with required component
 * combinations.
 */
using Signature = std::bitset<kMaxComponentTypes>;
}  // namespace ECS

#endif  // TBGE_SRC_ECS_DEFINITIONS_H_