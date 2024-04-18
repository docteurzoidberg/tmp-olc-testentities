#pragma once

#include "../TileMap/TileMap.h"
#include "../Player/Player.h"
#include "../PNJ/PNJ.h"

struct Context {
  public:
    TileMap *map;
    Player *player;
    std::vector<PNJ*> *pnjs;
    float elapsedTime = 0.0f;
    Context(TileMap *map, Player *player, std::vector<PNJ*> *pnjs, float elapsedTime);
};