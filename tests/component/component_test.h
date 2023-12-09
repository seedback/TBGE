#ifndef TBGE_TEST_COMPONENT_COMPONENT_TEST_H_
#define TBGE_TEST_COMPONENT_COMPONENT_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "src/component/component.h"

class ComponentTest : public ::testing::Test {
  protected:
    // ComponentTest() {
    //   // You can do set-up work for each test here.
    // }
  
    // ~ComponentTest() override {
    //   // You can do clean-up work that doesn't throw exceptions here.
    // }
  
    // // If the constructor and destructor are not enough for setting up
    // // and cleaning up each test, you can define the following methods:
    // void SetUp() override {
    //   // Code here will be called immediately after the constructor (right
    //   // before each test).
    //   root_ = new tbge::Component();
    //   child_ = new tbge::Component(root_);
    //   grandchild_ = new tbge::Component(child_);
    // }
  
    void SetUp() override {
      // Code here will be called immediately after each test (right
      // before the destructor).
      delete tbge::Component::getRoot();
      // root_ = new tbge::Component();
    }

    // void TearDown() override {
    //   delete tbge::Component::getRoot();
    // }

    void printComponent(tbge::Component* component) {
      std::cout << component->dbgToString() << std::endl;
    }
  
    // // Class members declared here can be used by all tests in the test suite
    // // for Foo.
    // tbge::Component* root_;
    // tbge::Component* child_;
    // tbge::Component* grandchild_;
};

TEST_F(ComponentTest, RootComponent) {
  // Test that the Fixture's SetUp() method functions correctly, only needed to
  // be done here once
  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  tbge::Component* root = new tbge::Component();

  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(0, root->getId());
  EXPECT_EQ(nullptr, root->getParent());

  delete root;

  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  root = new tbge::Component();

  // Expect that the root component got reset after getting deleted
  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(0, root->getId());
  EXPECT_EQ(nullptr, root->getParent());
}

TEST_F(ComponentTest, DefaultConstructorTwice) {
  tbge::Component* root = new tbge::Component();

  EXPECT_THROW(new tbge::Component(), std::runtime_error);
}

TEST_F(ComponentTest, NonRootComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(1, child->getId());
  EXPECT_EQ(root, child->getParent());

  delete root;

  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  root = new tbge::Component();
  child = new tbge::Component(root);

  // Expect that the root component got reset after getting deleted
  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(1, child->getId());
  EXPECT_EQ(root, child->getParent());
}

TEST_F(ComponentTest, CopyConstructor) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  tbge::Component* copy = new tbge::Component(*child);

  EXPECT_EQ(root, copy->getRoot());
  EXPECT_GT(copy->getId(), child->getId());
  EXPECT_EQ(root, copy->getParent());
}

TEST_F(ComponentTest, CopyConstructorWithParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_GT(grandchild->getId(), child->getId());
  EXPECT_EQ(root, child->getParent());
}

TEST_F(ComponentTest, CopyConstructorWithNullParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_THROW(new tbge::Component(nullptr), std::runtime_error);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_GT(grandchild->getId(), child->getId());
  EXPECT_EQ(root, child->getParent());
}

TEST_F(ComponentTest, Destructor) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_GT(grandchild->getId(), child->getId());
  EXPECT_EQ(root, child->getParent());

  delete root;

  EXPECT_EQ(nullptr, tbge::Component::getRoot());
}

TEST_F(ComponentTest, GetRoot) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(root, grandchild->getRoot());
}

TEST_F(ComponentTest, GetId) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(0, root->getId());
  EXPECT_EQ(1, child->getId());
  EXPECT_EQ(2, grandchild->getId());
}

TEST_F(ComponentTest, GetParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(nullptr, root->getParent());
  EXPECT_EQ(root, child->getParent());
  EXPECT_EQ(child, grandchild->getParent());
}

TEST_F(ComponentTest, GetComponentById) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(child, root->getComponent(1));
}

TEST_F(ComponentTest, GetComponentByInvalidId) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(nullptr, root->getComponent(2));
}

TEST_F(ComponentTest, GetComponentByType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(child, root->getComponent<tbge::Component>());
}

