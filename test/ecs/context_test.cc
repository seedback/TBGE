#include "src/ecs/context.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <bitset>
#include <cstdint>
#include <typeinfo>

#include "test/includes/test_log_sink.h"

TEST(Context, ContextDefault) {
  using TestContext = ECS::Context<>;  // Using default template

  EXPECT_EQ(typeid(TestContext::Entity), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::ComponentTypeId), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<65535>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint16_t));
  EXPECT_EQ(TestContext::kMaxEntities, 65535);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 65535);
}

TEST(Context, ContextCustomTypes) {
  // Setting custom types
  using TestContext = ECS::Context< 2000, 100>;

  EXPECT_EQ(typeid(TestContext::Entity), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::ComponentTypeId), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<100>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint16_t));
  EXPECT_EQ(TestContext::kMaxEntities, 2000);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 100);
}

TEST(Context, ContextCustomALL) {
  // Setting custom types and values
  using TestContext = ECS::Context<500, 50, std::uint32_t, std::uint8_t>;

  EXPECT_EQ(typeid(TestContext::Entity), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::ComponentTypeId), typeid(std::uint8_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<50>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint8_t));
  EXPECT_EQ(TestContext::kMaxEntities, 500);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 50);
}