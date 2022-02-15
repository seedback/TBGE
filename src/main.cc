// Copyright 2022 Chr. Alexander B. Bøhler

#define quote(x) #x

#include <iostream>
#include <string>
#include <typeinfo>

#include "str_to_int/str_to_int.hh"  // from the shf library

#include "lib/gameObjects/game_object.hh"

int main() {
  tbge::GameObject obj = tbge::GameObject("Test");
  obj.description("This is a fine description, and it is many lines long!");

  tbge::Command com = tbge::Command();
  com.action("look");

  tbge::CommandAction act = com.action_translate_str_to_command_action_("LOOK");

  if (act == tbge::CommandAction::kLook) {
    std::cout << "true" << std::endl;
  } else {
    std::cout << "false" << std::endl;
  }

  std::cout << typeid(act).name() << std::endl;

  com.action_translate_command_action_to_str_(tbge::CommandAction::kInspect);

  std::cout << com.action_translate_command_action_to_str_(act) << std::endl;
  std::cout << obj.id() << " : " << obj.description() << std::endl;
  std::cout << shf::str_to_int("test") << std::endl;
  std::cout << "Hello World!" << std::endl;
}
