#pragma once 

#include "../../lib/olcPixelGameEngine.h"

class Player {
  public:
    float x = 0.0f;
    float y = 0.0f;
    float speed = 1.0f;
    bool hasMoved = false;
    olc::vi2d getPosI();
    olc::vf2d getPosF();
    void move(float dx, float dy);
};