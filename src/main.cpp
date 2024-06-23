#define OLC_PGE_APPLICATION


#include "defines.h"

#include "GameRenderer/GameRenderer.h"

int main() {
  GameRenderer renderer2d = GameRenderer();
  if (renderer2d.Construct(SCREEN_W , SCREEN_H, SCREEN_PIXELSIZE, SCREEN_PIXELSIZE))
    renderer2d.Start();
  else {
    std::cout << "Failed to construct renderer" << std::endl;
    return 1;
  }
  return 0;
}
