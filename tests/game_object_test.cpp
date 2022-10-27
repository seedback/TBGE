/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */
#include <vector>
#include <iostream>

#include "lib/object/object.h"
#include "lib/game/game.h"
#include "lib/game_object/game_object.h"


#include "gtest/gtest.h"

class GameObjectClass : public ::testing::Test {
 protected:
  virtual void SetUp() {
    object1 = tbge::Object("test_object");

    parent1 = tbge::GameObject(&game, "parent1");
    parent2 = tbge::GameObject(&game, "parent2");
    child1 = tbge::GameObject(&game, "child1");
    child2 = tbge::GameObject(&game, "child2");
    child3 = tbge::GameObject(&game, "child3");
    child4 = tbge::GameObject(&game, "child4");
    child5 = tbge::GameObject(&game, "child5");

    children1 = std::vector<tbge::GameObject*>();
    children2 = std::vector<tbge::GameObject*>();

    children1.push_back(&child1);
    children1.push_back(&child2);
    children1.push_back(&child3);

    children2.push_back(&child4);
    children2.push_back(&child5);
  }

  tbge::Object object1;

  tbge::Game game;
  tbge::Game game2;

  tbge::GameObject parent1;
  tbge::GameObject parent2;
  tbge::GameObject child1;
  tbge::GameObject child2;
  tbge::GameObject child3;
  tbge::GameObject child4;
  tbge::GameObject child5;

  std::vector<tbge::GameObject*> children1;
  std::vector<tbge::GameObject*> children2;
};

TEST_F(GameObjectClass, DefaultConstructor) {
  tbge::GameObject go0 = tbge::GameObject();

  EXPECT_EQ(go0.get_id(), -1);
  EXPECT_EQ(go0.get_name(), "GameObject_dud");
  EXPECT_EQ(go0.GetGame(), nullptr);
  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectClass, CopyConstructor) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "game_object_0");
  tbge::GameObject goc = tbge::GameObject(go0);

  EXPECT_TRUE(go0 == goc);
}

TEST_F(GameObjectClass, ConstructorGame) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectClass, ConstructorGameName) {
  tbge::GameObject go0 = tbge::GameObject(&game, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectClass, ConstructorGameParent) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());

  EXPECT_EQ(parent1.GetChildById(go0.get_id()), &go0);
}

TEST_F(GameObjectClass, ConstructorGameParentName) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());

  EXPECT_EQ(parent1.GetChildById(go0.get_id()), &go0);
}

TEST_F(GameObjectClass, ConstructorGameChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game, children1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_EQ(go0.GetChildren(), children1);

  EXPECT_EQ(child1.GetParent(), &go0);
  EXPECT_EQ(child2.GetParent(), &go0);
  EXPECT_EQ(child3.GetParent(), &go0);
}

TEST_F(GameObjectClass, ConstructorGameChildrenName) {
  tbge::GameObject go0 = tbge::GameObject(&game, children1, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_EQ(go0.GetChildren(), children1);

  EXPECT_EQ(child1.GetParent(), &go0);
  EXPECT_EQ(child2.GetParent(), &go0);
  EXPECT_EQ(child3.GetParent(), &go0);
}

TEST_F(GameObjectClass, ConstructorGameParentChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_EQ(go0.GetChildren(), children1);

  EXPECT_EQ(parent1.GetChildById(go0.get_id()), &go0);

  EXPECT_EQ(child1.GetParent(), &go0);
  EXPECT_EQ(child2.GetParent(), &go0);
  EXPECT_EQ(child3.GetParent(), &go0);
}

TEST_F(GameObjectClass, FullConstructor) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.GetGame(), &game);
  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_EQ(go0.GetChildren(), children1);

  EXPECT_EQ(parent1.GetChildById(go0.get_id()), &go0);

  EXPECT_EQ(child1.GetParent(), &go0);
  EXPECT_EQ(child2.GetParent(), &go0);
  EXPECT_EQ(child3.GetParent(), &go0);
}

TEST_F(GameObjectClass, OperatorDoubleEqualsGameObject) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object1");
  tbge::GameObject go1 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object1");

  // Testing equal
  EXPECT_TRUE(go0 == go1);

  // Testing different game
  go1 = tbge::GameObject(&game2, &parent1, children1, "test_game_object1");
  EXPECT_FALSE(go0 == go1);
  // Testing different parent
  go1 = tbge::GameObject(&game, &parent2, children1, "test_game_object1");
  EXPECT_FALSE(go0 == go1);
  // Testing different children
  go1 = tbge::GameObject(&game, &parent1, children2, "test_game_object2");
  EXPECT_FALSE(go0 == go1);
  // Testing different name
  go1 = tbge::GameObject(&game, &parent1, children1, "test_game_object2");
  EXPECT_FALSE(go0 == go1);
}

TEST_F(GameObjectClass, OperatorDoubleEqualsObject) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "test_object");
  tbge::GameObject go1 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object1");

  EXPECT_TRUE(go0 == object1);
  EXPECT_FALSE(go1 == object1);
}

