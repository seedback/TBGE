#ifndef TBGE_TEST_COMPONENT_COMPONENT_TEST_H_
#define TBGE_TEST_COMPONENT_COMPONENT_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

#include "src/component/component.h"

class ComponentTest : public ::testing::Test {
  protected:
    void SetUp() override {
      delete tbge::Component::getRoot();
    }

    void printComponent(tbge::Component* component,
                        std::string custom_name = "") {
      if (custom_name != "") {
        std::cout << custom_name << std::endl;
      }
      std::cout << component->dbgToString() << std::endl;
    }
};

TEST_F(ComponentTest, DefaultConstructor) {
  // Test that the Fixture's SetUp() method functions correctly, only needed to
  // be done here once
  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  tbge::Component* root = new tbge::Component();

  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(1, root->getId());
  EXPECT_EQ(nullptr, root->getParent());
}

TEST_F(ComponentTest, DefaultConstructorThenDeleteAndConstructAgain) {
  // Test that the Fixture's SetUp() method functions correctly, only needed to
  // be done here once
  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  tbge::Component* root = new tbge::Component();

  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(1, root->getId());
  EXPECT_EQ(nullptr, root->getParent());

  delete root;

  EXPECT_EQ(nullptr, tbge::Component::getRoot());

  root = new tbge::Component();

  // Expect that the root component got reset after getting deleted
  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(1, root->getId());
  EXPECT_EQ(nullptr, root->getParent());
}

TEST_F(ComponentTest, DefaultConstructorTwice) {
  tbge::Component* root = new tbge::Component();

  EXPECT_THROW(new tbge::Component(), std::runtime_error);
}

TEST_F(ComponentTest, ConstructorWithParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(2, child->getId());
  EXPECT_EQ(root, child->getParent());
}

TEST_F(ComponentTest, ConstructorWithParentAndGrandparent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(2, child->getId());
  EXPECT_EQ(root, child->getParent());
  EXPECT_EQ(3, grandchild->getId());
  EXPECT_EQ(child, grandchild->getParent());
}

TEST_F(ComponentTest, CopyConstructor) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  tbge::Component* copy = new tbge::Component(*child);

  EXPECT_EQ(root, copy->getRoot());
  EXPECT_GT(copy->getId(), child->getId());
  EXPECT_EQ(root, copy->getParent());
}

TEST_F(ComponentTest, CopyConstructorWithChildAndParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, child->getRoot());
  EXPECT_GT(grandchild->getId(), child->getId());
  EXPECT_EQ(root, child->getParent());

  tbge::Component* copy = new tbge::Component(*child);

  EXPECT_EQ(root, copy->getRoot());
  EXPECT_GT(copy->getId(), child->getId());
  EXPECT_EQ(root, copy->getParent());
  EXPECT_EQ(child->getComponents().size(), copy->getComponents().size());

  tbge::Component* grandchild_copy = copy->getComponent();

  EXPECT_EQ(root, grandchild_copy->getRoot());
  EXPECT_EQ(copy, grandchild_copy->getParent());
  EXPECT_EQ(grandchild->getComponents().size(),
            grandchild_copy->getComponents().size());
  EXPECT_EQ(2, root->getComponents().size());
  EXPECT_EQ(1, child->getComponents().size());
  EXPECT_EQ(0, grandchild->getComponents().size());;
  EXPECT_EQ(1, copy->getComponents().size());
  EXPECT_EQ(0, grandchild_copy->getComponents().size());
}

TEST_F(ComponentTest, ConstructorWithNullParent) {
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
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  delete child1;

  EXPECT_EQ(0, root->getComponents().size());
  EXPECT_EQ(nullptr, child1->getParent());
}

TEST_F(ComponentTest, DestructorWithChildrenAndGrandchildren) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);
  tbge::Component* grandchild2 = new tbge::Component(child1);

  delete root;

  EXPECT_EQ(nullptr, tbge::Component::getRoot());
  EXPECT_EQ(nullptr, root->getRoot());
}

