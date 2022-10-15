#include "gtest/gtest.h"

//#include <iostream>

// Demonstrate some basic assertions.
TEST(HelloTest1, BasicAssertions1) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}