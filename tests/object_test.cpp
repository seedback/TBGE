/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include "lib/object/object.h"

#include "gtest/gtest.h"

TEST(Object, IdsAssignedSequentially) {
  tbge::Object ob0;
  tbge::Object ob1;
  tbge::Object ob2;
  tbge::Object ob3;
  tbge::Object ob4;

  EXPECT_EQ(ob1.getId(), ob0.getId() + 1);
  EXPECT_EQ(ob2.getId(), ob1.getId() + 1);
  EXPECT_EQ(ob3.getId(), ob2.getId() + 1);
  EXPECT_EQ(ob4.getId(), ob3.getId() + 1);
}
