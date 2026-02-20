#include "src/ecs/coordinator/coordinator.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include "test/includes/test_log_sink.h"

class DummyComponent {
 public:
  DummyComponent(int value = 15) { this->value = value; };
  int value;
};

class DummyComponent2 {
 public:
  DummyComponent2(int value = 15) { this->value = value; };
  int value;
};

class CoordinatorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    absl::SetStderrThreshold(absl::LogSeverityAtLeast::kFatal);
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());

    testing::internal::CaptureStdout();
    test_coordinator = std::make_unique<ecs::Coordinator>();
    testing::internal::GetCapturedStdout();
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs("Tested in TearDown");
  }

  std::unique_ptr<TestLogSink> test_sink_;
  std::unique_ptr<ecs::Coordinator> test_coordinator;
};

class DummySystem : public ecs::System {
 public:
  void Update() {
    // Dummy update logic
  }
};

class DummySystem2 : public ecs::System {
 public:
  void Update() {
    // Dummy update logic
  }
};

TEST_F(CoordinatorTest, Constructor) {
  testing::internal::CaptureStdout();
  ecs::Coordinator();
  std::string captured_stdout = testing::internal::GetCapturedStdout();
  
  test_sink_->TestLogs(absl::LogSeverity::kInfo, "The .*_DEBUG.* preprocessor definition has been detected.*");
}

TEST_F(CoordinatorTest, CreateEntity) {
  ecs::Entity entity1 = test_coordinator->CreateEntity();
  ecs::Entity entity2 = test_coordinator->CreateEntity();
  ecs::Entity entity3 = test_coordinator->CreateEntity();

  EXPECT_EQ(entity1, 0);
  EXPECT_EQ(entity2, 1);
  EXPECT_EQ(entity3, 2);
}

TEST_F(CoordinatorTest, RegisterComponentType) {
  ecs::ComponentManager* component_manager =
      test_coordinator->get_component_manager();

  EXPECT_EQ(component_manager->get_component_types().size(), 0)
      << "The ComponentManager should not have any ComponentTypes at "
         "initiation.";

  test_coordinator->RegisterComponentType<DummyComponent>();

  EXPECT_EQ(component_manager->get_component_types().size(), 1)
      << "The ComponentManager should have 1 ComponentTypeId.";

  test_coordinator->RegisterComponentType<DummyComponent2>();

  EXPECT_EQ(component_manager->get_component_types().size(), 2)
      << "The ComponentManager should have 2 ComponentTypeId.";
}

TEST_F(CoordinatorTest, RegisterSameComponentTypeMulipleTimes) {
  ecs::ComponentManager* component_manager =
      test_coordinator->get_component_manager();

  EXPECT_EQ(component_manager->get_component_types().size(), 0)
      << "The ComponentManager should not have any ComponentTypes at "
         "initiation.";

  test_coordinator->RegisterComponentType<DummyComponent>();
  test_sink_->TestNoLogs();

  EXPECT_EQ(component_manager->get_component_types().size(), 1)
      << "The ComponentManager should have 1 ComponentTypeId.";

  test_coordinator->RegisterComponentType<DummyComponent>();
  test_sink_->TestLogs(
      absl::LogSeverity::kWarning,
      "Registering component type more than once. Component type registered "
      "twice has typeid .*. Operation ignored.");

  EXPECT_EQ(component_manager->get_component_types().size(), 1)
      << "The ComponentManager should have 1 ComponentTypeId.";
}

TEST_F(CoordinatorTest, AddComponent) {
  DummyComponent component;
  test_coordinator->RegisterComponentType<DummyComponent>();
  ecs::Entity entity = test_coordinator->CreateEntity();

  ecs::Signature expected_signature;
  ecs::Signature signature =
      test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "Signature is expected to not be set yet.";

  auto& returned =
      test_coordinator->AddComponent<DummyComponent>(entity, component);
  EXPECT_EQ(&returned, test_coordinator.get())
      << "A reference to the Coordinator should be returned";

  expected_signature = ecs::Signature(0b1);
  signature = test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "The signature is expected to be 0b1 at this point. Representing the "
         "first Component ID";

  auto component_array = test_coordinator->get_component_manager()
                             ->get_component_array<DummyComponent>();
  EXPECT_EQ(component_array->get_size(), 1)
      << "Only one component should be in the array,";
}

