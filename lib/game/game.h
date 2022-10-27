/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 * 
 * This is the class for the gameworld/gameworlds.
 * The whole game is run from here.
 */

// NOLINT(build/header_guard)
#ifndef TBGE_LIB_GAME_H_
#define TBGE_LIB_GAME_H_

#include <string>

#include "lib/object/object.h"
#include "lib/game_object/game_object.h"

namespace tbge {
class GameObject;
class Game : public Object {
 public:
  Game();
  explicit Game(std::string);

  std::string GetClassName() override;

  GameObject* get_dud_game_object();

 private:
  GameObject* dud_game_object_;
};
}  // namespace tbge


#endif  // TBGE_LIB_GAME_H_
