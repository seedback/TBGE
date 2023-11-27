#ifndef TBGE_TEST_GLOBAL_GLOBAL_TEST_H_
#define TBGE_TEST_GLOBAL_GLOBAL_TEST_H_

#include <gtest/gtest.h>

#include "src/global/global.h"
#include "src/game_object/game_object.h"

class GlobalTest : public ::testing::Test, public tbge::global::Global {
 protected:
  void SetUp() override {
    tbge::global::Global::clearAliases();
  }
};

TEST_F(GlobalTest, RegisterGameObjectTest) {
  tbge::GameObject game_object;

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 1);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>{&game_object});
}

TEST_F(GlobalTest, UnregisterGameObjectTest) {
  tbge::GameObject* game_object = new tbge::GameObject{"test_object"};

  delete game_object;

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 0);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>());
}

TEST_F(GlobalTest, GetGameObjectByIdTest) {
  tbge::GameObject game_object{"test_object"};

  EXPECT_EQ(tbge::global::Global::getGameObject(game_object.getId()), &game_object);
}

TEST_F(GlobalTest, GetGameObjectByNameTest) {
  tbge::GameObject game_object{"test_object"};

  EXPECT_EQ(tbge::global::Global::getGameObject(game_object.getName()), &game_object);
}

TEST_F(GlobalTest, GetGameObjectByNameWithParentsTest) {
  tbge::GameObject granparent{"granparent"};
  tbge::GameObject parent{"parent", &granparent};
  tbge::GameObject game_object{"game_object", &parent};

  EXPECT_EQ(tbge::global::Global::getGameObject(game_object.getName()), &game_object);
  EXPECT_EQ(tbge::global::Global::getGameObject(parent.getName() + "." + game_object.getName()), &game_object);
  EXPECT_EQ(tbge::global::Global::getGameObject(granparent.getName() + "." + parent.getName() + "." + game_object.getName()), &game_object);
  EXPECT_EQ(tbge::global::Global::getGameObject(parent.getName()), &parent);
  EXPECT_EQ(tbge::global::Global::getGameObject(granparent.getName() + "." + parent.getName()), &parent);
  EXPECT_EQ(tbge::global::Global::getGameObject(granparent.getName()), &granparent);
}

TEST_F(GlobalTest, GetGameObjectByInvalidNameTest) {
  tbge::GameObject game_object{"test_object"};

  EXPECT_EQ(tbge::global::Global::getGameObject("invalid_name"), nullptr);
}

TEST_F(GlobalTest, GetAllGameObjectsWithNameTest) {
  tbge::GameObject game_object1{"test_object"};
  tbge::GameObject game_object2{"test_object"};

  std::vector<tbge::GameObject*> expected_game_objects = {&game_object1, &game_object2};

  EXPECT_EQ(tbge::global::Global::getAllGameObjectsWithName(game_object1.getName()), expected_game_objects);
}

TEST_F(GlobalTest, HasGameObjectByIdTest) {
  tbge::GameObject game_object{"test_object"};

  EXPECT_TRUE(tbge::global::Global::hasGameObject(game_object.getId()));
}

TEST_F(GlobalTest, HasGameObjectByNameTest) {
  tbge::GameObject game_object{"test_object"};

  EXPECT_TRUE(tbge::global::Global::hasGameObject(game_object.getName()));
}

TEST_F(GlobalTest, GetGameObjectByIdNullTest) {
  EXPECT_EQ(tbge::global::Global::getGameObject(0), nullptr);
}

TEST_F(GlobalTest, GetGameObjectByInvallidNameTest) {
  EXPECT_EQ(tbge::global::Global::getGameObject("invalid_name"), nullptr);
}

TEST_F(GlobalTest, HasGameObjectByIdNullTest) {
  EXPECT_FALSE(tbge::global::Global::hasGameObject(0));
}

TEST_F(GlobalTest, HasGameObjectByInvallidNameTest) {
  EXPECT_FALSE(tbge::global::Global::hasGameObject("invalid_name"));
}

TEST_F(GlobalTest, GetGameObjectsTest) {
  tbge::GameObject game_object1{"test_object1"};
  tbge::GameObject game_object2{"test_object2"};

  std::vector<tbge::GameObject*> expected_game_objects = {&game_object1, &game_object2};

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 2);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), expected_game_objects);
}

