/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include "lib/game/game.h"

#include "gtest/gtest.h"

TEST(GameClass, Constructor) {
  tbge::Game g0;

  int id = g0.get_id();

  EXPECT_EQ(g0.get_name(), "Game_" + std::to_string(id));
  EXPECT_EQ(g0.GetFullName(), "Game_" + std::to_string(id));
  EXPECT_EQ(g0.GetClassName(), "Game");
}