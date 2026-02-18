#include "src/ecs/system_manager/system_manager.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include "test/includes/test_log_sink.h"

class SystemManagerTest : public ::testing::Test {
 public:
  using TestContext = ECS::Context<10, 5, uint8_t, uint8_t>;;

 protected:
  void SetUp() override {
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs();
  }

  std::unique_ptr<TestLogSink> test_sink_;
  ECS::SystemManager<TestContext> test_system_manager;
};

class DummySystem : public ECS::System<SystemManagerTest::TestContext> {
 public:
  DummySystem() = default;
  void operator()(SystemManagerTest::TestContext&) {}
};

class DummySystem2 : public ECS::System<SystemManagerTest::TestContext> {
 public:
  DummySystem2() = default;
  void operator()(SystemManagerTest::TestContext&) {}
};

TEST_F(SystemManagerTest, RegisterSystem) {
  EXPECT_NE(test_system_manager.RegisterSystem<DummySystem>(), nullptr);
  EXPECT_EQ(test_system_manager.get_systems().size(), 1);
  EXPECT_NE(test_system_manager.RegisterSystem<DummySystem2>(), nullptr);
  EXPECT_EQ(test_system_manager.get_systems().size(), 2);
}

TEST_F(SystemManagerTest, RegisterSystemMoreThanOnce) {
  test_system_manager.RegisterSystem<DummySystem>();
  EXPECT_EQ(test_system_manager.get_systems().size(), 1);

  test_system_manager.RegisterSystem<DummySystem>();
  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Registering system of typename .* more than once, "
                       "returning existing pointer");
  EXPECT_EQ(test_system_manager.get_systems().size(), 1);
}

TEST_F(SystemManagerTest, SetSignature) {
  test_system_manager.RegisterSystem<DummySystem>();
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(2));

  EXPECT_EQ(test_system_manager.get_signatures().size(), 1);
  EXPECT_EQ(test_system_manager.get_signatures().begin()->second.to_ulong(), 2);

  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(4));

  EXPECT_EQ(test_system_manager.get_signatures().size(), 1);
  EXPECT_EQ(test_system_manager.get_signatures().begin()->second.to_ulong(), 4);
}

TEST_F(SystemManagerTest, SetSignatureOnUnregisteredSystem) {
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(2));
  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      "Attempted to set signature on system of typename .* before it was "
      "registered. No signature will be registered, this may lead to bugs and "
      "errors down the line.");
}
TEST_F(SystemManagerTest, EntityDestroyed) {
  // Register a dummy system and set a signature
  std::shared_ptr<DummySystem> system =
      test_system_manager.RegisterSystem<DummySystem>();
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(2));

  // Add some entities to the system's entity set
  system->add_entity_(1);
  system->add_entity_(2);
  system->add_entity_(3);

  // Destroy entity 2
  test_system_manager.EntityDestroyed(2);

  EXPECT_FALSE(system->has_entity(2))
      << "Entity 2 should be removedfrom the system's entities";
  EXPECT_TRUE(system->has_entity(1))
      << "Entity 1 should still be in the system's entities";
  EXPECT_TRUE(system->has_entity(3))
      << "Entity 3 should still be in the system's entities";
}

TEST_F(SystemManagerTest, EntityDestroyedOnEntityNotInSet) {
  test_system_manager.EntityDestroyed(1);

  EXPECT_TRUE(test_sink_->GetCapturedLogs().empty())
      << "No logs should be generated";
  EXPECT_EQ(test_system_manager.get_systems().size(), 0)
      << "No systems should be affected";
  EXPECT_EQ(test_system_manager.get_signatures().size(), 0)
      << "No signatures should be affected";
}

TEST_F(SystemManagerTest, EntityDestroyedWithNoSystemsRegistered) {
  test_system_manager.EntityDestroyed(42);
  // No logs expected
  EXPECT_TRUE(test_sink_->GetCapturedLogs().empty())
      << "No logs should be generated";
  EXPECT_EQ(test_system_manager.get_systems().size(), 0)
      << "No systems should be affected";
  EXPECT_EQ(test_system_manager.get_signatures().size(), 0)
      << "No signatures should be affected";
}

