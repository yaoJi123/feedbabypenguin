#ifndef _SMARTENEMY_H_
#define _SMARTENEMY_H_

#include <iostream>
#include "scaledSprite.h"
#include "twowaysprite.h"
#include "gamedata.h"

class SmartEnemy : public ScaledSprite {
public: 
    SmartEnemy(const std::string&,
               const TwoWaySprite&);
    void draw() const ;
    void update(Uint32);
    void goLeft();
    void goRight();
    void goUp();
    void goDown();

    float getSafeDistance() {return safeDistance;}

private:
    enum MODE {NORMAL, ATTACK};
    const TwoWaySprite& player;
    float safeDistance;
    MODE crtMode;
    SmartEnemy(const SmartEnemy&);
    SmartEnemy& operator= (const SmartEnemy& rhs);
};

#endif