TEST_F(CoordinatorTest, AddComponentsOfSameTypeMultipleTimes) {
  DummyComponent component;
  DummyComponent component2;
  test_coordinator->RegisterComponentType<DummyComponent>();
  ecs::Entity entity = test_coordinator->CreateEntity();

  ecs::Signature expected_signature;
  ecs::Signature signature =
      test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "Signature is expected to not be set yet.";

  test_coordinator->AddComponent<DummyComponent>(entity, component);
  test_coordinator->AddComponent<DummyComponent>(entity, component2);

  expected_signature = ecs::Signature(0b1);
  signature = test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "The signature is expected to be 0b1 at this point. Representing the "
         "first Component ID";

  auto component_array = test_coordinator->get_component_manager()
                             ->get_component_array<DummyComponent>();
  EXPECT_EQ(component_array->get_size(), 1)
      << "Only one component should be in the array,";

  test_sink_->TestLogs(
      absl::LogSeverity::kWarning,
      "Component of type '.*' added to the same entity more than once.");
}

TEST_F(CoordinatorTest, AddComponentsOfDifferentTypes) {
  DummyComponent component;
  DummyComponent2 component2;
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();
  ecs::Entity entity = test_coordinator->CreateEntity();

  ecs::Signature expected_signature;
  ecs::Signature signature =
      test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "Signature is expected to not be set yet.";

  test_coordinator->AddComponent<DummyComponent>(entity, component);
  test_coordinator->AddComponent<DummyComponent2>(entity, component2);

  signature = test_coordinator->get_entity_manager()->GetSignature(entity);
  expected_signature = ecs::Signature(0b11);
  EXPECT_EQ(signature, expected_signature)
      << "The signature is expected to be 0b11 at this point. Representing the "
         "first twoComponent ID";

  auto component_array = test_coordinator->get_component_manager()
                             ->get_component_array<DummyComponent>();
  auto component_array2 = test_coordinator->get_component_manager()
                              ->get_component_array<DummyComponent2>();
  EXPECT_EQ(component_array->get_size(), 1)
      << "Only one component should be in the array,";
  EXPECT_EQ(component_array2->get_size(), 1)
      << "Only one component should be in the array,";
}

TEST_F(CoordinatorTest, RemoveComponent) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  DummyComponent component;
  DummyComponent2 component2;
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();

  ecs::Signature expected_signature;
  ecs::Signature signature =
      test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "Signature is expected to not be set yet.";

  test_coordinator->AddComponent<DummyComponent>(entity, component);
  test_coordinator->AddComponent<DummyComponent2>(entity, component2);

  auto& returned = test_coordinator->RemoveComponent<DummyComponent>(entity);
  EXPECT_EQ(&returned, test_coordinator.get());

  auto component_array = test_coordinator->get_component_manager()
                             ->get_component_array<DummyComponent>();
  auto component_array2 = test_coordinator->get_component_manager()
                              ->get_component_array<DummyComponent2>();
  EXPECT_EQ(component_array->get_size(), 0);
  EXPECT_EQ(component_array2->get_size(), 1);

  expected_signature = ecs::Signature(0b10);
  signature = test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature);
}

TEST_F(CoordinatorTest, RemoveSameComponentTwice) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  DummyComponent component;
  test_coordinator->RegisterComponentType<DummyComponent>();

  ecs::Signature expected_signature;
  ecs::Signature signature =
      test_coordinator->get_entity_manager()->GetSignature(entity);
  EXPECT_EQ(signature, expected_signature)
      << "Signature is expected to not be set yet.";

  test_coordinator->AddComponent<DummyComponent>(entity, component);

  test_coordinator->RemoveComponent<DummyComponent>(entity);
  test_coordinator->RemoveComponent<DummyComponent>(entity);

  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Removing non-existent component of type '.*'.");
}

TEST_F(CoordinatorTest, RemoveUnregisteredComponent) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  DummyComponent component;
  test_coordinator->RemoveComponent<DummyComponent>(entity);
  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Component with typename \".*\" not registered before "
                       "access. Registering now.");
  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Removing non-existent component of type '.*'.");
}

