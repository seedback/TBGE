#include "src/ecs/system/system.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "src/ecs/context/context.h"
#include "test/includes/test_log_sink.h"

class SystemTest : public ::testing::Test {
 protected:
  void SetUp() override {
    absl::SetStderrThreshold(absl::LogSeverityAtLeast::kFatal);
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_system = ecs::System();
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs();
  }

  std::unique_ptr<TestLogSink> test_sink_;
  ecs::System test_system;
  ecs::Entity invalid_entity = 1000;
};

/**
 * @brief Test that get_entities returns an empty set initially.
 */
TEST_F(SystemTest, GetEntitiesInitiallyEmpty) {
  EXPECT_TRUE(test_system.get_entities().empty());
}

/**
 * @brief Test that has_entity returns false initially.
 */
TEST_F(SystemTest, HasEntityEmptySet) {
  EXPECT_FALSE(test_system.has_entity(1));
  EXPECT_FALSE(test_system.has_entity(invalid_entity));
}

/**
 * @brief Test that has_entity correctly identifies entities.
 *
 * @note This test is basic validation that has_entity works.
 * The entity management is handled by SystemManager in production.
 */
TEST_F(SystemTest, HasEntityAfterConstruction) {
  // System starts empty - no entities are added
  EXPECT_FALSE(test_system.has_entity(1));
  EXPECT_FALSE(test_system.has_entity(2));
  EXPECT_FALSE(test_system.has_entity(3));
}