TEST_F(GlobalTest, GetGameObjectsEmptyTest) {
  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 0);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>());
}

TEST_F(GlobalTest, GetGameObjectsAfterDeleteTest) {
  tbge::GameObject* game_object = new tbge::GameObject{"test_object"};

  delete game_object;

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 0);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>());
}

TEST_F(GlobalTest, GetGameObjectsAfterDeleteOneTest) {
  tbge::GameObject* game_object1 = new tbge::GameObject{"test_object1"};
  tbge::GameObject* game_object2 = new tbge::GameObject{"test_object2"};

  delete game_object1;

  std::vector<tbge::GameObject*> expected_game_objects = {game_object2};

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 1);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), expected_game_objects);

  delete game_object2;

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 0);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>());
}

TEST_F(GlobalTest, GetGameObjectsAfterDeleteAllTest) {
  tbge::GameObject* game_object1 = new tbge::GameObject{"test_object1"};
  tbge::GameObject* game_object2 = new tbge::GameObject{"test_object2"};

  delete game_object1;
  delete game_object2;

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 0);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>());
}

TEST_F(GlobalTest, GetGameObjectsAfterDeleteAllAndAddTest) {
  tbge::GameObject* game_object1 = new tbge::GameObject{"test_object1"};
  tbge::GameObject* game_object2 = new tbge::GameObject{"test_object2"};

  delete game_object1;
  delete game_object2;

  tbge::GameObject game_object3{"test_object3"};

  EXPECT_EQ(tbge::global::Global::getGameObjects().size(), 1);
  EXPECT_EQ(tbge::global::Global::getGameObjects(), std::vector<tbge::GameObject*>{&game_object3});
}

TEST_F(GlobalTest, AddCommandWordAlias) {
  tbge::global::Global::addCommandWordAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias"), "test");
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test"), (std::vector<std::string>{"alias"}));
}

TEST_F(GlobalTest, AddCommandWordAliasMultiple) {
  tbge::global::Global::addCommandWordAlias("test", "alias1");
  tbge::global::Global::addCommandWordAlias("test", "alias2");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias1"), "test");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias2"), "test");
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test"), (std::vector<std::string>{"alias1", "alias2"}));
}

TEST_F(GlobalTest, AddCommandWordAliasMultipleCommands) {
  tbge::global::Global::addCommandWordAlias("test1", "alias1");
  tbge::global::Global::addCommandWordAlias("test2", "alias2");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias1"), "test1");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias2"), "test2");
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test1"), (std::vector<std::string>{"alias1"}));
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test2"), (std::vector<std::string>{"alias2"}));
}

TEST_F(GlobalTest, AddCommandWordAliasMultipleCommandsMultipleAliases) {
  tbge::global::Global::addCommandWordAlias("test1", "alias1");
  tbge::global::Global::addCommandWordAlias("test1", "alias2");
  tbge::global::Global::addCommandWordAlias("test2", "alias3");
  tbge::global::Global::addCommandWordAlias("test2", "alias4");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias1"), "test1");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias2"), "test1");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias3"), "test2");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias4"), "test2");
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test1"), (std::vector<std::string>{"alias1", "alias2"}));
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test2"), (std::vector<std::string>{"alias3", "alias4"}));
}

TEST_F(GlobalTest, AddCommandWordAliasMultipleCommandsMultipleAliasesMultipleTimes) {
  tbge::global::Global::addCommandWordAlias("test", "alias1");
  tbge::global::Global::addCommandWordAlias("test", "alias2");
  tbge::global::Global::addCommandWordAlias("test", "alias2");
  tbge::global::Global::addCommandWordAlias("test", "alias2");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias1"), "test");
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias2"), "test");
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases().at("test"), (std::vector<std::string>{"alias1", "alias2"}));
}

TEST_F(GlobalTest, GetCommandWordAliases) {
  tbge::global::Global::addCommandWordAlias("test1", "alias1");
  tbge::global::Global::addCommandWordAlias("test1", "alias2");
  tbge::global::Global::addCommandWordAlias("test2", "alias3");
  tbge::global::Global::addCommandWordAlias("test2", "alias4");

  std::map<std::string, std::vector<std::string>> expected_command_aliases = {
    {"test1", {"alias1", "alias2"}},
    {"test2", {"alias3", "alias4"}}
  };

  EXPECT_EQ(tbge::global::Global::getCommandWordAliases(), expected_command_aliases);
}

