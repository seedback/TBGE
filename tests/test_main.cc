#define GTEST_COLOR yes

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// #include "game_object/game_object_test.h"
// #include "global/global_test.h"
// #include "command/command_test.h"
// #include "command/command_action/print_test.h"
#include "component/component_test.h"
// #include "component/print_test.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}