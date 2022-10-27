/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include "lib/object/object.h"

#include "gtest/gtest.h"

TEST(ObjectClass, Constructor) {
  tbge::Object ob0;

  int id = ob0.get_id();

  EXPECT_EQ(ob0.get_name(), "Object_" + std::to_string(id));
  EXPECT_EQ(ob0.GetFullName(), "Object_" + std::to_string(id));
}

TEST(ObjectClass, ConstructorName) {
  tbge::Object ob0 = tbge::Object("object_name");

  EXPECT_EQ(ob0.get_name(), "object_name");
  EXPECT_EQ(ob0.GetFullName(), "object_name");
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

TEST(ObjectClass, SetGetName) {
  tbge::Object ob0;
  tbge::Object* ob0_p = &ob0;

  // Testing that set_name, sets the correct name and returns a reference to ob0
  // to allow for method-chaining.
  // Then that get_name returns the correct name
  EXPECT_EQ(ob0.set_name("Test Object").get_name(), "Test Object");
  // Testing same as above, but with empty name, meaning the name is sat to
  // default
  EXPECT_EQ(ob0.set_name("").get_name(), "Object_" + std::to_string(ob0.get_id()));
}

TEST(ObjectClass, GetFullName) {
  tbge::Object ob0;
  
  EXPECT_EQ(ob0.GetFullName(), "Object_" + std::to_string(ob0.get_id()));
  EXPECT_EQ(ob0.set_name("Test Object").GetFullName(), "Test Object");
}