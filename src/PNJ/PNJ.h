#pragma once

#include "../../lib/olcPixelGameEngine.h" 

#include <cstdint>
#include <memory>
#include <sys/types.h>

class Context;

class PNJ {
  private:
    olc::vi2d spriteSize = {0, 0};
    std::unique_ptr<olc::Sprite> spriteSheet;

    //handle animation looping. current frame index, start frame, end frame
    uint8_t curAnimationFrame = 0;
    uint8_t startAnimationFrame = 0;
    uint8_t endAnimationFrame = 0;
    uint8_t animationFps = 1;
    bool animationLoop = false;

    float totalTime = 0.0f;

  protected:
    float targetX=0.0f;
    float targetY=0.0f; 

  public:
    std::string name="Unamed"; 
    
    float x = 0.0f;
    float y = 0.0f;
    float speed = 1.0f; //tile per second?
    olc::Pixel color = olc::WHITE;

    PNJ(float x, float y, std::string name);
    ~PNJ() ;

    void setAnimation(uint8_t startIndex, uint8_t endIndex) ;

    void loadSpriteSheet(std::string path, uint16_t w, uint16_t h) ;

    olc::vi2d getSpriteSize() ;

    void setSpriteSize(uint16_t w, uint16_t h) ;

    void setAnimation(uint8_t startIndex, uint8_t endIndex, float fps);

    void update(float elapsedTime);

    virtual void tick(Context context) = 0;

    void setTarget(float dx, float dy); 
    void move(float elapsedTime);
};