TEST_F(GlobalTest, GetCommandWordAliasesEmpty) {
  EXPECT_EQ(tbge::global::Global::getCommandWordAliases(), (std::map<std::string, std::vector<std::string>>()));
}

TEST_F(GlobalTest, GetCommandWordFromAlias) {
  tbge::global::Global::addCommandWordAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias"), "test");
}

TEST_F(GlobalTest, GetCommandWordFromAliasEmpty) {
  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("alias"), "");
}

TEST_F(GlobalTest, GetCommandWordFromAliasInvalidAlias) {
  tbge::global::Global::addCommandWordAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getCommandWordFromAlias("invalid_alias"), "");
}

TEST_F(GlobalTest, AddDescriptorAlias) {
  tbge::global::Global::addDescriptorAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias"), "test");
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test"), (std::vector<std::string>{"alias"}));
}

TEST_F(GlobalTest, AddDescriptorAliasMultiple) {
  tbge::global::Global::addDescriptorAlias("test", "alias1");
  tbge::global::Global::addDescriptorAlias("test", "alias2");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias1"), "test");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias2"), "test");
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test"), (std::vector<std::string>{"alias1", "alias2"}));
}

TEST_F(GlobalTest, AddDescriptorAliasMultipleCommands) {
  tbge::global::Global::addDescriptorAlias("test1", "alias1");
  tbge::global::Global::addDescriptorAlias("test2", "alias2");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias1"), "test1");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias2"), "test2");
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test1"), (std::vector<std::string>{"alias1"}));
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test2"), (std::vector<std::string>{"alias2"}));
}

TEST_F(GlobalTest, AddDescriptorAliasMultipleCommandsMultipleAliases) {
  tbge::global::Global::addDescriptorAlias("test1", "alias1");
  tbge::global::Global::addDescriptorAlias("test1", "alias2");
  tbge::global::Global::addDescriptorAlias("test2", "alias3");
  tbge::global::Global::addDescriptorAlias("test2", "alias4");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias1"), "test1");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias2"), "test1");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias3"), "test2");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias4"), "test2");
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test1"), (std::vector<std::string>{"alias1", "alias2"}));
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test2"), (std::vector<std::string>{"alias3", "alias4"}));
}

TEST_F(GlobalTest, AddDescriptorAliasMultipleCommandsMultipleAliasesMultipleTimes) {
  tbge::global::Global::addDescriptorAlias("test", "alias1");
  tbge::global::Global::addDescriptorAlias("test", "alias2");
  tbge::global::Global::addDescriptorAlias("test", "alias2");
  tbge::global::Global::addDescriptorAlias("test", "alias2");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias1"), "test");
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias2"), "test");
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases().at("test"), (std::vector<std::string>{"alias1", "alias2"}));
}

TEST_F(GlobalTest, GetDescriptorAliases) {
  tbge::global::Global::addDescriptorAlias("test1", "alias1");
  tbge::global::Global::addDescriptorAlias("test1", "alias2");
  tbge::global::Global::addDescriptorAlias("test2", "alias3");
  tbge::global::Global::addDescriptorAlias("test2", "alias4");

  std::map<std::string, std::vector<std::string>> expected_descriptor_aliases = {
    {"test1", {"alias1", "alias2"}},
    {"test2", {"alias3", "alias4"}}
  };

  EXPECT_EQ(tbge::global::Global::getDescriptorAliases(), expected_descriptor_aliases);
}

TEST_F(GlobalTest, GetDescriptorAliasesEmpty) {
  EXPECT_EQ(tbge::global::Global::getDescriptorAliases(), (std::map<std::string, std::vector<std::string>>()));
}

TEST_F(GlobalTest, GetDescriptorFromAlias) {
  tbge::global::Global::addDescriptorAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias"), "test");
}

TEST_F(GlobalTest, GetDescriptorFromAliasEmpty) {
  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("alias"), "");
}

TEST_F(GlobalTest, GetDescriptorFromAliasInvalidAlias) {
  tbge::global::Global::addDescriptorAlias("test", "alias");

  EXPECT_EQ(tbge::global::Global::getDescriptorFromAlias("invalid_alias"), "");
}

#endif // TBGE_TEST_GLOBAL_GLOBAL_TEST_H_
