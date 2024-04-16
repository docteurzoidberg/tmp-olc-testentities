#include "Player.h"

olc::vi2d  Player::getPosI() {
  return {(int)x, (int)y};
}

olc::vf2d Player::getPosF() {
  return {x, y};
} 

void Player::move(float dx, float dy) {
  x += dx;
  y += dy;
  hasMoved = true;
}

