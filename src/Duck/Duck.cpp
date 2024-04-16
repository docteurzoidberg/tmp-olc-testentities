#include "Duck.h"

Duck::Duck(float x, float y, std::string name, olc::Pixel color, bool leader) : PNJ(x,y,name){
  std::cout << "Duck constructor" << std::endl; 
  this->speed = 1.0f; //tile per second?
  this->color = color;
  this->state = STATE_IDLE;
  loadSpriteSheet("./sprites/duck.png", 16, 16);
}

Duck::~Duck() {
  std::cout << "Duck destructor" << std::endl;
}

void Duck::setFollowTarget(Duck * duckToFollow) {
  this->duckToFollow = duckToFollow;
}

void Duck::setAnimation(uint8_t anim) {

  uint8_t startIndex = 0;
  uint8_t endIndex = 0;
  uint8_t fps = 1;

  switch(anim) {
    case ANIM_IDLE:
      startIndex = 0;
      endIndex = 3;
      fps=1;
      break;
    case ANIM_WALK:
      startIndex = 4;
      endIndex = 7;
      break;
    case ANIM_RUN:
      startIndex = 8;
      endIndex = 11;
      fps = 3;
      break;
    case ANIM_FLY:
      startIndex = 12;
      endIndex = 15;
      break;
    case ANIM_SWIM:
      startIndex = 16;
      endIndex = 19;
      break;
  }
  PNJ::setAnimation(startIndex, endIndex, fps);
}

void Duck::startIdling() {
  state = STATE_IDLE;
  setAnimation(ANIM_IDLE);
}

void Duck::startWandering() {
  state = STATE_WANDERING;
  //todo: choose random target
  setAnimation(ANIM_WALK);
}

void Duck::startFollowing(Duck * duckToFollow) {
  state = STATE_FOLLOWING;
  //todo choose duck to follow
  setAnimation(ANIM_WALK);
}

void Duck::startFleeing(olc::vf2d awayFrom) {
  state = STATE_FLEEING;
  //todo: calc flee vector
  setAnimation(ANIM_FLY);
}

void Duck::startSwimming() {
  state = STATE_SWIMMING;
  setAnimation(ANIM_SWIM);
}

//given other pnjs, player pos and tilemap 2d array, update duck logic
void Duck::tick(TileMap *tileMap, Player *player, std::vector<PNJ> *pnjs, float fElapsedTime) {

  if(state == STATE_IDLE) {

    //if player is not close, start wandering/following
    //if player is far, stay idle
    //if player is near, start fleeing
    //if water is near, start swimming

  } else if(state == STATE_WANDERING) {

    //if player is near start fleeing
    //if player is very far, start idling
    //if water is near, target water
    //if on water start swimming

    //-> if current wandering target reached, choose new target

  } else if(state == STATE_FOLLOWING) {

    //if player is near, start fleeing
    //if on water start swimming

    //-> check target and move torwards it

  } else if(state == STATE_FLEEING) {

    //if player is near, keep fleeing
    //if player is far, start wandering/following

    //-> move with flee vector

  } else if(state == STATE_SWIMMING) {

    //if player is near, start fleeing
    //if closest duck too far. follow ?

  }

  //pnj update
  update(fElapsedTime);
}
