// NOLINT(legal/copyright)
#include "src/lib/game_object/game_object.h"

#include "gtest/gtest.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  GameObject go;

  EXPECT_EQ(go.getId(), 23);


  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(TbgeTest, GameObjectGetId) {
  GameObject go;


  EXPECT_EQ(go.getId(), 23);
}
