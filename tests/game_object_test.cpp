/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */
#include <vector>
#include <iostream>

#include "lib/game_object/game_object.h"

#include "gtest/gtest.h"

class GameObjectClass : public ::testing::Test {
 protected:
  virtual void SetUp() {
    parent1 = tbge::GameObject(&game, "parent1");
    parent2 = tbge::GameObject(&game, "parent2");
    child1 = tbge::GameObject(&game, "child1");
    child2 = tbge::GameObject(&game, "child2");
    child3 = tbge::GameObject(&game, "child3");

    children = std::vector<tbge::GameObject*>();

    children.push_back(&child1);
    children.push_back(&child2);
    children.push_back(&child3);
  }

  virtual void TearDown() {
  }

  tbge::Game game;

  tbge::GameObject parent1 = tbge::GameObject(&game, "parent");
  tbge::GameObject parent2 = tbge::GameObject(&game, "parent");
  tbge::GameObject child1 = tbge::GameObject(&game, "child1");
  tbge::GameObject child2 = tbge::GameObject(&game, "child2");
  tbge::GameObject child3 = tbge::GameObject(&game, "child3");

  std::vector<tbge::GameObject*> children;
};

TEST_F(GameObjectClass, DefaultConstructor) {
  tbge::GameObject go0 = tbge::GameObject();

  EXPECT_EQ(go0.get_game(), nullptr);
  EXPECT_EQ(go0.get_parent(), nullptr);
  EXPECT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(go0.get_id(), -1);
  EXPECT_EQ(go0.get_name(), "GameObject_dud");
}

TEST_F(GameObjectClass, FullConstructor) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent1, children,
                                          "game_object_0");

  EXPECT_EQ(go0.get_game(), &game);
  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(go0.get_children(), children);
}


TEST_F(GameObjectClass, AddChild) {
  tbge::GameObject go0 = tbge::GameObject(&game);

  ASSERT_EQ(go0.get_num_children(), 0);
  ASSERT_EQ(go0.get_children(), std::vector<tbge::GameObject*>());

  go0.add_child(&child1);

  ASSERT_EQ(go0.get_num_children(), 1);
  ASSERT_EQ(go0.get_child_by_id(child1.get_id()), &child1);

  go0.add_child(&child2);
  go0.add_child(&child3);

  ASSERT_EQ(go0.get_num_children(), 3);
  ASSERT_EQ(go0.get_children(), children);
}

// TODO(Seedback): fix set_parent, possibly look in remove_child
TEST_F(GameObjectClass, SetParent) {
  tbge::GameObject go0 = tbge::GameObject(&game,
                                          &parent1);
  parent1.add_child(&go0);

  EXPECT_EQ(go0.get_parent(), &parent1);
  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), &go0);

  std::cout << "from here" << parent1.get_num_children() << std::endl;
  go0.set_parent(&parent2);
  std::cout << parent1.get_num_children() << std::endl;
  EXPECT_EQ(go0.get_parent(), &parent2);
  EXPECT_NE(parent1.get_child_by_id(go0.get_id()), &go0);
  EXPECT_EQ(parent1.get_child_by_id(go0.get_id()), game.get_dud_game_object());
}

// TEST_F(GameObjectClass, GetChildByIndex) {
//   tbge::GameObject go0 = tbge::GameObject(&game, &parent, children,
//                                           "game_object_0");

// }
