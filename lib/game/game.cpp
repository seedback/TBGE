/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 */

#include <iostream>

#include "lib/game/game.h"
#include "lib/object/object.h"
#include "lib/game_object/game_object.h"

namespace tbge{

Game::Game() : Object("") {
  set_name("");
  dud_game_object_ = new GameObject();
}
Game::Game(std::string name) : Object(name) {}

std::string Game::get_class_name() {
  return "Game";
}

GameObject* Game::get_dud_game_object() {
  return dud_game_object_;
}

} // namespace tbge