TEST_F(ComponentTest, GetComponentByInvalidType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(nullptr, root->getComponent<int>());
}

TEST_F(ComponentTest, GetComponentsByIds) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<unsigned long long> ids = {1, 2, 3};
  std::vector<tbge::Component*> components = root->getComponents(ids);

  EXPECT_EQ(3, components.size());
  EXPECT_EQ(child1, components[0]);
  EXPECT_EQ(child2, components[1]);
  EXPECT_EQ(child3, components[2]);
}

TEST_F(ComponentTest, GetComponentsByInvalidIds) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<unsigned long long> ids = {4, 5, 6};
  std::vector<tbge::Component*> components = root->getComponents(ids);

  EXPECT_EQ(3, components.size());
  EXPECT_EQ(nullptr, components[0]);
  EXPECT_EQ(nullptr, components[1]);
  EXPECT_EQ(nullptr, components[2]);
}

TEST_F(ComponentTest, GetComponentsByType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<tbge::Component*> components = root->getComponents<tbge::Component>();

  EXPECT_EQ(3, components.size());
  EXPECT_EQ(child1, components[0]);
  EXPECT_EQ(child2, components[1]);
  EXPECT_EQ(child3, components[2]);
}

TEST_F(ComponentTest, GetComponentsByInvalidType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<tbge::Component*> components = root->getComponents<int>();

  EXPECT_EQ(0, components.size());
}

TEST_F(ComponentTest, SetParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, child2->getParent());
  EXPECT_EQ(root, child3->getParent());

  tbge::Component* new_parent = new tbge::Component(root);

  child1->setParent(new_parent);
  child2->setParent(new_parent);
  child3->setParent(new_parent);

  EXPECT_EQ(new_parent, child1->getParent());
  EXPECT_EQ(new_parent, child2->getParent());
  EXPECT_EQ(new_parent, child3->getParent());
}

TEST_F(ComponentTest, SetParentWithNullptr) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, child2->getParent());
  EXPECT_EQ(root, child3->getParent());

  EXPECT_EQ(false, child1->setParent(nullptr));
  EXPECT_EQ(false, child2->setParent(nullptr));
  EXPECT_EQ(false, child3->setParent(nullptr));

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, child2->getParent());
  EXPECT_EQ(root, child3->getParent());
}

TEST_F(ComponentTest, SetParentWithChildComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, child->getParent());
  EXPECT_EQ(child, grandchild->getParent());

  EXPECT_FALSE(grandchild->setParent(child));
  // Test that you can't make a circular hierarchy by setting a child as a
  // parent of its parent
  EXPECT_FALSE(child->setParent(grandchild));

  EXPECT_EQ(root, child->getParent());
  EXPECT_EQ(child, grandchild->getParent());
}

TEST_F(ComponentTest, SetParentWithInvalidParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, child2->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());

  EXPECT_FALSE(child1->setParent(child1));
  EXPECT_FALSE(child2->setParent(child2));
  EXPECT_FALSE(grandchild1->setParent(grandchild1));
  EXPECT_FALSE(root->setParent(grandchild1));
  // Test that you can't make a circular hierarchy by setting a child as a
  // parent of its parent
  EXPECT_FALSE(child1->setParent(grandchild1));

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, child2->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());
}

TEST_F(ComponentTest, AddComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(root);
  tbge::Component* grandchild2 = new tbge::Component(root);

  EXPECT_EQ(3, root->getComponents().size());

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(root, grandchild1->getParent());
  EXPECT_EQ(root, grandchild2->getParent());

  EXPECT_NE(-1, child1->addComponent(grandchild1));
  EXPECT_NE(-1, child1->addComponent(grandchild2));

  EXPECT_EQ(1, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());
  EXPECT_EQ(child1, grandchild2->getParent());

  EXPECT_NE(-1, root->addComponent<tbge::Component>());
  EXPECT_NE(-1, root->addComponent<tbge::Component>());

  EXPECT_EQ(3, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());
  EXPECT_EQ(child1, grandchild2->getParent());
}