TEST_F(ComponentTest, GetRoot) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(root, root->getRoot());
  EXPECT_EQ(root, child->getRoot());
  EXPECT_EQ(root, grandchild->getRoot());
  bool is_component_base_class = std::is_same<decltype(root), decltype(root->getRoot())>::value;
  EXPECT_TRUE(is_component_base_class);
}

TEST_F(ComponentTest, GetId) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);
  tbge::Component* grandchild = new tbge::Component(child);

  EXPECT_EQ(1, root->getId());
  EXPECT_EQ(2, child->getId());
  EXPECT_EQ(3, grandchild->getId());
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

  EXPECT_EQ(child, root->getComponent(2));
}

TEST_F(ComponentTest, GetComponentByInvalidId) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child = new tbge::Component(root);

  EXPECT_EQ(nullptr, root->getComponent(0));
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

  std::vector<unsigned long long> ids = {2, 3, 4};
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

  std::vector<unsigned long long> ids = {5, 6, 7};
  std::vector<tbge::Component*> components = root->getComponents(ids);

  EXPECT_EQ(0, components.size());
}

TEST_F(ComponentTest, GetComponentsByInvalidIdsWithoutFilter) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<unsigned long long> ids = {5, 6, 7};
  std::vector<tbge::Component*> components = root->getComponents(ids, false);

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

// TODO: Update GetComponents tests when more sub classes exist to make sure it
//       works regardless of class
TEST_F(ComponentTest, GetAllComponents) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* child2 = new tbge::Component(root);
  tbge::Component* child3 = new tbge::Component(root);

  std::vector<tbge::Component*> components = root->getComponents();

  EXPECT_EQ(3, components.size());
  EXPECT_EQ(child1, components[0]);
  EXPECT_EQ(child2, components[1]);
  EXPECT_EQ(child3, components[2]);
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

  EXPECT_EQ(grandchild1, child1->addComponent(grandchild1));
  EXPECT_EQ(grandchild2, child1->addComponent(grandchild2));

  EXPECT_EQ(1, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());
  EXPECT_EQ(child1, grandchild2->getParent());

  tbge::Component* child2 = root->addComponent<tbge::Component>();
  tbge::Component* child3 = root->addComponent<tbge::Component>();

  EXPECT_EQ(typeid(tbge::Component*), typeid(child2));
  EXPECT_EQ(typeid(tbge::Component*), typeid(child3));

  EXPECT_EQ(3, root->getComponents().size());
  EXPECT_EQ(2, child1->getComponents().size());

  EXPECT_EQ(root, child1->getParent());
  EXPECT_EQ(child1, grandchild1->getParent());
  EXPECT_EQ(child1, grandchild2->getParent());
}

TEST_F(ComponentTest, AddComponentWithNullptr) {
  tbge::Component* root = new tbge::Component();

  EXPECT_EQ(0, root->getComponents().size());

  EXPECT_EQ(nullptr, root->addComponent(nullptr));

  EXPECT_EQ(0, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentToCurrentParent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_EQ(nullptr, root->addComponent(child1));

  EXPECT_EQ(1, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentToCurrentGranparent) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_NE(nullptr, root->addComponent(grandchild1));

  EXPECT_EQ(2, root->getComponents().size());
}

TEST_F(ComponentTest, AddComponentToDecendant) {
  tbge::Component* root = new tbge::Component();
  tbge::Component* child1 = new tbge::Component(root);
  tbge::Component* grandchild1 = new tbge::Component(child1);

  EXPECT_EQ(1, root->getComponents().size());

  EXPECT_EQ(nullptr, grandchild1->addComponent(root));

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

  EXPECT_TRUE(root->removeComponent(2));

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

  EXPECT_TRUE(root->removeComponent(2));

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

  std::cout << root->dbgToString() << std::endl;

  EXPECT_FALSE(root->isDescendantOf(nullptr));
}

#endif // TBGE_TEST_COMPONENT_COMPONENT_TEST_H_