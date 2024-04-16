#include "Game/Game.h"

Game::Game() {
  player = Player();
  tileMap = TileMap();

    //create some PNJs
  addPNJ(new Duck(0.0f,0.0f,"Albert", olc::BLUE, true));
  addPNJ(new Duck(5.0f,5.0f,"Bernard", olc::GREEN));
  addPNJ(new Duck(12.0f,12.0f,"Charles", olc::YELLOW));
  addPNJ(new Duck(-15.0f,-15.0f,"Denis", olc::RED));
}

void Game::addPNJ(PNJ* pnj) {
  pnjs.push_back(pnj);
}

void Game::movePlayer(float dx, float dy) {
  player.move(dx, dy);
}

//world pos is the integer value of the player pos
olc::vi2d Game::getWorldPos() {
  return player.getPosI();
} 

olc::vf2d Game::getPlayerPos() {
  return player.getPosF();
}

void Game::generateTileMap() {
  tileMap.generate((int)player.x, (int)player.y, SEED);
}

void Game::update(float fElapsedTime) {

  //update player
  //update pnjs
  //update tilemap

  //reset player moved flag !
  player.hasMoved = false;
}

