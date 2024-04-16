#pragma once

#include "../TileMap/TileMap.h"
#include "../Player/Player.h"
#include "../PNJ/PNJ.h"
#include "../Duck/Duck.h"

class Game {
  public:
    TileMap tileMap;
    Player player;
    std::vector<PNJ*> pnjs;

    Game();

    void addPNJ(PNJ* pnj);
    void movePlayer(float dx, float dy);

    //world pos is the integer value of the player pos
    olc::vi2d getWorldPos();

    olc::vf2d getPlayerPos(); 

    void generateTileMap();

    void update(float fElapsedTime);
};
