#pragma once

using namespace std;

#include "../lib/olcPixelGameEngine.h" 
#include "../Game/Game.h"

class GameRenderer : public olc::PixelGameEngine {
  public:
    GameRenderer();

  private:
    Game game;

    float fTotalTime = 0.0f;
    bool bShowDebug = true;
    bool bShowPerlin = false;
    bool bUseDebugSprites = true;

    std::unique_ptr<olc::Sprite> sprTileSheet;

    olc::vi2d lastWorldPos = {-1, -1};
    olc::vi2d tileSize = {TILE_WIDTH, TILE_HEIGHT};

  protected:

    void RenderPNJs(float fElapsedTime);

    void RenderTileMap();

    virtual bool OnUserCreate();

    virtual bool OnUserUpdate(float fElapsedTime);
};