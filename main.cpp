// NOLINT(legal/copyright)

#include <iostream>

#include "lib/object/object.h"
#include "lib/game_object/game_object.h"
#include "lib/game/game.h"

int main() {
  tbge::Game g0 = tbge::Game();

  tbge::GameObject go0 = tbge::GameObject(&g0, "test");

  std::cout << "Hello World!" << std::endl;

  system("PAUSE");
}