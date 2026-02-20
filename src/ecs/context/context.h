/**
 * @file context.h
 * @brief Core type definitions and compile-time configuration for the ECS.
 *
 * @details
 * Defines all fundamental types used throughout the ECS system (Entity,
 * ComponentTypeId, Signature) with compile-time configuration options.
 * Configuration macros:
 * - ECS_ENTITY_CONFIG: Entity ID size in bits (8, 16, 32, or 64)
 * - ECS_COMPONENT_CONFIG: Component type ID size in bits (8, 16, or 32)
 * - ECS_MAX_COMPONENT_TYPES: Maximum number of component types (0 < n <= 65536)
 */

#ifndef TBGE_ECS_CONTEXT_H_
#define TBGE_ECS_CONTEXT_H_

#ifdef _WIN32
#include <windows.h>
#ifdef max
#undef max
#endif  // max
#ifdef min
#undef min
#endif  // min
#endif  // _WIN32

#include <bitset>
#include <cstdint>
#include <limits>

namespace ecs {

/**
 * @defgroup ECS_Config Type Configuration
 * @{
 *
 * @brief Configuration macros for ECS entity and component type sizes.
 *
 * The following macros control the bit width of ECS types:
 *
 * - `ECS_ENTITY_CONFIG`: Entity ID size in bits (default: 32)
 *   - Supported values: 8, 16, 32, 64
 *   - Maps to `Entity` type
 *
 * - `ECS_COMPONENT_CONFIG`: Component type ID size in bits (default: 16)
 *   - Supported values: 8, 16, 32
 *   - Maps to `ComponentTypeId` type
 *
 * - `ECS_MAX_COMPONENT_TYPES`: Maximum number of component types (default:
 * 1024)
 *   - Used for `Signature` bitset size
 *   - Must be a compile-time constant
 *
 * @note Define these macros before including ECS headers if you want
 * different size configurations.
 *
 * @}
 */

#ifndef ECS_ENTITY_CONFIG
#define ECS_ENTITY_CONFIG 32
#endif  // ECS_ENTITY_CONFIG

#ifndef ECS_COMPONENT_CONFIG
#define ECS_COMPONENT_CONFIG 16
#endif  // ECS_COMPONENT_CONFIG

#ifndef ECS_MAX_COMPONENT_TYPES
#define ECS_MAX_COMPONENT_TYPES 1024
#endif  // ECS_MAX_COMPONENT_TYPES

// Validate configuration macros
#if !((ECS_ENTITY_CONFIG) == 8 || (ECS_ENTITY_CONFIG) == 16 || \
      (ECS_ENTITY_CONFIG) == 32 || (ECS_ENTITY_CONFIG) == 64)
#error "ECS_ENTITY_CONFIG must be 8, 16, 32, or 64"
#endif

#if !((ECS_COMPONENT_CONFIG) == 8 || (ECS_COMPONENT_CONFIG) == 16 || \
      (ECS_COMPONENT_CONFIG) == 32)
#error "ECS_COMPONENT_CONFIG must be 8, 16, or 32"
#endif

#if (ECS_MAX_COMPONENT_TYPES) <= 0
#error "ECS_MAX_COMPONENT_TYPES must be greater than 0"
#endif

#if ECS_ENTITY_CONFIG == 64
/// @brief Entity identifier type (configured for 64-bit).
using Entity = std::uint64_t;
#elif ECS_ENTITY_CONFIG == 32
/// @brief Entity identifier type (configured for 32-bit).
using Entity = std::uint32_t;
#elif ECS_ENTITY_CONFIG == 16
/// @brief Entity identifier type (configured for 16-bit).
using Entity = std::uint16_t;
#else  // ECS_ENTITY_CONFIG == 8
/// @brief Entity identifier type (configured for 8-bit).
using Entity = std::uint8_t;
#endif

#if ECS_COMPONENT_CONFIG == 32
/// @brief Component type identifier type (configured for 32-bit).
using ComponentTypeId = std::uint32_t;
#elif ECS_COMPONENT_CONFIG == 16
/// @brief Component type identifier type (configured for 16-bit).
using ComponentTypeId = std::uint16_t;
#else  // ECS_COMPONENT_CONFIG == 8
/// @brief Component type identifier type (configured for 8-bit).
using ComponentTypeId = std::uint8_t;
#endif

constexpr size_t kMaxComponentTypes = ECS_MAX_COMPONENT_TYPES;

// Validate ECS_MAX_COMPONENT_TYPES at compile time
static_assert(ECS_MAX_COMPONENT_TYPES > 0,
              "ECS_MAX_COMPONENT_TYPES must be greater than 0");
static_assert(ECS_MAX_COMPONENT_TYPES <= 65536,
              "ECS_MAX_COMPONENT_TYPES must not exceed 65536");

/// @brief Bitset representing which component types are associated with an
/// entity.
using Signature = std::bitset<kMaxComponentTypes>;

}  // namespace ECS

#endif  // TBGE_ECS_CONTEXT_H_