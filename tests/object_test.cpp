/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include "lib/object/object.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ObjectClass, Constructor) {
  tbge::Object ob0;

  int id = ob0.get_id();

  EXPECT_EQ(ob0.get_name(), "Object_" + std::to_string(id));
  EXPECT_EQ(ob0.get_full_name(), "Object_" + std::to_string(id));
}

TEST(ObjectClass, IdsAssignedSequentially) {
  tbge::Object ob0;
  tbge::Object ob1;
  tbge::Object ob2;
  tbge::Object ob3;
  tbge::Object ob4;

  EXPECT_EQ(ob1.get_id(), ob0.get_id() + 1);
  EXPECT_EQ(ob2.get_id(), ob1.get_id() + 1);
  EXPECT_EQ(ob3.get_id(), ob2.get_id() + 1);
  EXPECT_EQ(ob4.get_id(), ob3.get_id() + 1);
}

TEST(ObjectClass, SetName) {
  tbge::Object ob0;
  tbge::Object* ob0_p = &ob0;

  EXPECT_EQ(&ob0.set_name("test_object"), &ob0);
  ob0.set_name("test_object");
  EXPECT_EQ(ob0.get_name(), "test_object");
  EXPECT_EQ(ob0.set_name("object_test").get_name(), "object_test");
}