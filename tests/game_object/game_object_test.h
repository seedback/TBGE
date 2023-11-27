#ifndef TBGE_TEST_GAME_OBJECT_GAME_OBJECT_TEST_H_
#define TBGE_TEST_GAME_OBJECT_GAME_OBJECT_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/game_object/game_object.h"

class GameObjectTest : public ::testing::Test {
protected:
  std::string parent_name = "parent_object";
  std::string child1_name = "child1";
  std::string child2_name = "child2";
  tbge::GameObject parent{parent_name};
  tbge::GameObject child1{child1_name};
  tbge::GameObject child2{child1_name};
  std::vector<tbge::GameObject*> children = {&child1, &child2};
};

TEST_F(GameObjectTest, DefaultConstructorTest) {
  tbge::GameObject game_object;

  EXPECT_EQ(game_object.getName(), "GameObject_" + std::to_string(game_object.getId()));
  EXPECT_EQ(game_object.getFullName(), "GameObject_" + std::to_string(game_object.getId()));
  EXPECT_EQ(game_object.getParent(), nullptr);
  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectTest, ConstructorWithNameTest) {
  std::string name = "test_object";

  tbge::GameObject game_object = tbge::GameObject(name);

  EXPECT_EQ(game_object.getName(), name);
  EXPECT_EQ(game_object.getFullName(), name);
  EXPECT_EQ(game_object.getParent(), nullptr);
  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectTest, ConstructorWithNameParentTest) {
  std::string name = "test_object";

  tbge::GameObject game_object{name, &parent};

  EXPECT_EQ(game_object.getName(), name);
  EXPECT_EQ(game_object.getFullName(), parent_name + "." + name);
  EXPECT_EQ(game_object.getParent(), &parent);
  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectTest, ConstructorWithNameChildrenTest) {
  std::string name = "test_object";

  tbge::GameObject game_object{name, children};

  EXPECT_EQ(game_object.getName(), name);
  EXPECT_EQ(game_object.getFullName(), name);
  EXPECT_EQ(game_object.getParent(), nullptr);
  EXPECT_EQ(game_object.getChildren(), children);
}

TEST_F(GameObjectTest, ConstructorWithNameParentChildrenTest) {
  std::string name = "test_object";

  tbge::GameObject game_object{name, &parent, children};

  EXPECT_EQ(game_object.getName(), name);
  EXPECT_EQ(game_object.getFullName(), parent_name + "." + name);
  EXPECT_EQ(game_object.getParent(), &parent);
  EXPECT_EQ(game_object.getChildren(), children);
}

TEST_F(GameObjectTest, CopyConstructorTest) {
  std::string name = "test_object";

  tbge::GameObject game_object{name, &parent, children};

  tbge::GameObject game_object_copy{game_object};

  EXPECT_EQ(game_object_copy.getName(), name);
  EXPECT_EQ(game_object_copy.getFullName(), parent_name + "." + name);
  EXPECT_EQ(game_object_copy.getParent(), &parent);
  EXPECT_EQ(game_object_copy.getChildren(), children);
}

TEST_F(GameObjectTest, DestructorTest) {
  tbge::GameObject* game_object = new tbge::GameObject{"test_object", &parent, children};

  delete game_object;

  EXPECT_EQ(parent.getChildren(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), nullptr);
}

TEST_F(GameObjectTest, GetIdTest) {
  tbge::GameObject game_object;
  tbge::GameObject game_object_2;

  EXPECT_GT(game_object_2.getId(), game_object.getId());
}

TEST_F(GameObjectTest, GetNameTest) {
  std::string name = "test_object";

  tbge::GameObject game_object{name};

  EXPECT_EQ(game_object.getName(), name);
}

TEST_F(GameObjectTest, GetParentTest) {
  tbge::GameObject game_object{"test_object", &parent};

  EXPECT_EQ(game_object.getParent(), &parent);
}

TEST_F(GameObjectTest, GetChildrenTest) {
  tbge::GameObject game_object{"test_object", children};

  EXPECT_EQ(game_object.getChildren(), children);
}

