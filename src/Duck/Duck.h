#pragma once

#include "../Game/Game.h"
#include "../PNJ/PNJ.h"
#include "../Context/Context.h"

class Duck : public PNJ {
  public:

    enum DuckType {
      MALE = 0,
      FEMALE = 1,
      DUCKLING = 2,
    };

    enum DuckState {
      STATE_IDLE = 0,
      STATE_WANDERING= 1,
      STATE_FOLLOWING = 2,
      STATE_FLEEING = 3,
      STATE_SWIMMING = 4,
    };

    enum DuckAnimations {
      ANIM_IDLE = 0,
      ANIM_WALK = 1,
      ANIM_RUN = 2,
      ANIM_FLY = 3,
      ANIM_SWIM = 4,
    };

    bool isLeader = false;
    bool isRunning = false; //to calc speed

    uint8_t state = STATE_IDLE;
    uint8_t type = MALE;

    Duck(float x, float y, std::string name, olc::Pixel color, bool leader=false);
    ~Duck();

    void setAnimation(uint8_t anim);
    void setFollowTarget(Duck * duckToFollow);

    //state changes
    void startIdling();
    void startWandering();
    void startFollowing(Duck * duckToFollow); 
    void startFleeing(olc::vf2d awayFrom);
    void startSwimming();

    //state checks
    void checkIdle(Context context);
    void checkWandering(Context context);
    void checkFleeing(Context context);
    void checkSwimming(Context context);

    //given other pnjs, player pos and tilemap 2d array, update duck logic
    void tick(Context context);

  private:
    Duck* duckToFollow = nullptr;
};