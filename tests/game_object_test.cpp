#include <vector>

#include "lib/game_object/game_object.h"

#include "gtest/gtest.h"

class GameObjectClass : public ::testing::Test {
 protected:
  virtual void SetUp() {
    parent = tbge::GameObject(&game, "parent");
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

  tbge::GameObject parent = tbge::GameObject(&game, "parent");
  tbge::GameObject child1 = tbge::GameObject(&game, "child1");
  tbge::GameObject child2 = tbge::GameObject(&game, "child2");
  tbge::GameObject child3 = tbge::GameObject(&game, "child3");

  std::vector<tbge::GameObject*> children;
};

// Demonstrate some basic assertions.
TEST_F(GameObjectClass, FullConstructor) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent, children,
                                          "game_object_0");

  EXPECT_EQ(go0.game, &game);
  EXPECT_EQ(go0.get_parent(), &parent);
  EXPECT_EQ(go0.get_children(), children);

  std::cout << go0.get_child_by_index(0)->get_id() << std::endl;

  EXPECT_EQ(1,1);
}


TEST_F(GameObjectClass, SetParent) {
  tbge::GameObject go0 = tbge::GameObject(&game, &parent, std::vector<tbge::GameObject*>(),
                                          "game_object_0");
  std::cout << go0.get_child_by_index(0)->get_id() << std::endl;
}

// TEST_F(GameObjectClass, GetChildByIndex) {
//   tbge::GameObject go0 = tbge::GameObject(&game, &parent, children,
//                                           "game_object_0");

// }