TEST_F(GameObjectClass, SetGetParent) {
  tbge::GameObject go0 = tbge::GameObject(&game,
                                          &parent1);
  parent1.AddChild(&go0);

  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_EQ(parent1.GetChildById(go0.get_id()), &go0);

  go0.SetParent(&parent2);
  EXPECT_EQ(go0.GetParent(), &parent2);
  EXPECT_EQ(parent2.GetChildById(go0.get_id()), &go0);
  EXPECT_NE(parent1.GetChildById(go0.get_id()), &go0);
  EXPECT_EQ(parent1.GetChildById(go0.get_id()), game.get_dud_game_object());
}

// Also tests RemoveParentActual
TEST_F(GameObjectClass, RemoveParent) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1);

  EXPECT_EQ(go0.GetParent(), &parent1);
  EXPECT_NE(go0.GetParent(), nullptr);

  go0.RemoveParent();

  EXPECT_EQ(go0.GetParent(), nullptr);
  EXPECT_NE(go0.GetParent(), &parent1);
}

TEST_F(GameObjectClass, SetChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.GetNumChildren(), 0);
  EXPECT_EQ(go0.GetChildByName("child1"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child2"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child3"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child4"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child5"), game.get_dud_game_object());

  go0.SetChildren(children1);

  EXPECT_EQ(go0.GetNumChildren(), 3);
  EXPECT_EQ(go0.GetChildByName("child1"), &child1);
  EXPECT_EQ(go0.GetChildByName("child2"), &child2);
  EXPECT_EQ(go0.GetChildByName("child3"), &child3);
  EXPECT_EQ(go0.GetChildByName("child4"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child5"), game.get_dud_game_object());

  go0.SetChildren(children2);

  EXPECT_EQ(go0.GetNumChildren(), 2);
  EXPECT_EQ(go0.GetChildByName("child1"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child2"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child3"), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByName("child4"), &child4);
  EXPECT_EQ(go0.GetChildByName("child5"), &child5);
}

TEST_F(GameObjectClass, GetNumChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.GetNumChildren(), 0);

  go0.AddChild(&child1);
  EXPECT_EQ(go0.GetNumChildren(), 1);

  go0.AddChild(&child2);
  go0.AddChild(&child3);
  EXPECT_EQ(go0.GetNumChildren(), 3);

  go0.RemoveChild(&child2);
  EXPECT_EQ(go0.GetNumChildren(), 2);
}

TEST_F(GameObjectClass, GetChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game);
  std::vector<tbge::GameObject*> expected = std::vector<tbge::GameObject*>();

  EXPECT_EQ(go0.GetChildren(), expected);

  expected.clear();
  expected.push_back(&child1);
  go0.AddChild(&child1);
  EXPECT_EQ(go0.GetChildren(), expected);

  expected.clear();
  expected.push_back(&child1);
  expected.push_back(&child2);
  expected.push_back(&child3);
  go0.AddChild(&child2);
  go0.AddChild(&child3);
  EXPECT_EQ(go0.GetChildren(), expected);

  expected.clear();
  expected.push_back(&child1);
  expected.push_back(&child3);
  go0.RemoveChild(&child2);
  EXPECT_EQ(go0.GetChildren(), expected);
}

TEST_F(GameObjectClass, GetChildByIndex) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.GetChildByIndex(0), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByIndex(1), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByIndex(2), game.get_dud_game_object());

  go0.AddChild(&child1);
  EXPECT_EQ(go0.GetChildByIndex(0), &child1);
  EXPECT_EQ(go0.GetChildByIndex(1), game.get_dud_game_object());
  EXPECT_EQ(go0.GetChildByIndex(2), game.get_dud_game_object());
}

TEST_F(GameObjectClass, AddChild) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.GetNumChildren(), 0);
  EXPECT_EQ(go0.GetChildren(), std::vector<tbge::GameObject*>());


  go0.AddChild(&child1);

  EXPECT_EQ(go0.GetNumChildren(), 1);
  EXPECT_EQ(go0.GetChildById(child1.get_id()), &child1);
  EXPECT_EQ(child1.GetParent(), &go0);

  go0.AddChild(&child2);
  go0.AddChild(&child3);

  EXPECT_EQ(go0.GetNumChildren(), 3);
  EXPECT_EQ(go0.GetChildren(), children1);
  EXPECT_EQ(child2.GetParent(), &go0);
  EXPECT_EQ(child3.GetParent(), &go0);

  // Checking that a duplicate does not add another instance of the same
  // child's pointer
  go0.AddChild(&child1);

  EXPECT_EQ(go0.GetNumChildren(), 3);
  EXPECT_EQ(go0.GetChildren(), children1);
  EXPECT_EQ(child1.GetParent(), &go0);
}

// // TEST_F(GameObjectClass, GetChildByIndex) {
// //   tbge::GameObject go0 = tbge::GameObject(&game, &parent, children1,
// //                                           "game_object_0");

// // }
