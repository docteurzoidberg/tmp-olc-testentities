#include "GameRenderer.h"

GameRenderer::GameRenderer() {
  sAppName = "Tiles";
}

void GameRenderer::RenderPNJs(float elapsedTime) {
  for(auto pnj : game->pnjs) {

    //if pnj is a duck
    //if(Duck* duck = static_cast<Duck*>(pnj)) {
      //duck->update(elapsedTime);
    //}

    //tile offset relative to player (screen center)
    auto tileOffsetX = (pnj->x - game->player.x) * TILE_WIDTH;
    auto tileOffsetY = (pnj->y - game->player.y) * TILE_HEIGHT;

    //tile position on screen is tileOffset - screen center to get at 0
    auto pnjScreenX = (SCREEN_W / 2) + tileOffsetX;
    auto pnjScreenY = (SCREEN_H / 2) + tileOffsetY;
    
    //fill color
    FillRect(pnjScreenX, pnjScreenY, TILE_WIDTH, TILE_HEIGHT, pnj->color);

    //draw red box around pnj
    DrawRect(pnjScreenX, pnjScreenY, TILE_WIDTH, TILE_HEIGHT, olc::RED);

    //TODO: draw pnj sprite
    //TODO: update pnj logic@
    pnj->update(elapsedTime);
  }
}

void GameRenderer::RenderTileMap() {

  //render tile map
  for (int y = 0; y < TILES_Y; y++) {
    for (int x = 0; x < TILES_X; x++) {

      auto tileNoise = game->tileMap.getNoiseXY(x, y);
      auto tile = game->tileMap.toTile(tileNoise);

      if(!showPerlin && tile == TILE_NOTHING) 
        continue;

      //tile position on screen is tileOffset - screen center to get at 0
      auto tileX = x * TILE_WIDTH;
      auto tileY = y * TILE_HEIGHT;
      auto tileCoords = olc::vi2d(tileX, tileY);
      
      //draw directly to screen*
      if(showPerlin)
        FillRect(tileCoords, tileSize, olc::Pixel(tileNoise, tileNoise, tileNoise));
      else
        DrawPartialSprite(tileCoords, sprTileSheet.get(), olc::vi2d(tile, (useDebugSprites?0:1))*tileSize, tileSize); 
      
      //Draw to a buffer sprite instead of screen
      //for (int ty = 0; ty < tileSize.y; ty++) {
        //for (int tx = 0; tx < tileSize.x; tx++) {
          //if(bShowPerlin)
            //sprTileMap->SetPixel(x*tileSize.x+tx, y*tileSize.y+ty, olc::Pixel(tileNoise, tileNoise, tileNoise));
          //else {
            //olc::Pixel p = sprTileSheet->GetPixel((tile-1)*tileSize.x+tx, ty + (bUseDebugSprites?0:tileSize.y)); 
            //sprTileMap->SetPixel(x*tileSize.x+tx, y*tileSize.y+ty, p);
          //}
        //}
      //}

    }
  }
}

bool GameRenderer::OnUserCreate() { 
  
  //init game
  game = new Game();

  // Load the sprites
  sprTileSheet = std::make_unique<olc::Sprite>("./sprites/tileset16px.png");

  //Set random seed
  srand(SEED);

  return true;
}

bool GameRenderer::OnUserUpdate(float elapsedTime) {  

  totalTime+=elapsedTime;

  // Handle Input
  if (GetKey(olc::Key::D).bPressed){
    showDebug = !showDebug;
    useDebugSprites = !useDebugSprites;
  }

  if(GetKey(olc::Key::P).bPressed)
    showPerlin = !showPerlin;

  if(GetKey(olc::Key::UP).bHeld) 
    game->movePlayer(0,-15.0f * elapsedTime);  
  
  if(GetKey(olc::Key::DOWN).bHeld) 
    game->movePlayer(0, 15.0f * elapsedTime);  

  if(GetKey(olc::Key::RIGHT).bHeld) 
    game->movePlayer(15.0f * elapsedTime, 0);  
  
  if(GetKey(olc::Key::LEFT).bHeld) 
    game->movePlayer(-15.0f * elapsedTime, 0); 

  //debug show player pos if player as moved
  if(game->player.hasMoved) {
    //cout << "Player moved pos: " << game.player.x << ", " << game.player.y << endl;
  }
  
  //get world pos
  auto newWorldPos = game->getWorldPos();

  //if world pos  changed, update tile map
  if(lastWorldPos != newWorldPos) {
    sAppName = std::to_string(newWorldPos.x) + ", " + std::to_string(newWorldPos.y);
    std::cout <<  "New world pos: " << newWorldPos.x << ", " << newWorldPos.y <<  ", regenerating tile map" << std::endl;
    game->generateTileMap();
    lastWorldPos = newWorldPos;
  }
  
  //no need to clear screen if we draw all tiles ! (insert smart gif here)
  RenderTileMap();

  //render and update PNJs
  RenderPNJs(elapsedTime);
  
  //update game logic
  game->update(elapsedTime);
  
  return true;
}
