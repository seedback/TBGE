#ifndef TBGE_TEST_COMMAND_COMMAND_ACTION_PRINT_TEST_H_
#define TBGE_TEST_COMMAND_COMMAND_ACTION_PRINT_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/command/command.h"
#include "src/command/command_action/print.h"
#include "tests/mocks/mock_print.h"

TEST(PrintTest, Constructor) {
  tbge::PrintCommandAction print_action;
  tbge::Command command("test", &print_action);
  EXPECT_EQ(command.getCommandWord(), "test");
}

TEST(PrintTest, Execute) {
  MockPrint mock_print_action;
  tbge::Command command("test", &mock_print_action);
  std::vector<std::string> arguments = {"arg1", "arg2"};
  EXPECT_CALL(mock_print_action, execute(arguments));
  command.execute(arguments);
}

#endif // TBGE_TEST_COMMAND_TEST_COMMAND_ACTION_TEST_PRINT_TEST_H_
