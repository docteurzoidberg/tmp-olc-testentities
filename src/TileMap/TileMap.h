#pragma once 

#include <cstdint>

#include "defines.h"

#define DB_PERLIN_IMPL

#include "../lib/dbPerlin.hpp"

enum Tiles { 
  TILE_NOTHING = 0, 

  TILE_DIRT = 1,
  TILE_EARTH = 2,

  TILE_GRASS1 = 3,
  TILE_GRASS2 = 4,
  TILE_GRASS3 = 5,
  TILE_GRASS4 = 6,

  TILE_WHEAT = 7,
  TILE_ROCK = 8,
};

class TileMap {
  public:

    //map data
    uint8_t map[TILES_X][TILES_Y];
 
    TileMap();

    uint8_t calcNoise(int x, int y, double seed);

    void generate(int worldx, int worldy, double seed); 

    void randomize(float fElapsedTime); 

    uint8_t getTileXY(int x, int y);
    uint8_t getNoiseXY(int x, int y);

    uint8_t toTile(uint8_t noise);
};
