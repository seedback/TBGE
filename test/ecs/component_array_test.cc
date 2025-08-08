#include "src/ecs/component_array.h"

#include <absl/log/initialize.h>
#include <absl/log/log_sink.h>
#include <absl/log/log_sink_registry.h>
#include <gtest/gtest.h>

#include "test/includes/test_log_sink.h"

struct TestComponent {
  int value;
  bool operator==(const TestComponent& other) const {
    return value == other.value;
  }
};

class ComponentArrayTest : public ::testing::Test {
 protected:
  using TestContext = ECS::Context<10, 5, uint8_t, uint8_t>;
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
  ECS::ComponentArray<TestContext, TestComponent> test_component_array;
  typename TestContext::Entity entity1 = 1;
  typename TestContext::Entity entity2 = 2;
  TestComponent component1{10};
  TestComponent component2{20};
};

/**
 * @brief Tests insertion and retrieval of a component in the ComponentArray.
 *
 * This test verifies that after inserting a TestComponent with a specific value
 * for a given entity, retrieving the component returns the correct value.
 * It ensures that the InsertData and GetData methods of the ComponentArray
 * work as expected for basic usage.
 */
TEST_F(ComponentArrayTest, InsertComponent) {
  TestComponent retrieved;

  test_component_array.InsertData(entity1, component1);
  EXPECT_EQ(test_component_array.get_size(), 1);

  test_component_array.InsertData(entity2, component1);
  EXPECT_EQ(test_component_array.get_size(), 2);
}

/**
 * @brief Tests that inserting a component for the same entity twice triggers an
 * error log and does not overwrite the original component.
 *
 * @details
 * This test verifies the following behavior:
 * - When a component is inserted for an entity that already has the same
 * component, an error log is generated.
 * - The severity of the log is `absl::LogSeverity::kError`.
 * - The log message contains "Component added to same entity more than once".
 * - The original component's value remains unchanged after attempting to insert
 * a new component for the same entity.
 */
TEST_F(ComponentArrayTest, OverwriteComponent) {
  test_component_array.InsertData(entity1, component1);

  test_component_array.InsertData(entity1, component2);

  test_sink_->TestLogs(
      absl::LogSeverity::kWarning,
      "Component of type \".*\" added to the same entity more than once.");

  TestComponent retrieved = test_component_array.GetData(entity1);
  EXPECT_EQ(retrieved, component1);
}

/**
 * @brief Tests the removal of a component from the ComponentArray.
 *
 * @details
 * This test inserts a component for a given entity, removes it,
 * and then asserts that accessing the removed component results in a program
 * death. It verifies that the ComponentArray correctly handles removal and
 * prevents access to deleted components.
 */
TEST_F(ComponentArrayTest, RemoveComponent) {
  test_component_array.InsertData(entity1, component1);
  EXPECT_EQ(test_component_array.get_size(), 1);
  test_component_array.RemoveData(entity1);
  EXPECT_EQ(test_component_array.get_size(), 0);
}

/**
 * @brief Tests that removing a non-existent component from the component array
 *        triggers a warning log.
 *
 * @details
 * This test verifies that when RemoveData is called with an ID that does not
 * exist in the component array, the system logs a warning indicating the
 * attempted removal of a non-existent component.
 */
TEST_F(ComponentArrayTest, RemoveNonExistentComponent) {
  test_component_array.RemoveData(255);

  test_sink_->TestLogs(absl::LogSeverity::kWarning,
                       "Removing non-existent component of type \".*\".");
}

/**
 * @brief Tests insertion and retrieval of a component in the ComponentArray.
 *
 * This test verifies that after inserting a TestComponent with a specific value
 * for a given entity, retrieving the component returns the correct value.
 * It ensures that the InsertData and GetData methods of the ComponentArray
 * work as expected for basic usage.
 */
TEST_F(ComponentArrayTest, GetComponent) {
  TestComponent retrieved;

  test_component_array.InsertData(entity1, component1);
  retrieved = test_component_array.GetData(entity1);
  EXPECT_EQ(retrieved, component1);

  test_component_array.InsertData(entity2, component1);
  retrieved = test_component_array.GetData(entity2);
  EXPECT_EQ(retrieved, component1);
}

/**
 * @brief Tests retrieval of a non-existent component from the component array.
 *
 * @details
 * This test verifies that attempting to get data for a component ID that does
 * not exist triggers a fatal check with the expected message.
 */
TEST_F(ComponentArrayTest, GettingNonexistentComponent) {
  EXPECT_DEATH(test_component_array.GetData(255),
               "Retrieving non-existent component of type \".*\".");
}