TEST_F(SystemManagerTest, EntityDestroyedWithMultipleSystems) {
  std::shared_ptr<DummySystem> system1 =
      test_system_manager.RegisterSystem<DummySystem>();
  std::shared_ptr<DummySystem2> system2 =
      test_system_manager.RegisterSystem<DummySystem2>();
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(0b01));
  test_system_manager.SetSignature<DummySystem2>(TestContext::Signature(0b10));

  system1->add_entity_(1);
  system1->add_entity_(2);
  system1->add_entity_(3);
  system2->add_entity_(4);
  system2->add_entity_(5);

  test_system_manager.EntityDestroyed(5);

  EXPECT_EQ(system1->get_entities().size(), 3)
      << "system1 should still have all its entities.";
  EXPECT_EQ(system2->get_entities().size(), 1)
      << "system2 should be lacking one entity";
  EXPECT_TRUE(system1->has_entity(1)) << "system 1 should have entity 1";
  EXPECT_TRUE(system1->has_entity(2)) << "system 1 should have entity 2";
  EXPECT_TRUE(system1->has_entity(3)) << "system 1 should have entity 3";
  EXPECT_FALSE(system1->has_entity(4)) << "system 1 should not have entity 4";
  EXPECT_FALSE(system1->has_entity(5)) << "system 1 should not have entity 5";

  EXPECT_FALSE(system2->has_entity(1)) << "system 2 should not have entity 1";
  EXPECT_FALSE(system2->has_entity(2)) << "system 2 should not have entity 2";
  EXPECT_FALSE(system2->has_entity(3)) << "system 2 should not have entity 3";
  EXPECT_TRUE(system2->has_entity(4)) << "system 2 should have entity 4";
  EXPECT_FALSE(system2->has_entity(5)) << "system 2 should not have entity 5";
}

TEST_F(SystemManagerTest, EntitySignatureChangedAddAndRemoveEntity) {
  // Register a dummy system and set a signature
  std::shared_ptr<DummySystem> system =
      test_system_manager.RegisterSystem<DummySystem>();
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(1));

  EXPECT_FALSE(system->has_entity(1))
      << "Entity 1 should not exist in the system initially.";
  EXPECT_FALSE(system->has_entity(1))
      << "Entity 2 should not exist in the system initially.";

  // Change signature of Entity 1 to match system's signature
  test_system_manager.EntitySignatureChanged(1, TestContext::Signature(1));

  EXPECT_TRUE(system->has_entity(1))
      << "Entity 1 should exist in the system after the EntitySignatureChanged "
         "call.";
  EXPECT_FALSE(system->has_entity(2))
      << "Entity 2 should still not exist in the even after the "
         "EntitySignatureChanged call.";

  // Change signature of Entity 2 to match system's signature
  test_system_manager.EntitySignatureChanged(2, TestContext::Signature(1));

  EXPECT_TRUE(system->has_entity(1))
      << "Entity 1 should still exist in the system.";
  EXPECT_TRUE(system->has_entity(2))
      << "Entity 2 should exist in the system after the EntitySignatureChanged "
         "call.";

  // Change signature of Entity 2 to no longer match system's signature
  test_system_manager.EntitySignatureChanged(2, TestContext::Signature(0));

  EXPECT_TRUE(system->has_entity(1))
      << "Entity 1 should still exist in the system.";
  EXPECT_FALSE(system->has_entity(2))
      << "Entity 2 should no longer exist in the system after the "
         "EntitySignatureChanged call.";

  // Change signature of Entity 2 to no longer match system's signature
  test_system_manager.EntitySignatureChanged(1, TestContext::Signature(0));

  EXPECT_FALSE(system->has_entity(1))
      << "Entity 1 should no longer exist in the system after the "
         "EntitySignatureChanged call.";
  EXPECT_FALSE(system->has_entity(2))
      << "Entity 2 should still not exist in the system.";
}

TEST_F(SystemManagerTest, EntitySignatureChangedNonMatchingSignature) {
  // Register a dummy system and set a signature
  std::shared_ptr<DummySystem> system =
      test_system_manager.RegisterSystem<DummySystem>();
  test_system_manager.SetSignature<DummySystem>(TestContext::Signature(1));

  EXPECT_FALSE(system->has_entity(1))
      << "Entity 1 should not exist in the system initially.";
  EXPECT_FALSE(system->has_entity(1))
      << "Entity 2 should not exist in the system initially.";

  // Change signature of Entity 1 to another signature that doesn't match the
  // system's signature.
  test_system_manager.EntitySignatureChanged(1, TestContext::Signature(2));

  EXPECT_FALSE(system->has_entity(1))
      << "Entity 2 should still not exist in the even after the "
         "EntitySignatureChanged call.";
  EXPECT_FALSE(system->has_entity(2))
      << "Entity 2 should still not exist in the even after the "
         "EntitySignatureChanged call.";
}

TEST_F(SystemManagerTest, EntitySignatureNoSystemsRegistered) {
  test_system_manager.EntitySignatureChanged(1, TestContext::Signature(1));
  // No logs expected
  EXPECT_TRUE(test_sink_->GetCapturedLogs().empty())
      << "No logs should be generated";
  EXPECT_EQ(test_system_manager.get_systems().size(), 0)
      << "No systems should be affected";
  EXPECT_EQ(test_system_manager.get_signatures().size(), 0)
      << "No signatures should be affected";
}
