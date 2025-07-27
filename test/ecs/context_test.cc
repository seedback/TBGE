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
  EXPECT_EQ(typeid(TestContext::ComponentType), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<65535>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint16_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint16_t));
  EXPECT_EQ(TestContext::kMaxEntities, 65535);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 65535);
}

TEST(Context, ContextCustomTypes) {
  // Setting custom types
  using TestContext = ECS::Context<std::uint32_t, std::uint8_t>;

  EXPECT_EQ(typeid(TestContext::Entity), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::ComponentType), typeid(std::uint8_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<255>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint8_t));
  EXPECT_EQ(TestContext::kMaxEntities, 4294967295);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 255);
}

TEST(Context, ContextCustomALL) {
  // Setting custom types and values
  using TestContext = ECS::Context<std::uint32_t, std::uint8_t, 500, 50>;

  EXPECT_EQ(typeid(TestContext::Entity), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::ComponentType), typeid(std::uint8_t));
  EXPECT_EQ(typeid(TestContext::Signature), typeid(std::bitset<50>));
  EXPECT_EQ(typeid(TestContext::kMaxEntities), typeid(std::uint32_t));
  EXPECT_EQ(typeid(TestContext::kMaxComponentTypes), typeid(std::uint8_t));
  EXPECT_EQ(TestContext::kMaxEntities, 500);
  EXPECT_EQ(TestContext::kMaxComponentTypes, 50);
}