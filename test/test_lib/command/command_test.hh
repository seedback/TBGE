

#ifndef TBGE_TEST_COMMAND_COMMAND_TEST_HH_  // NOLINT
#define TBGE_TEST_COMMAND_COMMAND_TEST_HH_

#include <iostream>

//#include "src/lib/command/command.hh"

//#include "include/gtest/gtest.h"




//// Testing that tbge::Command.command_word() works
////   both as an accessor and a mutator
//TEST(CommandTestSuite, Command__command_word) {
//  tbge::Command actual = tbge::Command();
//  actual.command_word("Test_word");
//  EXPECT_EQ(actual.command_word(), "TEST_WORD");
//}

//// Testing that tbge::Command.action() works
////   both as an accessor and a mutator
//TEST(CommandTestSuite, Command__action) {
//  tbge::Command actual = tbge::Command();

//  // Testing an invalid input
//  actual.action("Test_word");
//  EXPECT_EQ(actual.action(), "INVALID_ACTION");

//  // Testing valid actions, all-lower-case
//  actual.action("look");
//  EXPECT_EQ(actual.action(), "LOOK");
//  actual.action("inspect");
//  EXPECT_EQ(actual.action(), "INSPECT");
//  actual.action("go");
//  EXPECT_EQ(actual.action(), "GO");
//  actual.action("take");
//  EXPECT_EQ(actual.action(), "TAKE");
//  actual.action("use");
//  EXPECT_EQ(actual.action(), "USE");
//  actual.action("open");
//  EXPECT_EQ(actual.action(), "OPEN");
//  actual.action("close");
//  EXPECT_EQ(actual.action(), "CLOSE");

//  // Testing valid actions, all-mixed-case
//  actual.action("LoOk");
//  EXPECT_EQ(actual.action(), "LOOK");
//  actual.action("iNsPeCt");
//  EXPECT_EQ(actual.action(), "INSPECT");
//  actual.action("Go");
//  EXPECT_EQ(actual.action(), "GO");
//  actual.action("tAkE");
//  EXPECT_EQ(actual.action(), "TAKE");
//  actual.action("UsE");
//  EXPECT_EQ(actual.action(), "USE");
//  actual.action("oPeN");
//  EXPECT_EQ(actual.action(), "OPEN");
//  actual.action("ClOsE");
//  EXPECT_EQ(actual.action(), "CLOSE");

//  // Testing valid actions, all-upper-case
//  actual.action("LOOK");
//  EXPECT_EQ(actual.action(), "LOOK");
//  actual.action("INSPECT");
//  EXPECT_EQ(actual.action(), "INSPECT");
//  actual.action("GO");
//  EXPECT_EQ(actual.action(), "GO");
//  actual.action("TAKE");
//  EXPECT_EQ(actual.action(), "TAKE");
//  actual.action("USE");
//  EXPECT_EQ(actual.action(), "USE");
//  actual.action("OPEN");
//  EXPECT_EQ(actual.action(), "OPEN");
//  actual.action("CLOSE");
//  EXPECT_EQ(actual.action(), "CLOSE");

//  // Testing invalid actions, all contain special characters
//  actual.action("!LOOK");
//  EXPECT_NE(actual.action(), "LOOK");
//  actual.action("INS!PECT");
//  EXPECT_NE(actual.action(), "INSPECT");
//  actual.action("G2O");
//  EXPECT_NE(actual.action(), "GO");
//  actual.action("TA-KE");
//  EXPECT_NE(actual.action(), "TAKE");
//  actual.action("USE,");
//  EXPECT_NE(actual.action(), "USE");
//  actual.action("OPE/N");
//  EXPECT_NE(actual.action(), "OPEN");
//  actual.action("CLOS]E");
//  EXPECT_NE(actual.action(), "CLOSE");
//}

//TEST(CommandTestSuite, Command__EMPTY) {
//  // tbge::Command com = tbge::Command();

//  ASSERT_STREQ("test", "test");
//}


#endif // #ifndef TBGE_TEST_COMMAND_COMMAND_TEST_HH_  //NOLINT
