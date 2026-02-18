#include "src/ecs/entity_manager/entity_manager.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <bitset>
#include <iostream>
#include <memory>

#include "src/ecs/context/context.h"
#include "test/includes/test_log_sink.h"

class EntityManagerTest : public ::testing::Test {
 protected:
  using TestContext = ECS::Context<10, 5, uint8_t, uint8_t>;;
  void SetUp() override {
    absl::SetStderrThreshold(absl::LogSeverityAtLeast::kFatal);
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_entity_manager = ECS::EntityManager<TestContext>();
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs();
  }

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

  EXPECT_DEATH(test_entity_manager.CreateEntity(),
               "Too many Entities were created. The maximum amount of Entities "
               "is .*. This maximum can be adjusted in the Context.");
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
  test_entity_manager.SetSignature(invalid_entity, TestContext::Signature(256));
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      "Attempted to set signature of Entity out of range at Entity ID .*. The "
      "current amount of Entities is .*. This error usually means that you're "
      "trying to access an Entity that has not yet been created or has been "
      "deleted.");
}

TEST_F(EntityManagerTest, GetSignatureOfNonExistentEntity) {
  EXPECT_DEATH(test_entity_manager.GetSignature(invalid_entity),
               "Attempted to get signature of Entity out of range at Entity ID "
               ".*. The current amount of Entities is .*. This error usually "
               "means that you're trying to access an Entity that has not yet "
               "been created or has been deleted.");
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
  test_entity_manager.DestroyEntity(invalid_entity);
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      "Attempted to destroy Entity out of range. The maximum amount of "
      "Entities is .*. This maximum can be adjusted in the Context.");
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

TEST_F(EntityManagerTest, SetSignature) {
  // Create an entity
  TestContext::Entity entity = test_entity_manager.CreateEntity();

  // Initially, the signature should be default constructed (0)
  EXPECT_EQ(test_entity_manager.GetSignature(entity), TestContext::Signature());

  // Set a new signature and verify it is updated
  TestContext::Signature new_signature(0b101);
  test_entity_manager.SetSignature(entity, new_signature);
  EXPECT_EQ(test_entity_manager.GetSignature(entity), new_signature);
}

TEST_F(EntityManagerTest, SetGetSignatureUpdatesSignatureCorrectly) {
  // Create an entity
  TestContext::Entity entity = test_entity_manager.CreateEntity();

  // Initially, the signature should be default constructed (0)
  EXPECT_EQ(test_entity_manager.GetSignature(entity), TestContext::Signature());

  // Set a new signature and verify it is updated
  TestContext::Signature new_signature(1);
  test_entity_manager.SetSignature(entity, new_signature);
  EXPECT_EQ(test_entity_manager.GetSignature(entity), new_signature);

  // Set another signature and verify update
  TestContext::Signature another_signature(2);
  test_entity_manager.SetSignature(entity, another_signature);
  EXPECT_EQ(test_entity_manager.GetSignature(entity), another_signature);
}

TEST_F(EntityManagerTest, SetGetSignatureDoesNotAffectOtherEntities) {
  // Create two entities
  TestContext::Entity entity1 = test_entity_manager.CreateEntity();
  TestContext::Entity entity2 = test_entity_manager.CreateEntity();

  // Set signature for entity1
  TestContext::Signature signature1(1);
  test_entity_manager.SetSignature(entity1, signature1);

  // Set signature for entity2
  TestContext::Signature signature2(2);
  test_entity_manager.SetSignature(entity2, signature2);

  // Verify signatures are independent
  EXPECT_EQ(test_entity_manager.GetSignature(entity1), signature1);
  EXPECT_EQ(test_entity_manager.GetSignature(entity2), signature2);
}

TEST_F(EntityManagerTest, SetSignatureOnEntityOutOfRange) {
  TestContext::Signature signature1(1);
  test_entity_manager.SetSignature(invalid_entity, signature1);
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      "Attempted to set signature of Entity out of range at Entity ID .+. The "
      "current amount of Entities is .+. This error usually means that you're "
      "trying to access an Entity that has not yet been created or has been "
      "deleted.");
}

TEST_F(EntityManagerTest, GetSignatureOnEntityOutOfRange) {
  TestContext::Signature signature1(1);
  EXPECT_DEATH(test_entity_manager.GetSignature(invalid_entity),
               "Attempted to get signature of Entity out of range at Entity ID "
               ".+. The current amount of Entities is .+. This error usually "
               "means that you're trying to access an Entity that has not yet "
               "been created or has been deleted.");
}

TEST_F(EntityManagerTest, GetCurrentEntityCountReturnsCorrectCount) {
  // Initially, no entities
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 0);

  // Create entities and check count
  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 1);

  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 2);

  // Destroy one entity and check count
  test_entity_manager.DestroyEntity(0);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 1);

  // Destroy another entity and check count
  test_entity_manager.DestroyEntity(1);
  EXPECT_EQ(test_entity_manager.get_current_entity_count(), 0);
}

TEST_F(EntityManagerTest, GetEntityIdCounterIncrementsCorrectly) {
  // The entity ID counter should start at 0
  EXPECT_EQ(test_entity_manager.get_entity_id_counter(), 0);

  // Create entities and check counter
  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_entity_id_counter(), 1);

  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_entity_id_counter(), 2);

  // Destroying entities should not decrease the counter
  test_entity_manager.DestroyEntity(0);
  EXPECT_EQ(test_entity_manager.get_entity_id_counter(), 2);

  // Creating another entity should not increment the counter as we have an
  // available entity ID stored
  test_entity_manager.CreateEntity();
  EXPECT_EQ(test_entity_manager.get_entity_id_counter(), 2);
}
