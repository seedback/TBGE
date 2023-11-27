#ifndef TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_
#define TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/game_object/game_object.h"
#include "src/game_object/game_object_with_commands/game_object_with_commands.h"
#include "src/command/command.h"
#include "src/command/command_action/command_action.h"
#include "src/command/command_action/print.h"
#include "tests/mocks/mock_print.h"

class GameObjectWithCommandsTest : public ::testing::Test {
protected:
  std::string parent_name = "parent_object";
  std::string child1_name = "child1";
  std::string child2_name = "child2";
  tbge::GameObjectWithCommands parent{parent_name};
  tbge::GameObjectWithCommands child1{child1_name};
  tbge::GameObjectWithCommands child2{child1_name};
  std::vector<tbge::GameObject*> children = {&child1, &child2};
  MockPrint mock_print_action;
};

TEST_F(GameObjectWithCommandsTest, DefaultConstructorTest) {
  tbge::GameObjectWithCommands game_object;

  EXPECT_EQ(game_object.getName(), "GameObject_" + std::to_string(game_object.getId()));
  EXPECT_EQ(game_object.getFullName(), "GameObject_" + std::to_string(game_object.getId()));
  EXPECT_EQ(game_object.getParent(), nullptr);
  EXPECT_EQ(game_object.getChildren(), std::vector<tbge::GameObject*>());
  EXPECT_EQ(game_object.getCommands(), std::vector<tbge::Command>());
  EXPECT_EQ(game_object.getDescriptors(), std::vector<std::string>());
}

TEST_F(GameObjectWithCommandsTest, ConstructorWithNameDescriptorsCommandsParentChildrenTest) {
  std::string name = "test_object";
  std::vector<std::string> descriptors = {"descriptor1", "descriptor2"};
  std::vector<tbge::Command> commands = {tbge::Command("command1", new tbge::Print()), tbge::Command("command2", &mock_print_action)};

  tbge::GameObjectWithCommands game_object{name, descriptors, commands, &parent, children};

  EXPECT_EQ(game_object.getName(), name);
  EXPECT_EQ(game_object.getFullName(), parent_name + "." + name);
  EXPECT_EQ(game_object.getParent(), &parent);
  EXPECT_EQ(game_object.getChildren(), children);
  EXPECT_EQ(game_object.getCommands(), commands);
  EXPECT_EQ(game_object.getDescriptors(), descriptors);
}

TEST_F(GameObjectWithCommandsTest, DestructorTest) {
  std::string name = "test_object";
  std::vector<std::string> descriptors = {"descriptor1", "descriptor2"};
  std::vector<tbge::Command> commands = {tbge::Command("command1", &mock_print_action), tbge::Command("command2", &mock_print_action)};

  tbge::GameObjectWithCommands* game_object = new tbge::GameObjectWithCommands{name, descriptors, commands, &parent, children};

  EXPECT_EQ(game_object->getName(), name);
  EXPECT_EQ(game_object->getFullName(), parent_name + "." + name);
  EXPECT_EQ(game_object->getParent(), &parent);
  EXPECT_EQ(game_object->getChildren(), children);
  EXPECT_EQ(game_object->getCommands(), commands);
  EXPECT_EQ(game_object->getDescriptors(), descriptors);

  delete game_object;
}

TEST_F(GameObjectWithCommandsTest, GetCommandsTest) {
  std::vector<tbge::Command> commands = {tbge::Command("command1", &mock_print_action), tbge::Command("command2", &mock_print_action)};

  tbge::GameObjectWithCommands game_object{"test_object", {}, commands};

  EXPECT_EQ(game_object.getCommands(), commands);
}

TEST_F(GameObjectWithCommandsTest, GetDescriptorsTest) {
  std::vector<std::string> descriptors = {"descriptor1", "descriptor2"};

  tbge::GameObjectWithCommands game_object{"test_object", descriptors};

  EXPECT_EQ(game_object.getDescriptors(), descriptors);
}

TEST_F(GameObjectWithCommandsTest, SetCommandsTest) {
  std::vector<tbge::Command> commands = {tbge::Command("command1", &mock_print_action), tbge::Command("command2", &mock_print_action)};

  tbge::GameObjectWithCommands game_object{"test_object", {}, commands};

  EXPECT_EQ(game_object.getCommands(), commands);

  commands = {tbge::Command("command3", &mock_print_action), tbge::Command("command4", &mock_print_action)};

  game_object.setCommands(commands);

  EXPECT_EQ(game_object.getCommands(), commands);
}

TEST_F(GameObjectWithCommandsTest, SetDescriptorsTest) {
  std::vector<std::string> descriptors = {"descriptor1", "descriptor2"};

  tbge::GameObjectWithCommands game_object{"test_object", descriptors};

  EXPECT_EQ(game_object.getDescriptors(), descriptors);

  descriptors = {"descriptor3", "descriptor4"};

  game_object.setDescriptors(descriptors);

  EXPECT_EQ(game_object.getDescriptors(), descriptors);
}



#endif  // TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_COMMANDS_GAME_OBJECT_WITH_COMMANDS_H_