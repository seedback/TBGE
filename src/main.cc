// Copyright 2022 Chr. Alexander B. Bøhler


#include <iostream>

#include "lib/gameObjects/GameObject.hh"


int main() {
  tbge::GameObject obj = tbge::GameObject("Test");
  obj.description("This is a fine description, and it is many lines long!");

  std::cout << obj.id() << " : " << obj.description() << std::endl;
  std::cout << "Hello World!" << std::endl;
}
