#ifndef _SMARTFRIEND_H_
#define _SMARTFRIEND_H_

#include <iostream>
#include "twowaysprite.h"
#include "gamedata.h"

class SmartFriend: public TwoWaySprite {
public:
    SmartFriend(const std::string&,
                const TwoWaySprite&);
    void draw() const;
    void update(Uint32);
    void goLeft();
    void goRight();
    void stop();
//    void goUp();
//    void goDown();
   void reset();
    float getSafeDistance() {return safeDistance;}

private:
    enum MODE {NORMAL, FOLLOW};
    const TwoWaySprite& player;
    float safeDistance;
    MODE crtMode;
    SmartFriend(const SmartFriend&);
    SmartFriend& operator= (const SmartFriend& rhs);
};

#endif
