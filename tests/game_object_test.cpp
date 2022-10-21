#include <vector>

#include "lib/game_object/game_object.h"

#include "gtest/gtest.h"

// Demonstrate some basic assertions.
TEST(GameObjectClass, FullConstructor) {
  tbge::Game game = tbge::Game();
  
  tbge::GameObject parent = tbge::GameObject(&game, "parent");
  tbge::GameObject child1 = tbge::GameObject(&game, "child1");
  tbge::GameObject child2 = tbge::GameObject(&game, "child2");
  tbge::GameObject child3 = tbge::GameObject(&game, "child3");

  std::vector<tbge::GameObject*> children;
  children.push_back(&child1);
  children.push_back(&child2);
  children.push_back(&child3);

  tbge::GameObject go0 = tbge::GameObject(&game, &parent, children, "game_object_0");

  EXPECT_EQ(go0.game, &game);
  EXPECT_EQ(go0.get_parent(), &parent);
  EXPECT_EQ(go0.get_children(), children);

  EXPECT_EQ(1,1);
}
