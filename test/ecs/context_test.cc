#include "src/ecs/context/context.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <bitset>
#include <cstdint>
#include <limits>
#include <typeinfo>

#include "test/includes/test_log_sink.h"

/**
 * @brief Tests the macro-based ECS configuration system.
 *
 * @details
 * The ECS now uses compile-time macros instead of templates:
 * - ECS_ENTITY_CONFIG: Bit width of Entity type (8, 16, 32, or 64)
 * - ECS_COMPONENT_CONFIG: Bit width of ComponentTypeId (8, 16, or 32)
 * - ECS_MAX_COMPONENT_TYPES: Maximum number of component types
 *
 * These tests verify that the types are correctly configured based on the
 * macro values that are currently in effect.
 */

/**
 * @brief Test that Entity type is correctly sized based on ECS_ENTITY_CONFIG.
 *
 * The default configuration uses ECS_ENTITY_CONFIG=32, which should result in
 * a uint32_t Entity type.
 */
TEST(Context, EntityTypeConfiguration) {
#if ECS_ENTITY_CONFIG == 64
  EXPECT_EQ(sizeof(ECS::Entity), 8);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint64_t));
#elif ECS_ENTITY_CONFIG == 32
  EXPECT_EQ(sizeof(ECS::Entity), 4);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint32_t));
#elif ECS_ENTITY_CONFIG == 16
  EXPECT_EQ(sizeof(ECS::Entity), 2);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint16_t));
#elif ECS_ENTITY_CONFIG == 8
  EXPECT_EQ(sizeof(ECS::Entity), 1);
  EXPECT_EQ(typeid(ECS::Entity), typeid(std::uint8_t));
#endif
}

/**
 * @brief Test that ComponentTypeId type is correctly sized based on
 * ECS_COMPONENT_CONFIG.
 *
 * The default configuration uses ECS_COMPONENT_CONFIG=16, which should result
 * in a uint16_t ComponentTypeId type.
 */
TEST(Context, ComponentTypeIdConfiguration) {
#if ECS_COMPONENT_CONFIG == 32
  EXPECT_EQ(sizeof(ECS::ComponentTypeId), 4);
  EXPECT_EQ(typeid(ECS::ComponentTypeId), typeid(std::uint32_t));
#elif ECS_COMPONENT_CONFIG == 16
  EXPECT_EQ(sizeof(ECS::ComponentTypeId), 2);
  EXPECT_EQ(typeid(ECS::ComponentTypeId), typeid(std::uint16_t));
#elif ECS_COMPONENT_CONFIG == 8
  EXPECT_EQ(sizeof(ECS::ComponentTypeId), 1);
  EXPECT_EQ(typeid(ECS::ComponentTypeId), typeid(std::uint8_t));
#endif
}

/**
 * @brief Test that Signature is correctly sized based on ECS_MAX_COMPONENT_TYPES.
 *
 * The Signature should be a bitset with size equal to ECS_MAX_COMPONENT_TYPES.
 */
TEST(Context, SignatureConfiguration) {
  // Verify that kMaxComponentTypes matches the macro value
  EXPECT_EQ(ECS::kMaxComponentTypes, ECS_MAX_COMPONENT_TYPES);

  // Create a Signature and verify its size
  ECS::Signature sig;
  EXPECT_EQ(sig.size(), ECS_MAX_COMPONENT_TYPES);
}

/**
 * @brief Test that kMaxComponentTypes constant is correctly set.
 */
TEST(Context, MaxComponentTypesConstant) {
  EXPECT_GT(ECS::kMaxComponentTypes, 0);
  EXPECT_LE(ECS::kMaxComponentTypes, 65536);
  EXPECT_EQ(ECS::kMaxComponentTypes, ECS_MAX_COMPONENT_TYPES);
}

/**
 * @brief Test that Entity type max value is correctly derived from bit width.
 */
TEST(Context, EntityMaxValue) {
  ECS::Entity max_entity = std::numeric_limits<ECS::Entity>::max();

  // Verify the max value matches the expected size
#if ECS_ENTITY_CONFIG == 64
  EXPECT_EQ(max_entity, std::numeric_limits<std::uint64_t>::max());
#elif ECS_ENTITY_CONFIG == 32
  EXPECT_EQ(max_entity, std::numeric_limits<std::uint32_t>::max());
#elif ECS_ENTITY_CONFIG == 16
  EXPECT_EQ(max_entity, std::numeric_limits<std::uint16_t>::max());
#elif ECS_ENTITY_CONFIG == 8
  EXPECT_EQ(max_entity, std::numeric_limits<std::uint8_t>::max());
#endif
}

/**
 * @brief Test that ComponentTypeId type max value is correctly derived from bit
 * width.
 */
TEST(Context, ComponentTypeIdMaxValue) {
  ECS::ComponentTypeId max_type_id = std::numeric_limits<ECS::ComponentTypeId>::max();

  // Verify the max value matches the expected size
#if ECS_COMPONENT_CONFIG == 32
  EXPECT_EQ(max_type_id, std::numeric_limits<std::uint32_t>::max());
#elif ECS_COMPONENT_CONFIG == 16
  EXPECT_EQ(max_type_id, std::numeric_limits<std::uint16_t>::max());
#elif ECS_COMPONENT_CONFIG == 8
  EXPECT_EQ(max_type_id, std::numeric_limits<std::uint8_t>::max());
#endif
}

/**
 * @brief Test that Signature can be constructed and used properly.
 */
TEST(Context, SignatureUsage) {
  ECS::Signature sig1;
  ECS::Signature sig2(0b1010);
  ECS::Signature sig3(5);

  // Verify default construction creates all zeros
  EXPECT_EQ(sig1.count(), 0);

  // Verify construction with value works
  EXPECT_GT(sig2.count(), 0);
  EXPECT_GT(sig3.count(), 0);

  // Verify bitset operations work
  sig1[0] = 1;
  sig1[2] = 1;
  EXPECT_EQ(sig1.count(), 2);
}