TEST_F(CoordinatorTest, GetComponent) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  test_coordinator->RegisterComponentType<DummyComponent>();
  DummyComponent component(15);

  test_coordinator->AddComponent<DummyComponent>(entity, component);

  EXPECT_EQ(test_coordinator->GetComponent<DummyComponent>(entity).value,
            component.value);
}

TEST_F(CoordinatorTest, GetMultipleComponentsFromOneEntity) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();
  DummyComponent component(15);
  DummyComponent2 component2(15);

  test_coordinator->AddComponent<DummyComponent>(entity, component);
  test_coordinator->AddComponent<DummyComponent2>(entity, component2);

  EXPECT_EQ(test_coordinator->GetComponent<DummyComponent>(entity).value,
            component.value);
  EXPECT_EQ(test_coordinator->GetComponent<DummyComponent2>(entity).value,
            component2.value);
}

TEST_F(CoordinatorTest, GetSameComponentFromMultipleEntities) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  ecs::Entity entity2 = test_coordinator->CreateEntity();
  test_coordinator->RegisterComponentType<DummyComponent>();
  DummyComponent component(15);

  test_coordinator->AddComponent<DummyComponent>(entity, component);
  test_coordinator->AddComponent<DummyComponent>(entity2, component);

  EXPECT_EQ(test_coordinator->GetComponent<DummyComponent>(entity).value,
            component.value);
  EXPECT_EQ(test_coordinator->GetComponent<DummyComponent>(entity2).value,
            component.value);
}

TEST_F(CoordinatorTest, GetNonExistentComponent) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  test_coordinator->RegisterComponentType<DummyComponent>();
  DummyComponent component(15);

  EXPECT_DEATH(test_coordinator->GetComponent<DummyComponent>(entity),
               "Retrieving non-existent component of type '.*'.");
}

TEST_F(CoordinatorTest, GetComponentOfUnregisteredClass) {
  ecs::Entity entity = test_coordinator->CreateEntity();
  DummyComponent component(15);

  test_coordinator->AddComponent<DummyComponent>(entity, component);

  test_coordinator->GetComponent<DummyComponent>(entity);

  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Component with typename \".*\" not registered before "
                       "access. Registering now.");
}

TEST_F(CoordinatorTest, GetComponentTypeId) {
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();

  EXPECT_EQ(test_coordinator->GetComponentTypeId<DummyComponent>(), 0);
  EXPECT_EQ(test_coordinator->GetComponentTypeId<DummyComponent2>(), 1);
}

TEST_F(CoordinatorTest, GetComponentTypeIdOfUnregisteredComponentType) {
  EXPECT_DEATH(test_coordinator->GetComponentTypeId<DummyComponent>(),
               "Component of type .* not registered before use.");
  EXPECT_DEATH(test_coordinator->GetComponentTypeId<DummyComponent2>(),
               "Component of type .* not registered before use.");
}

TEST_F(CoordinatorTest, RegisterSystem) {
  auto system_manager = test_coordinator->get_system_manager();

  test_coordinator->RegisterSystem<DummySystem>();
  EXPECT_EQ(system_manager->get_systems().size(), 1);

  test_coordinator->RegisterSystem<DummySystem2>();
  EXPECT_EQ(system_manager->get_systems().size(), 2);
}

TEST_F(CoordinatorTest, RegisterSameSystemTwice) {
  test_coordinator->RegisterSystem<DummySystem>();
  test_coordinator->RegisterSystem<DummySystem>();

  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Registering system of typename '.*' more than once, "
                       "returning existing pointer");
}

TEST_F(CoordinatorTest, SetSystemSignature) {
  auto system_manager = test_coordinator->get_system_manager();

  test_coordinator->RegisterSystem<DummySystem>();
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();

  test_coordinator->SetSystemSignature<DummySystem>(
      ecs::Signature(0b10));

  EXPECT_EQ(system_manager->get_signatures().size(), 1);
}

TEST_F(CoordinatorTest, SetSystemSignatureOfUnregisteredSystem) {
  test_coordinator->RegisterComponentType<DummyComponent>();
  test_coordinator->RegisterComponentType<DummyComponent2>();

  test_coordinator->SetSystemSignature<DummySystem>(
      ecs::Signature(0b10));

  test_sink_->TestLogs(
      absl::LogSeverity::kError,
      "Attempted to set signature on system of typename \".*\" before it was "
      "registered. No signature will be registered, this may lead to bugs and "
      "errors down the line.");
}