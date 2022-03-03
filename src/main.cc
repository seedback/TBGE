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

  obj2->set_parent(*obj1);
  std::cout << "obj2 full_name: " << obj2->get_full_name() << std::endl;
  obj4->set_parent(*obj1);
  std::cout << "obj4 full_name: " << obj4->get_full_name() << std::endl;
  obj2->set_parent(*obj4);
  std::cout << "obj2 full_name: " << obj2->get_full_name() << std::endl;
  std::cout << "test: " << obj1->get_children()[0]->get_name() << std::endl;

  std::cout << "Hello World!" << std::endl;
}
