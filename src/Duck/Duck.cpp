#include "Duck.h"

float randf(float lo, float hi) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = hi - lo;
    float r = random * diff;
    return lo + r;
}

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
  std::cout << "Duck " << name << " start idling" << std::endl;
  state = STATE_IDLE;
  setAnimation(ANIM_IDLE);
}

void Duck::startWandering() {
  std::cout << "Duck " << name << " start wandering" << std::endl;
  state = STATE_WANDERING;
  speed = 1.0f;
  setAnimation(ANIM_WALK);


  //random x offset between -50 and 50
  float dx =randf(-15, 15);

  //random y offset between -5 and 5
  float dy = randf(-15, 15);

  setTarget(x + dx, y + dy);
}

void Duck::startFollowing(Duck * duckToFollow) {
  state = STATE_FOLLOWING;
  //todo choose duck to follow
  setAnimation(ANIM_WALK);
}

void Duck::startFleeing(olc::vf2d awayFrom) {
  state = STATE_FLEEING;
  speed = 2.0f;
  setAnimation(ANIM_FLY);
  std::cout << "Duck " << name << " start fleeing" << std::endl;
  //calculate flee vector
}

void Duck::startSwimming() {
  state = STATE_SWIMMING;
  setAnimation(ANIM_SWIM);
}

void Duck::checkIdle(Context context) {
  //if player is near, start fleeing
  //if player is not close, start wandering/following
  //else, player is too far, stay idle

  Player *player = context.player;

  //calculate distance to player
  float dist = sqrt((player->x - x)*(player->x - x) + (player->y - y)*(player->y - y));

  //std::cout << "Duck " << name << " dist to player: " << dist << std::endl;

  if(dist < 1) {
    startFleeing(olc::vi2d(player->x, player->y));
  } else if(dist < 30) {
    //std::cout << "Duck " << name << " is not near player !" << std::endl;
    startWandering();
    //if(isLeader) {
      
    //} else {
      //todo: check which other duck to follow
      //startFollowing(nullptr);
    //}
  } else {
    //stay idle
  }
}

void Duck::checkWandering(Context context) {

  /* 
  WANDERING:
  - if player is near, start fleeing
  - if player is very far, start idling
  - if wandering target is reached, choose new target
  - if water is near, target water
  */
  
  auto distToPlayer = sqrt((context.player->x - x)*(context.player->x - x) + (context.player->y - y)*(context.player->y - y));
  auto distToTarget = sqrt((targetX - x)*(targetX - x) + (targetY - y)*(targetY - y));

  //std::cout << "Duck " << name << " dist to target: " << distToTarget << ", player:" << distToPlayer << std::endl;

  //1) if player is near. star fleeing
  if(distToPlayer < 1) {
    startFleeing(olc::vi2d(context.player->x, context.player->y));
    return;
  } 

  //2) if player is very far, start idling
  if(distToPlayer > 30) {
    startIdling();
    return;
  }

  //3) if target reached, choose new target 
  if(distToTarget < 0.4) {
    //choose new target
    std::cout << "Duck " << name << " reached target" << std::endl;
    startWandering();
    return;
  } 
  
  //else: continue moving towards target
  move(context.elapsedTime);
}

void Duck::checkFleeing(Context context) {
  //if player is near, keep fleeing
  //if player is far, start wandering/following
  //-> move with flee vector

  //calculate distance to player
  float playerDist = sqrt((context.player->x - x)*(context.player->x - x) + (context.player->y - y)*(context.player->y - y));

  if(playerDist > 15) {
    //start wandering//following
    startWandering();
    return;
  }

  //calculate flee vector (away from player) and get target
  olc::vf2d fleeVector = olc::vf2d(x - context.player->x, y - context.player->y);
  fleeVector.norm();
  setTarget(x + fleeVector.x, y + fleeVector.y);

  move(context.elapsedTime);
}

//given other pnjs, player pos and tilemap 2d array, update duck logic
void Duck::tick(Context context) {

  //std::cout << "Duck tick" << std::endl;

  if(state == STATE_IDLE) {

    //if player is near, start fleeing
    //if player is not close, start wandering/following
    //else, player is too far, stay idle

    checkIdle(context);

  } else if(state == STATE_WANDERING || state == STATE_FOLLOWING) {
    
    //if player is very far, start idling
    //if player is near start fleeing
    //if water is near, target water
    //if on water start swimming

    //-> if current wandering target reached, choose new target
    //-> if following, check target and move towards it

    checkWandering(context);

  } else if(state == STATE_FLEEING) {

    //if player is near, keep fleeing
    //if player is far, start wandering/following

    //-> move with flee vector
    checkFleeing(context);

  } else if(state == STATE_SWIMMING) {

    //if player is near, start fleeing
    //if closest duck too far. follow ?

    

  }

  //pnj update
  update(context.elapsedTime);
}
