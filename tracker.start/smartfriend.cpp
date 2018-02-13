#include <cmath>
#include "smartfriend.h"

float close (float x1, float y1, float x2, float y2) {
    return hypot(x1 - x2, y1 - y2);
}

SmartFriend::SmartFriend( const std::string& name,
                         const TwoWaySprite& p):
    TwoWaySprite(name),
    player(p),
    safeDistance(Gamedata::getInstance().getXmlInt("safeDistance")),
    crtMode(NORMAL)
{}

void SmartFriend::draw() const {
    TwoWaySprite::draw();
}

void SmartFriend::update(Uint32 ticks) {
    TwoWaySprite::update(ticks);
    float x = X() + getFrame() -> getWidth() / 2;
    float y = Y() + getFrame() -> getHeight() / 2;
    float px = player.X() + player.getFrame() -> getWidth() / 2;
    float py = player.Y() + player.getFrame() -> getHeight() / 2;
    float px1 = px - 20;
    float px2 = px + 20;
    float distance2p = ::close(x, y, px, py);

    if (crtMode == NORMAL) {
        if (distance2p <= safeDistance) crtMode = FOLLOW;
    } else if (crtMode == FOLLOW){
        if (distance2p > safeDistance) {
            crtMode = NORMAL;
        } else {
            if (x < px1) {
                goRight();
            }
            if (x > px2) {
                goLeft();
            }
           // if (x == px) {TwoWaySprite::stopAll();}
        }
    }
}

void SmartFriend::goLeft() {
    if (X() > 0) velocityX( -abs(velocityX()) );
}

void SmartFriend::goRight() {
    velocityX( fabs(velocityX()) );
}

void SmartFriend::stop() {
    velocityX(0);
}

void SmartFriend::reset() {
    TwoWaySprite::reset();
}
