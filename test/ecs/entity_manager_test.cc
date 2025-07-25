#include "src/ecs/entity_manager.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <bitset>
#include <iostream>
#include <memory>

#include "src/ecs/context.h"
#include "test/includes/test_log_sink.h"

class EntityManagerTest : public ::testing::Test {
 protected:
  using TestContext = ECS::Context<uint8_t, uint8_t, 10, 5>;
  void SetUp() override {
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_entity_manager = ECS::EntityManager<TestContext>();
  }

  void TearDown() override { absl::RemoveLogSink(test_sink_.get()); }

  std::unique_ptr<TestLogSink> test_sink_;
  ECS::EntityManager<TestContext> test_entity_manager;
  TestContext::Entity invalid_entity = TestContext::kMaxEntities - 2;
};

TEST_F(EntityManagerTest, CreateEntities) {
  EXPECT_EQ(test_entity_manager.CreateEntity(), 0);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 1);
  EXPECT_EQ(test_entity_manager.CreateEntity(), 1);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 2);
  EXPECT_EQ(test_entity_manager.CreateEntity(), 2);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 3);
  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 4);
  EXPECT_EQ(test_entity_manager.CreateEntity(), 4);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 5);
}

TEST_F(EntityManagerTest, CreateTooManyEntities) {
  for (int i = 0; i < TestContext::kMaxEntities; i++) {
    test_entity_manager.CreateEntity();
  }

  EXPECT_DEATH(
      test_entity_manager.CreateEntity(),
      ("Too many Entities were created. The maximum amount of Entities is " +
       std::to_string(TestContext::kMaxEntities) +
       ". This maximum can be adjusted in the Context.")
          .c_str());
}

TEST_F(EntityManagerTest, SetAndGetSignature) {
  TestContext::Entity entity1 = test_entity_manager.CreateEntity();
  TestContext::Entity entity2 = test_entity_manager.CreateEntity();
  TestContext::Entity entity3 = test_entity_manager.CreateEntity();

  EXPECT_EQ(test_entity_manager.GetSignature(entity1),
            TestContext::Signature());
  EXPECT_EQ(test_entity_manager.GetSignature(entity2),
            TestContext::Signature());
  EXPECT_EQ(test_entity_manager.GetSignature(entity3),
            TestContext::Signature());

  test_entity_manager.SetSignature(entity1, TestContext::Signature(1));
  test_entity_manager.SetSignature(entity2, TestContext::Signature(2));
  test_entity_manager.SetSignature(entity3, TestContext::Signature(3));

  EXPECT_EQ(test_entity_manager.GetSignature(entity1),
            TestContext::Signature(1));
  EXPECT_EQ(test_entity_manager.GetSignature(entity2),
            TestContext::Signature(2));
  EXPECT_EQ(test_entity_manager.GetSignature(entity3),
            TestContext::Signature(3));
}

TEST_F(EntityManagerTest, SetSignatureOfNonExistentEntity) {
  test_sink_->Clear();
  test_entity_manager.SetSignature(invalid_entity, TestContext::Signature(256));
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      ("Attempted to set signature of Entity out of range at Entity ID " +
       std::to_string(invalid_entity) + ". The current amount of Entities is " +
       std::to_string(test_entity_manager.get_current_entity_count()) +
       ". This error usually means that you're trying to access an Entity that "
       "has not yet been created or has been deleted.")
          .c_str());
}

TEST_F(EntityManagerTest, GetSignatureOfNonExistentEntity) {
  EXPECT_DEATH(
      test_entity_manager.GetSignature(invalid_entity),
      ("Attempted to get signature of Entity out of range at Entity ID " +
       std::to_string(invalid_entity) + ". The current amount of Entities is " +
       std::to_string(test_entity_manager.get_current_entity_count()) +
       ". This error usually means that you're trying to access an Entity that "
       "has not yet been created or has been deleted.")
          .c_str());
}

TEST_F(EntityManagerTest, DestroyEntity) {
  TestContext::Entity entity1 = test_entity_manager.CreateEntity();
  TestContext::Entity entity2 = test_entity_manager.CreateEntity();
  TestContext::Entity entity3 = test_entity_manager.CreateEntity();

  test_entity_manager.SetSignature(entity1, TestContext::Signature(1));
  test_entity_manager.SetSignature(entity2, TestContext::Signature(2));
  test_entity_manager.SetSignature(entity3, TestContext::Signature(3));

  test_entity_manager.DestroyEntity(entity2);

  EXPECT_EQ(test_entity_manager.GetSignature(entity1),
            TestContext::Signature(1));
  EXPECT_EQ(test_entity_manager.GetSignature(entity2),
            TestContext::Signature(0));
  EXPECT_EQ(test_entity_manager.GetSignature(entity3),
            TestContext::Signature(3));
  EXPECT_FALSE(test_entity_manager.HasEntity(entity2));
}

TEST_F(EntityManagerTest, DestroyEntityOutOfRange) {
  test_sink_->Clear();
  test_entity_manager.DestroyEntity(invalid_entity);
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      ("Attempted to destroy Entity out of range. The maximum amount "
       "of Entities is " +
       std::to_string(test_entity_manager.get_entity_id_counter()) +
       ". This maximum can be adjusted in the Context.")
          .c_str());
}

TEST_F(EntityManagerTest, HasEntity) {
  TestContext::Entity entity1 = test_entity_manager.CreateEntity();
  TestContext::Entity entity2 = test_entity_manager.CreateEntity();
  TestContext::Entity entity3 = test_entity_manager.CreateEntity();

  EXPECT_TRUE(test_entity_manager.HasEntity(entity1));
  EXPECT_TRUE(test_entity_manager.HasEntity(entity2));
  EXPECT_TRUE(test_entity_manager.HasEntity(entity3));
  EXPECT_FALSE(test_entity_manager.HasEntity(invalid_entity));

  test_entity_manager.DestroyEntity(entity2);

  EXPECT_TRUE(test_entity_manager.HasEntity(entity1));
  EXPECT_FALSE(test_entity_manager.HasEntity(entity2));
  EXPECT_TRUE(test_entity_manager.HasEntity(entity3));
  EXPECT_FALSE(test_entity_manager.HasEntity(invalid_entity));
}