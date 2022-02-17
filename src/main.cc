// Copyright 2022 Chr. Alexander B. Bøhler

#include <iostream>
#include <string>
#include <typeinfo>

#include "str_to_int/str_to_int.hh"  // from the shf library

//#include "lib/gameObjects/game_object.hh"
#include "src/lib/global/global_singleton.hh"
#include "src/lib/command/command.hh"

int main() {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::getInstance();

  //tbge::GameObject obj = tbge::GameObject("Test");
  //obj.description("This is a fine description, and it is many lines long!");

  //tbge::Command com = tbge::Command("look", "look");
  
  //std::cout << com.command_word() << " : " << com.action() << std::endl;

  //std::cout << obj.id() << " : " << obj.description() << std::endl;
  //std::cout << s_p.str << std::endl;
  std::cout << shf::str_to_int("test") << std::endl;
  std::cout << "Hello World!" << std::endl;
}
