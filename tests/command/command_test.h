#ifndef TBGE_TEST_COMMAND_COMMAND_TEST_H_
#define TBGE_TEST_COMMAND_COMMAND_TEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/command/command.h"
#include "src/command/command_action/command_action.h"

class MockCommandAction : public tbge::CommandAction {
 public:
  MOCK_METHOD(void, execute, (std::vector<std::string>& arguments), (override));
};

TEST(CommandTest, Constructor) {
  MockCommandAction mock_command_action;
  MockCommandAction* mock_command_action_pointer = &mock_command_action;
  tbge::Command command("test", &mock_command_action);
  EXPECT_EQ(command.getCommandWord(), "test");
}

TEST(CommandTest, EqualityOperator) {
  MockCommandAction mock_command_action;
  MockCommandAction* mock_command_action_pointer = &mock_command_action;
  tbge::Command command1("test", &mock_command_action);
  tbge::Command command2("test", &mock_command_action);
  EXPECT_EQ(command1, command2);
}

TEST(CommandTest, Destructor) {
  MockCommandAction mock_command_action;
  MockCommandAction* mock_command_action_pointer = &mock_command_action;
  tbge::Command* command = new tbge::Command("test", &mock_command_action);
  delete command;
}

TEST(CommandTest, Execute) {
  MockCommandAction mock_command_action;
  tbge::Command command("test", &mock_command_action);
  std::vector<std::string> arguments = {"arg1", "arg2"};
  EXPECT_CALL(mock_command_action, execute(arguments));
  command.execute(arguments);
}

TEST(CommandTest, GetCommandWord) {
  MockCommandAction mock_command_action;
  MockCommandAction* mock_command_action_pointer = &mock_command_action;
  tbge::Command command("test", &mock_command_action);
  EXPECT_EQ(command.getCommandWord(), "test");
}

#endif // TBGE_TEST_COMMAND_COMMAND_TEST_H_
