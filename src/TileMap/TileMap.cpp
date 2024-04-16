#include "TileMap.h"

TileMap::TileMap() {
  //init empty map
  for (auto y = 0; y < TILES_Y; y++) {
    for (auto x = 0; x < TILES_X; x++) {
      map[x][y] = TILE_NOTHING;
    }
  }
}

uint8_t  TileMap::calcNoise(int x, int y, double seed) {
  auto const noise = (
    db::perlin((double)x / 64.0f, (double)y / 64.0f, .25f*seed) * 1.0 +
    db::perlin((double)x / 32.0f, (double)y / 32.0f, .75f*seed) * 0.5
  ) / 1.5;
  auto const scaled = (uint8_t)((noise * 0.5 + 0.5) * 255.0);
  return scaled;
}

void TileMap::generate(int worldx, int worldy, double seed) {

  //world 0,0 is center screen so we must generate offset by TILE_WIDTH/2, TILE_HEIGHT/2
  auto startX = worldx - TILES_X/2;
  auto startY = worldy - TILES_Y/2;
  for (auto y = 0u; y < TILES_Y; ++y) {
    for (auto x = 0u; x < TILES_X; ++x) {
      map[x][y] =calcNoise(startX+x, startY+y, seed);
    }
  }
}

void TileMap::randomize(float fElapsedTime) {
  for (auto y = 0u; y < TILES_Y; ++y) {
    for (auto x = 0u; x < TILES_X; ++x) {
      map[x][y] = calcNoise(x, y, fElapsedTime);
    }
  }
}

uint8_t TileMap::getTileXY(int x, int y) {
  return toTile(map[x][y]);
}

uint8_t TileMap::getNoiseXY(int x, int y) {
  return map[x][y];
}

uint8_t TileMap::toTile(uint8_t noise) {
  uint8_t tile = 0;
  if (noise > 200) {
    tile = TILE_NOTHING;
  } else if (noise > 160) {
    tile = TILE_EARTH;
  } else if (noise > 140) {
    tile = TILE_DIRT;
  } else if (noise > 80) {
    tile = TILE_GRASS1;
  } else if (noise > 78) {
    tile = TILE_GRASS2;
  } else if (noise > 76) {
    tile = TILE_GRASS3;
  } else if (noise > 60) {
    tile = TILE_WHEAT;
  }
  return tile;
}
