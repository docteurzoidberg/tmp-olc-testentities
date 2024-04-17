#include "Context.h"

Context::Context(TileMap *map, Player *player, std::vector<PNJ> *pnjs, float elapsedTime) {
  this->tileMap = map;
  this->player = player;
  this->pnjs = pnjs;
  this->elapsedTime = elapsedTime;
}