TEST_F(GameObjectTest, SetNameTest) {
  std::string name = "test_object";
  std::string new_name = "new_test_object";

  tbge::GameObject game_object{name};

  game_object.setName(new_name);

  EXPECT_EQ(game_object.getName(), new_name);
}

TEST_F(GameObjectTest, SetNameEmptyTest) {
  std::string name = "test_object";
  std::string new_name = "";

  tbge::GameObject game_object{name};

  game_object.setName(new_name);

  EXPECT_EQ(game_object.getName(), std::string(game_object.getClassName()) + "_" + std::to_string(game_object.getId()));
}

TEST_F(GameObjectTest, SetParentTest) {
  tbge::GameObject game_object{"test_object"};

  game_object.setParent(&parent);

  EXPECT_EQ(game_object.getParent(), &parent);
  EXPECT_EQ(parent.getChildren().size(), 1);
  EXPECT_EQ(parent.getChildren(), std::vector<tbge::GameObject*>{&game_object});
}

TEST_F(GameObjectTest, ChangeParentTest) {
  tbge::GameObject parent_2("parent_object_2");
  tbge::GameObject game_object("test_object");

  std::vector<tbge::GameObject*> parent_2_expected_children = {&game_object};

  game_object.setParent(&parent);
  game_object.setParent(&parent_2);

  EXPECT_EQ(game_object.getParent(), &parent_2);
  EXPECT_EQ(parent.getChildren(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(parent_2.getChildren(), parent_2_expected_children);
}

TEST_F(GameObjectTest, RemoveParentTest) {
  tbge::GameObject game_object{"test_object", &parent};

  game_object.removeParent();

  EXPECT_EQ(game_object.getParent(), nullptr);
  EXPECT_EQ(parent.getChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectTest, SetChildrenTest) {
  tbge::GameObject game_object{"test_object"};

  game_object.setChildren(children);

  EXPECT_EQ(game_object.getChildren(), children);
}

TEST_F(GameObjectTest, AddChildTest) {
  tbge::GameObject game_object{"test_object"};

  game_object.addChild(&child1);

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>{&child1});
  EXPECT_EQ(child1.getParent(), &game_object);
}

TEST_F(GameObjectTest, AddChildrenTest) {
  tbge::GameObject game_object{"test_object"};

  game_object.addChild(&child1);
  game_object.addChild(&child2);

  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, MoveChildrenTest) {
  tbge::GameObject game_object{"test_object"};
  tbge::GameObject game_object_2{"test_object_2"};

  game_object.addChild(&child1);
  game_object.addChild(&child2);

  game_object_2.addChild(&child1);
  game_object_2.addChild(&child2);

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(game_object_2.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object_2);
  EXPECT_EQ(child2.getParent(), &game_object_2);
}

TEST_F(GameObjectTest, RemoveChildrenTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChildren();

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), nullptr);
}

TEST_F(GameObjectTest, RemoveChildTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild(&child1);

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>{&child2});
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByIdTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild(child1.getId());

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>{&child2});
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByNameTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild(child1.getName());

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>{&child2});
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByInvalidIdTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild(-100);

  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByInvalidNameTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild("invalid_name");

  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByEmptyNameTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild("");

  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildByNullptrTest) {
  tbge::GameObject game_object{"test_object", children};

  game_object.removeChild(nullptr);

  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(child1.getParent(), &game_object);
  EXPECT_EQ(child2.getParent(), &game_object);
}

TEST_F(GameObjectTest, RemoveChildWhenParentHasNoChildrenTest) {
  tbge::GameObject game_object{"test_object"};

  game_object.removeChild(&child1);

  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>{});
  EXPECT_EQ(child1.getParent(), nullptr);
  EXPECT_EQ(child2.getParent(), nullptr);
}

#endif // TBGE_TEST_GAME_OBJECT_GAME_OBJECT_TEST_H_
