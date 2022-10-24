/* MIT License
 *
 * Copyright (c) 2022 seedback (Chr. Alexander B. Bøhler)
 * 
 * This is the class for the gameworld/gameworlds.
 * The whole game is run from here.
 */

#ifndef TBGE_LIB_GAME_H_
#define TBGE_LIB_GAME_H_

#include <string>

#include "lib/object/object.h"
#include "lib/game_object/game_object.h"

namespace tbge
{
  class Game : public Object {
   public:
    Game();
    Game(std::string);

    std::string get_class_name () override;
  };
} // namespace tbge


#endif  // TBGE_LIB_GAME_H_