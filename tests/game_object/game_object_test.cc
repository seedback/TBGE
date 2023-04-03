#include <gtest/gtest.h>
#include "src/game_object/game_object.hh"

/// @brief Testing that the GameObjects' id increments with each object
TEST(GameObject, IdIncrementation) {
  tbge::GameObject go0 = tbge::GameObject();
  tbge::GameObject go1 = tbge::GameObject();
  tbge::GameObject go2 = tbge::GameObject();

  EXPECT_EQ(go1.get_id(), go0.get_id() + 1);
  EXPECT_EQ(go2.get_id(), go1.get_id() + 1);
}