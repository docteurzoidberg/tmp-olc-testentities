#pragma once

#include "../../lib/olcPixelGameEngine.h" 
#include "../Game/Game.h"

class GameRenderer : public olc::PixelGameEngine {
  public:
    GameRenderer();

  private:
    Game* game;

    float totalTime = 0.0f;
    bool showDebug = true;
    bool showPerlin = false;
    bool useDebugSprites = true;

    std::unique_ptr<olc::Sprite> sprTileSheet;

    olc::vi2d lastWorldPos = {-1, -1};
    olc::vi2d tileSize = {TILE_WIDTH, TILE_HEIGHT};

  protected:

    void RenderPNJs(float elapsedTime);

    void RenderTileMap();

    virtual bool OnUserCreate();

    virtual bool OnUserUpdate(float elapsedTime);
};