#ifndef TBGE_TEST_COMPONENT_PRINT_TEST_H_
#define TBGE_TEST_COMPONENT_PRINT_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/component/component.h"
#include "src/component/print_component.h"

class PrintComponentTest : public ::testing::Test {
 protected:
  tbge::GameObject game_object{"test_object"};
};

TEST_F(PrintComponentTest, Constructor) {
  tbge::PrintComponent print_component{&game_object};
}

TEST_F(PrintComponentTest, Print) {
  tbge::PrintComponent print_component{&game_object};
  print_component.print("test", "test2");
}

#endif // TBGE_TEST_COMPONENT_PRINT_TEST_H_