TEST_F(ComponentTest, AddComponentWithNullptr) {
  tbge::Component* root = new tbge::Component();

  EXPECT_EQ(0, root->getComponents().size());

  EXPECT_EQ(-1, root->addComponent(nullptr));

  EXPECT_EQ(0, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentWithInvalidParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_EQ(-1, root->addComponent(child1));

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentWithChildComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_NE(-1, root->addComponent(grandchild1));

  EXPECT_EQ(2, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentWithInvalidChildComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_EQ(-1, grandchild1->addComponent(root));

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_TRUE(root->removeComponent(child1));

  EXPECT_EQ(0, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentById) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_TRUE(root->removeComponent(1));

  EXPECT_EQ(0, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentByType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_TRUE(root->removeComponent<tbge::Component>());

  EXPECT_EQ(0, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentWithNullptr) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_FALSE(root->removeComponent(nullptr));

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentWithInvalidComponent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_FALSE(root->removeComponent(grandchild1));

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentWithInvalidType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_FALSE(root->removeComponent<int>());

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentAndGrandchildren) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);
  tbge::Component* grandchild2 = new tbge::Component(child1);

  EXPECT_EQ(2, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_TRUE(root->removeComponent(child1));

  EXPECT_EQ(1, root->getComponents().size());
  EXPECT_EQ(0, child1->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentAndGrandchildrenById) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);
  tbge::Component* grandchild2 = new tbge::Component(child1);

  EXPECT_EQ(2, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_TRUE(root->removeComponent(1));

  EXPECT_EQ(1, root->getComponents().size());
  EXPECT_EQ(0, child1->getComponents().size());
}

TEST_F(ComponentTest, RemoveComponentAndGrandchildrenByType) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);
  tbge::Component* grandchild2 = new tbge::Component(child1);

  EXPECT_EQ(2, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_TRUE(root->removeComponent<tbge::Component>());

  EXPECT_EQ(1, root->getComponents().size());
  EXPECT_EQ(0, child1->getComponents().size());
}

TEST_F(ComponentTest, IsDecendantOf) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);
  tbge::Component* grandchild2 = new tbge::Component(child1);

  // A component is not a decendant of itself
  EXPECT_FALSE(root->isDescendantOf(root));
  EXPECT_FALSE(child1->isDescendantOf(child1));
  EXPECT_FALSE(child2->isDescendantOf(child2));
  EXPECT_FALSE(grandchild1->isDescendantOf(grandchild1));
  EXPECT_FALSE(grandchild2->isDescendantOf(grandchild2));

  // A component is not a decendant of its siblings
  EXPECT_FALSE(child1->isDescendantOf(child2));
  EXPECT_FALSE(child2->isDescendantOf(child1));
  EXPECT_FALSE(grandchild2->isDescendantOf(grandchild1));
  EXPECT_FALSE(grandchild1->isDescendantOf(grandchild2));

  // A component is not a decendant of its decendants
  EXPECT_FALSE(root->isDescendantOf(child1));
  EXPECT_FALSE(root->isDescendantOf(child2));
  EXPECT_FALSE(root->isDescendantOf(grandchild1));
  EXPECT_FALSE(root->isDescendantOf(grandchild2));
  EXPECT_FALSE(child1->isDescendantOf(grandchild1));
  EXPECT_FALSE(child1->isDescendantOf(grandchild2));
  EXPECT_FALSE(child2->isDescendantOf(grandchild1));
  EXPECT_FALSE(child2->isDescendantOf(grandchild2));

  // A component is a decendant of its parent
  EXPECT_TRUE(child1->isDescendantOf(root));
  EXPECT_TRUE(child2->isDescendantOf(root));
  EXPECT_TRUE(grandchild1->isDescendantOf(child1));
  EXPECT_TRUE(grandchild2->isDescendantOf(child1));

  // A component is a decendant of its grandparent
  EXPECT_TRUE(grandchild1->isDescendantOf(root));
  EXPECT_TRUE(grandchild2->isDescendantOf(root));
}

TEST_F(ComponentTest, IsNotDecendantOfNullptr) {
  tbge::Component* root = new tbge::Component();

  EXPECT_FALSE(root->isDescendantOf(nullptr));
}

#endif // TBGE_TEST_COMPONENT_COMPONENT_TEST_H_