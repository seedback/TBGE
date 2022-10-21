/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include <iostream>

#include "lib/game/game.h"
#include "lib/object/object.h"

namespace tbge{

Game::Game() : Object("") {
  set_name("");
}
Game::Game(std::string name) : Object(name) {}

std::string Game::get_class_name() {
  return "Game";
}

} // namespace tbge
