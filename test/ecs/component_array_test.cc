#include <gtest/gtest.h>
#include "src/ecs/component_array.h"

struct TestComponent {
  int value;
};

class ComponentArrayTest : public ::testing::Test {
protected:
  tbge::ComponentArray<TestComponent> componentArray;
};

TEST_F(ComponentArrayTest, InsertAndGetComponent) {
  size_t entity = 1;
  TestComponent comp{42};
  componentArray.InsertData(entity, comp);

  auto* retrieved = componentArray.GetData(entity);
  ASSERT_NE(retrieved, nullptr);
  EXPECT_EQ(retrieved->value, 42);
}

TEST_F(ComponentArrayTest, RemoveComponent) {
  size_t entity = 2;
  componentArray.InsertData(entity, {100});
  componentArray.RemoveData(entity);

  EXPECT_EQ(componentArray.GetData(entity), nullptr);
}

TEST_F(ComponentArrayTest, OverwriteComponent) {
  size_t entity = 3;
  componentArray.InsertData(entity, {10});
  componentArray.InsertData(entity, {20});

  auto* retrieved = componentArray.GetData(entity);
  ASSERT_NE(retrieved, nullptr);
  EXPECT_EQ(retrieved->value, 20);
}

TEST_F(ComponentArrayTest, RemoveNonexistentComponent) {
  size_t entity = 4;
  // Should not throw or crash
  componentArray.RemoveData(entity);
  EXPECT_EQ(componentArray.GetData(entity), nullptr);
}

TEST_F(ComponentArrayTest, ClearRemovesAllComponents) {
  componentArray.InsertData(1, {1});
  componentArray.InsertData(2, {2});
  componentArray.Clear();

  EXPECT_EQ(componentArray.GetData(1), nullptr);
  EXPECT_EQ(componentArray.GetData(2), nullptr);
}

TEST_F(ComponentArrayTest, GetDataReturnsNullptrForMissingEntity) {
  EXPECT_EQ(componentArray.GetData(999), nullptr);
}