#include "PNJ.h"

PNJ::PNJ(float x, float y, std::string name) {
  this->x = x;
  this->y = y;
  this->name = name;
  //std::cout << "PNJ constructor" << std::endl;
}

PNJ::~PNJ() {
  //std::cout << "PNJ destructor" << std::endl;
}

void PNJ::setAnimation(uint8_t startIndex, uint8_t endIndex) {
  curAnimationFrame = 0;
  startAnimationFrame = startIndex;  
  endAnimationFrame = endIndex;
}

void PNJ::loadSpriteSheet(std::string path, uint16_t w, uint16_t h) {
  spriteSheet = std::make_unique<olc::Sprite>(path);
  spriteSize = {w, h};
}

olc::vi2d PNJ::getSpriteSize() {
  return spriteSize;
}

void PNJ::setSpriteSize(uint16_t w, uint16_t h) {
  spriteSize = {w, h};
}

void PNJ::setAnimation(uint8_t startIndex, uint8_t endIndex, float fps) {
  curAnimationFrame = startIndex;
  startAnimationFrame = startIndex;  
  endAnimationFrame = endIndex;
  animationFps = fps;
}

void PNJ::update(float elapsedTime) {
  
  //update animation
  if (curAnimationFrame < endAnimationFrame) {
    curAnimationFrame++;
  } else {
    if (animationLoop) {
      curAnimationFrame = startAnimationFrame;
    }
  }

  //move randomly for 0 to 3 tile
  //float moveX = (rand() % 3) - 1;
  //float moveY = (rand() % 3) - 1;
  //setTarget(x+ moveX, y+moveY);
  //move(elapsedTime*0.1f);
} 

void PNJ::setTarget(float dx, float dy) {
  targetX = dx;
  targetY = dy;
}

void PNJ::move(float elapsedTime) {
  //TODO: debug/test
  //move torward target based on elapsed time and speed
  if(x>targetX)
    x -= 0.5f * speed * elapsedTime;
  else
    x += 0.5f  * speed * elapsedTime;

  if(y>targetY)
    y -= 0.5f  * speed * elapsedTime;
  else
    y += 0.5f  * speed * elapsedTime;
}
