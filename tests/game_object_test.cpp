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
  EXPECT_EQ(go0.get_game(), nullptr);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());
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
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectClass, ConstructorGameName) {
  tbge::GameObject go0 = tbge::GameObject(&game, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());
}

TEST_F(GameObjectClass, ConstructorGameParent) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());

  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);
}

TEST_F(GameObjectClass, ConstructorGameParentName) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());

  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);
}

TEST_F(GameObjectClass, ConstructorGameChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game, children1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), children1);

  EXPECT_EQ(child1.get_parent(), &go0);
  EXPECT_EQ(child2.get_parent(), &go0);
  EXPECT_EQ(child3.get_parent(), &go0);
}

TEST_F(GameObjectClass, ConstructorGameChildrenName) {
  tbge::GameObject go0 = tbge::GameObject(&game, children1, "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), children1);

  EXPECT_EQ(child1.get_parent(), &go0);
  EXPECT_EQ(child2.get_parent(), &go0);
  EXPECT_EQ(child3.get_parent(), &go0);
}

TEST_F(GameObjectClass, ConstructorGameParentChildren) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1);

  EXPECT_EQ(go0.get_name(), "GameObject_" + std::to_string(go0.get_id()));
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(go0.get_children(), children1);

  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);

  EXPECT_EQ(child1.get_parent(), &go0);
  EXPECT_EQ(child2.get_parent(), &go0);
  EXPECT_EQ(child3.get_parent(), &go0);
}

TEST_F(GameObjectClass, FullConstructor) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object");

  EXPECT_EQ(go0.get_name(), "test_game_object");
  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(go0.get_children(), children1);

  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);

  EXPECT_EQ(child1.get_parent(), &go0);
  EXPECT_EQ(child2.get_parent(), &go0);
  EXPECT_EQ(child3.get_parent(), &go0);
}

TEST_F(GameObjectClass, OperatorDoubleEqualsGameObject) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object1");
  tbge::GameObject go1 = tbge::GameObject(&game, &parent1, children1,
                                          "test_game_object1");

  EXPECT_TRUE(go0 == go1);

  go1 = tbge::GameObject(&game, &parent1, children2, "test_game_object1");
  EXPECT_TRUE(go0 == go1);

  go1 = tbge::GameObject(&game2, &parent1, children1, "test_game_object1");
  EXPECT_FALSE(go0 == go1);
  go1 = tbge::GameObject(&game, &parent2, children1, "test_game_object1");
  EXPECT_FALSE(go0 == go1);
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
  parent1.add_child(&go0);

  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);

  go0.set_parent(&parent2);
  EXPECT_EQ(go0.get_parent(), &parent2);
  EXPECT_EQ(parent2.get_child_by_id(go0.get_id()), &go0);
  EXPECT_NE(parent1.get_child_by_id(go0.get_id()), &go0);
  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), game.get_dud_game_object());
}

TEST_F(GameObjectClass, AddChild) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  EXPECT_EQ(go0.get_num_children(), 0);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());


  go0.add_child(&child1);

  EXPECT_EQ(go0.get_num_children(), 1);
  EXPECT_EQ(go0.get_child_by_id(child1.get_id()), &child1);
  EXPECT_EQ(child1.get_parent(), &go0);

  go0.add_child(&child2);
  go0.add_child(&child3);

  EXPECT_EQ(go0.get_num_children(), 3);
  EXPECT_EQ(go0.get_children(), children1);
  EXPECT_EQ(child2.get_parent(), &go0);
  EXPECT_EQ(child3.get_parent(), &go0);

  // Checking that duplicate does not get added
  go0.add_child(&child1);

  EXPECT_EQ(go0.get_num_children(), 3);
  EXPECT_EQ(go0.get_children(), children1);
  EXPECT_EQ(child1.get_parent(), &go0);
}

// TEST_F(GameObjectClass, GetChildByIndex) {
//   tbge::GameObject go0 = tbge::GameObject(&game, &parent, children1,
//                                           "game_object_0");

// }
