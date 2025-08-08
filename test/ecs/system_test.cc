#include "src/ecs/system.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <iostream>
#include <set>

#include "src/ecs/context.h"
#include "test/includes/test_log_sink.h"

class SystemTest : public ::testing::Test {
 protected:
  using TestContext = ECS::Context<10, 5, uint8_t, uint8_t>;
  void SetUp() override {
    absl::SetStderrThreshold(absl::LogSeverityAtLeast::kFatal);
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_system = ECS::System<TestContext>();
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs();
  }

  std::unique_ptr<TestLogSink> test_sink_;
  ECS::System<TestContext> test_system;
  TestContext::Entity invalid_entity = TestContext::kMaxEntities - 2;
};

TEST_F(SystemTest, SetGetEntities) {
  std::set<TestContext::Entity> entities = {1, 2, 3};
  test_system.set_entities(entities);
  EXPECT_EQ(test_system.get_entities(), entities);
}

TEST_F(SystemTest, SetEntitiesOverwritesPrevious) {
  std::set<TestContext::Entity> first = {1, 2};
  std::set<TestContext::Entity> second = {3, 4};
  test_system.set_entities(first);
  EXPECT_EQ(test_system.get_entities(), first);
  test_system.set_entities(second);
  EXPECT_EQ(test_system.get_entities(), second);
}

TEST_F(SystemTest, GetEntitiesInitiallyEmpty) {
  EXPECT_TRUE(test_system.get_entities().empty());
}

TEST_F(SystemTest, SetEntitiesEmpty) {
  std::set<TestContext::Entity> entities = {1, 2, 3};
  test_system.set_entities(entities);
  EXPECT_FALSE(test_system.get_entities().empty());
  test_system.set_entities({});
  EXPECT_TRUE(test_system.get_entities().empty());
}

TEST_F(SystemTest, AddEntity) {
  std::set<TestContext::Entity> entities = {1, 2, 3};
  std::set<TestContext::Entity> entities2 = {1, 2, 3, 4};
  test_system.set_entities(entities);
  EXPECT_EQ(test_system.get_entities(), entities);
  test_system.add_entity(4);
  EXPECT_EQ(test_system.get_entities(), entities2);
}

TEST_F(SystemTest, HasEntity) {
  std::set<TestContext::Entity> entities = {1, 2, 3};
  test_system.set_entities(entities);
  EXPECT_EQ(test_system.get_entities(), entities);
  EXPECT_TRUE(test_system.has_entity(2));
  EXPECT_FALSE(test_system.has_entity(4));
}

TEST_F(SystemTest, RemoveEntity) {
  std::set<TestContext::Entity> entities = {1, 2, 3};
  std::set<TestContext::Entity> entities2 = {1, 3};
  test_system.set_entities(entities);
  EXPECT_EQ(test_system.get_entities(), entities);
  test_system.remove_entity(2);
  EXPECT_EQ(test_system.get_entities(), entities2);
}