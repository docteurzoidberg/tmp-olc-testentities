#define OLC_PGE_APPLICATION

using namespace std;

#include "defines.h"

#include "GameRenderer/GameRenderer.h"

int main() {
  GameRenderer renderer2d = GameRenderer();
  if (renderer2d.Construct(SCREEN_W , SCREEN_H, SCREEN_PIXELSIZE, SCREEN_PIXELSIZE))
    renderer2d.Start();
  else {
    cout << "Failed to construct renderer" << endl;
    return 1;
  }
  return 0;
}
