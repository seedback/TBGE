#ifndef TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_
#define TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "src/game_object/game_object.h"
#include "src/game_object/game_object_with_description/game_object_with_description.h"

class GameObjectWithDescriptionTest : public ::testing::Test {
 protected:
  std::string parent_name = "parent_object";
  std::string child1_name = "child1";
  std::string child2_name = "child2";
  tbge::GameObjectWithDescription parent{parent_name};
  tbge::GameObjectWithDescription child1{child1_name};
  tbge::GameObjectWithDescription child2{child1_name};
  std::vector<tbge::GameObject*> children = {&child1, &child2};
};

#endif  // TBGE_TEST_GAME_OBJECT_GAME_OBJECT_WITH_DESCRIPTION_GAME_OBJECT_WITH_DESCRIPTION_H_