// NOLINT(legal/copyright)

#include <iostream>

#include "lib/object/object.h"
#include "lib/game_object/game_object.h"

int main() {
  tbge::Object ob0;
  tbge::Object ob1;
  tbge::Object ob2;
  tbge::Object ob3;
  tbge::Object ob4;
  tbge::Object ob5;

  std::cout << ob0.getId() << std::endl
            << ob1.getId() << std::endl
            << ob2.getId() << std::endl
            << ob3.getId() << std::endl
            << ob4.getId() << std::endl
            << ob5.getId() << std::endl;

  GameObject go;

  std::cout << "aaaHello World!" << go.getId() << std::endl;

  system("PAUSE");
}