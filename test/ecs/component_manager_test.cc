#include "src/ecs/component_manager.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <string>
#include <typeinfo>

#include "src/ecs/context.h"
#include "test/includes/test_log_sink.h"

struct ComponentTypeInt {
  int value;
};

struct ComponentTypeFloat {
  float value;
};

struct ComponentTypeString {
  std::string value;
};

class ComponentManagerTest : public ::testing::Test {
 protected:
  using TestContext = ECS::Context<uint8_t, uint8_t, 10, 5>;
  ComponentManagerTest() {}

  static void SetUpTestSuite() {}

  void SetUp() override {
    test_sink_ = std::make_unique<TestLogSink>();
    absl::AddLogSink(test_sink_.get());
    test_component_manager = ECS::ComponentManager<TestContext>();
    test_sink_->Clear();
  }

  void TearDown() override {
    absl::RemoveLogSink(test_sink_.get());
    test_sink_->TestNoLogs();
  }

  std::unique_ptr<TestLogSink> test_sink_;
  ECS::ComponentManager<TestContext> test_component_manager;
  typename TestContext::Entity entity1 = 1;
  const char* component_type_int_type_name = typeid(ComponentTypeInt).name();
  const char* component_type_float_type_name =
      typeid(ComponentTypeFloat).name();
  const char* component_type_string_type_name =
      typeid(ComponentTypeString).name();
};

TEST_F(ComponentManagerTest, RegisterComponentType) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.RegisterComponentType<ComponentTypeFloat>();
  test_component_manager.RegisterComponentType<ComponentTypeString>();

  EXPECT_TRUE(test_component_manager.get_component_types().contains(
      component_type_int_type_name));
  EXPECT_TRUE(test_component_manager.get_component_types().contains(
      component_type_float_type_name));
  EXPECT_TRUE(test_component_manager.get_component_types().contains(
      component_type_string_type_name));
}

TEST_F(ComponentManagerTest, RegisterComponentTypeMoreThanOnce) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Registering component type more than once. Component "
                       "type registered twice has typeid \"" +
                           std::string(component_type_int_type_name) +
                           "\". Operation ignored.");
}

TEST_F(ComponentManagerTest, GetComponentTypeId) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.RegisterComponentType<ComponentTypeFloat>();
  test_component_manager.RegisterComponentType<ComponentTypeString>();

  EXPECT_EQ(test_component_manager.GetComponentTypeId<ComponentTypeInt>(), 0);
  EXPECT_EQ(test_component_manager.GetComponentTypeId<ComponentTypeFloat>(), 1);
  EXPECT_EQ(test_component_manager.GetComponentTypeId<ComponentTypeString>(), 2);
}

TEST_F(ComponentManagerTest, GetComponentTypeOfNotRegisteredType) {
  EXPECT_DEATH(test_component_manager.GetComponentTypeId<ComponentTypeInt>(),
               "Component of type " +
                   std::string(component_type_int_type_name) +
                   " not registered before use.");
}

TEST_F(ComponentManagerTest, AddComponent) {
  // Register component types
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.RegisterComponentType<ComponentTypeFloat>();
  test_component_manager.RegisterComponentType<ComponentTypeString>();

  // Add components to the entity
  ComponentTypeInt int_component{42};
  ComponentTypeFloat float_component{3.14f};
  ComponentTypeString string_component{"Expected"};

  test_component_manager.AddComponent<ComponentTypeInt>(entity1, int_component);
  test_component_manager.AddComponent<ComponentTypeFloat>(entity1,
                                                          float_component);
  test_component_manager.AddComponent<ComponentTypeString>(entity1,
                                                           string_component);

  // Retrieve and check the components
  ComponentTypeInt retrieved_int =
      test_component_manager.GetComponent<ComponentTypeInt>(entity1);
  EXPECT_EQ(retrieved_int.value, 42);

  ComponentTypeFloat retrieved_float =
      test_component_manager.GetComponent<ComponentTypeFloat>(entity1);
  EXPECT_FLOAT_EQ(retrieved_float.value, 3.14f);

  ComponentTypeString retrieved_string =
      test_component_manager.GetComponent<ComponentTypeString>(entity1);
  EXPECT_STREQ(retrieved_string.value.c_str(), "Expected");
}

TEST_F(ComponentManagerTest, AddDuplicateComponent) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();

  ComponentTypeInt int_component1{42};
  ComponentTypeInt int_component2{16};

  // Add first component
  test_component_manager.AddComponent<ComponentTypeInt>(entity1,
                                                        int_component1);

  // Add duplicate component (should overwrite or warn, depending on
  // implementation)
  test_component_manager.AddComponent<ComponentTypeInt>(entity1,
                                                        int_component2);
  test_sink_->TestLogs(
      absl::LogSeverity::kWarning,
      "Component of type \".*\" added to the same entity more than once.");

  // Check that the component hasn't changed
  ComponentTypeInt retrieved =
      test_component_manager.GetComponent<ComponentTypeInt>(entity1);
  EXPECT_EQ(retrieved.value, 42);
}

TEST_F(ComponentManagerTest, RemoveComponent) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.AddComponent<ComponentTypeInt>(entity1, {123});

  // Remove the component
  test_component_manager.RemoveComponent<ComponentTypeInt>(entity1);

  // After removal, trying to get the component should fail (death or exception)
  EXPECT_DEATH(test_component_manager.GetComponent<ComponentTypeInt>(entity1),
               "Retrieving non-existent component.");
}

TEST_F(ComponentManagerTest, RemoveComponentNotPresent) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  EXPECT_NO_THROW(
      test_component_manager.RemoveComponent<ComponentTypeInt>(entity1));
  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Removing non-existent component of type \".*\".");
}

TEST_F(ComponentManagerTest, HasComponent) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  test_component_manager.RegisterComponentType<ComponentTypeFloat>();
  EXPECT_FALSE(test_component_manager.HasComponent<ComponentTypeInt>(entity1));
  test_component_manager.AddComponent<ComponentTypeInt>(entity1, {99});
  EXPECT_TRUE(test_component_manager.HasComponent<ComponentTypeInt>(entity1));
  test_component_manager.RemoveComponent<ComponentTypeInt>(entity1);
  EXPECT_FALSE(test_component_manager.HasComponent<ComponentTypeInt>(entity1));
  EXPECT_FALSE(
      test_component_manager.HasComponent<ComponentTypeFloat>(entity1));
}

TEST_F(ComponentManagerTest, AddComponentWithoutRegistration) {
  test_component_manager.AddComponent<ComponentTypeInt>(entity1, {1});
  test_sink_->TestLogs(
      absl::LogSeverity::kWarning,
      "Component with typename \".*\" not registered before access.");
}

TEST_F(ComponentManagerTest, GetComponentForDifferentEntities) {
  test_component_manager.RegisterComponentType<ComponentTypeInt>();
  typename TestContext::Entity entity2 = 2;
  test_component_manager.AddComponent<ComponentTypeInt>(entity1, {10});
  test_component_manager.AddComponent<ComponentTypeInt>(entity2, {20});

  EXPECT_EQ(test_component_manager.GetComponent<ComponentTypeInt>(entity1).value,
  10);
  EXPECT_EQ(test_component_manager.GetComponent<ComponentTypeInt>(entity2).value,
  20);
}