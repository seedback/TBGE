// TBGE.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <iostream>

#include "include\global\global_singleton.h"

int main() {
  tbge::GameObject* parent = new tbge::GameObject("parent");
  tbge::GameObject* child_1 = new tbge::GameObject("child_1");
  tbge::GameObject* child_2 = new tbge::GameObject("child_2");
  tbge::GameObject* child_3 = new tbge::GameObject("child_3");

  std::vector<tbge::GameObject*> child_list;
  child_list.push_back(child_1);
  child_list.push_back(child_2);
  child_list.push_back(child_2);
  child_list.push_back(child_3);

  parent->add_children(child_list);

  std::cout << "Listing children of " << parent->get_full_name() << std::endl;
  for (int i = 0; i < parent->get_children().size(); i++) {
    std::cout << "  " << parent->get_children()[i]->get_full_name()
              << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Listing parents:" << std::endl
            << "  " << child_1->get_full_name() << " : "
            << child_1->get_parent()->get_full_name() << std::endl
            << "  " << child_2->get_full_name() << " : "
            << child_2->get_parent()->get_full_name() << std::endl
            << "  " << child_3->get_full_name() << " : "
            << child_3->get_parent()->get_full_name() << std::endl;

  parent->remove_child(child_2);

  std::cout << std::endl;
  std::cout << "Listing children of " << parent->get_full_name() << std::endl;
  for (int i = 0; i < parent->get_children().size(); i++) {
    std::cout << "  " << parent->get_children()[i]->get_full_name()
              << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Listing parents:" << std::endl;
  std::cout << "  " << child_1->get_full_name() << std::endl;
  std::cout << "  " << child_2->get_full_name() << std::endl;
  std::cout << "  " << child_3->get_full_name() << std::endl;

  child_1->set_parent(child_3);

  std::cout << std::endl;
  std::cout << "Listing children of " << parent->get_full_name() << std::endl;
  for (int i = 0; i < parent->get_children().size(); i++) {
    std::cout << "  " << parent->get_children()[i]->get_full_name()
              << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Listing parents:" << std::endl;
  std::cout << "  " << child_1->get_full_name() << std::endl;
  std::cout << "  " << child_2->get_full_name() << std::endl;
  std::cout << "  " << child_3->get_full_name() << std::endl;
}
