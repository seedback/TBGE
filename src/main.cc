// Copyright 2022 Chr. Alexander B. Bøhler

#include <iostream>
#include <string>
#include <typeinfo>

#include "str_to_int/str_to_int.hh"  // from the shf library

#include "src/lib/game_object/game_object.hh"
#include "src/lib/global/global_singleton.hh"
#include "src/lib/command/command.hh"

int main() {
  tbge::global::GlobalSingleton& inst =
      tbge::global::GlobalSingleton::get_instance();

  tbge::GameObject* obj1 = new tbge::GameObject("parent");
  tbge::GameObject* obj2 = new tbge::GameObject("child");
  tbge::GameObject* obj3 = new tbge::GameObject("new-parent");
  tbge::GameObject* obj4 = new tbge::GameObject("sibling");

  std::cout << obj1->get_name() << " : " << obj1->get_id() << std::endl;
  std::cout << obj2->get_name() << " : " << obj2->get_id() << std::endl;
  std::cout << obj3->get_name() << " : " << obj3->get_id() << std::endl;

  std::cout << std::endl;

  std::cout << inst.get_game_objects().size() << std::endl;
  std::cout << inst.get_game_objects()[1]->get_name() << std::endl;

  std::cout << std::endl;

  //system("PAUSE");

  obj2->set_parent(*obj1);
  std::cout << "obj2 full_name: " << obj2->get_full_name() << std::endl;
  obj4->set_parent(*obj1);
  std::cout << "obj4 full_name: " << obj4->get_full_name() << std::endl;
  obj2->set_parent(*obj4);
  std::cout << "obj2 full_name: " << obj2->get_full_name() << std::endl;
  std::cout << "test: " << obj1->get_children()[0]->get_name() << std::endl;

  //tbge::GameObject obj = tbge::GameObject("Test");
  //obj.description("This is a fine description, and it is many lines long!");

  //tbge::Command com = tbge::Command("look", "look");
  
  //std::cout << com.command_word() << " : " << com.action() << std::endl;

  //std::cout << obj.id() << " : " << obj.description() << std::endl;
  //std::cout << s_p.str << std::endl;

  //inst.command_word_aliases(std::multimap<std::string, std::string>());
  //inst.add_command_word_alias("LOOK", "LOOK");
  //inst.add_command_word_alias("SEE", "LOOK");
  //inst.add_command_word_alias("INSPECT", "LOOK");
  //inst.add_command_word_alias("GO", "GO");
  //inst.add_command_word_alias("MOVE", "GO");
  //inst.add_command_word_alias("ENTER", "GO");
  //inst.add_command_word_alias("INSPECT", "INSPECT");
  //inst.add_command_word_alias("TEST", "TEST");
  //inst.add_command_word_alias("TEMP", "TEST");
  //inst.add_command_word_alias("T", "TEST");

  //std::cout << inst.command_word_aliases().count("INSPECT") << std::endl;

  //auto list = inst.get_command_words_by_alias("INSPECT");

  //for (auto const& x : list) {
  //  std::cout << x << std::endl;
  //}

  //std::cout << shf::str_to_int("test") << std::endl;
  std::cout << "Hello World!" << std::endl;
}
