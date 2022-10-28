/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include "lib/object/object.h"

#include "gtest/gtest.h"

TEST(ObjectClass, Constructor) {
  tbge::Object ob0;

  int id = ob0.GetId();

  EXPECT_EQ(ob0.GetName(), "Object_" + std::to_string(id));
  EXPECT_EQ(ob0.GetFullName(), "Object_" + std::to_string(id));
}

TEST(ObjectClass, ConstructorName) {
  tbge::Object ob0 = tbge::Object("object_name");

  EXPECT_EQ(ob0.GetName(), "object_name");
  EXPECT_EQ(ob0.GetFullName(), "object_name");
}

TEST(ObjectClass, IdsAssignedSequentially) {
  tbge::Object ob0;
  tbge::Object ob1;
  tbge::Object ob2;
  tbge::Object ob3;
  tbge::Object ob4;

  EXPECT_EQ(ob1.GetId(), ob0.GetId() + 1);
  EXPECT_EQ(ob2.GetId(), ob1.GetId() + 1);
  EXPECT_EQ(ob3.GetId(), ob2.GetId() + 1);
  EXPECT_EQ(ob4.GetId(), ob3.GetId() + 1);
}

TEST(ObjectClass, SetGetName) {
  tbge::Object ob0;
  tbge::Object* ob0_p = &ob0;

  // Testing that SetName, sets the correct name and returns a reference to ob0
  // to allow for method-chaining.
  // Then that GetName returns the correct name
  EXPECT_EQ(ob0.SetName("Test Object").GetName(), "Test Object");
  // Testing same as above, but with empty name, meaning the name is sat to
  // default
  EXPECT_EQ(ob0.SetName("").GetName(), "Object_" + std::to_string(ob0.GetId()));
}

TEST(ObjectClass, GetFullName) {
  tbge::Object ob0;
  
  EXPECT_EQ(ob0.GetFullName(), "Object_" + std::to_string(ob0.GetId()));
  EXPECT_EQ(ob0.SetName("Test Object").GetFullName(), "Test Object");
}