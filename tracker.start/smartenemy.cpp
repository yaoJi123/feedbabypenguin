#include <cmath>
#include "smartenemy.h"

float distance (float x1, float y1, float x2, float y2) {
    return hypot(x1 - x2, y1 - y2);
}

SmartEnemy::SmartEnemy(const std::string& n, const TwoWaySprite& p) :
    ScaledSprite(n),
    player(p),
    safeDistance(Gamedata::getInstance().getXmlInt("safeDistance")),
    crtMode(NORMAL)
{}

void SmartEnemy::draw() const {
    ScaledSprite::draw();
}

void SmartEnemy::update(Uint32 ticks) {
    ScaledSprite::update(ticks);
    float x = X() + getFrame() -> getWidth() / 2;
    float y = Y() + getFrame() -> getHeight() / 2;
    float px = player.X() + player.getFrame() -> getWidth() / 2;
    float py = player.Y() + player.getFrame() -> getHeight() / 2;
    float distance2p = ::distance(x, y, px, py);

    if (crtMode == NORMAL) {
        if (distance2p < safeDistance) crtMode = ATTACK;
    } else if (crtMode == ATTACK) {
        if (distance2p > safeDistance) {
            crtMode = NORMAL;
        } else {
            if (x < px) {goRight();}
            if (x > px) {goLeft();}
            if (y < py) {goUp();}
            if (y > py) {goDown();}
        }
    }
}

void SmartEnemy::goLeft() {
    if (X() > 0) velocityX( -abs(velocityX()) );
}

void SmartEnemy::goRight() {
    velocityX( fabs(velocityX()) );
}

void SmartEnemy::goUp() {
    velocityY( -fabs(velocityY()) );
}

void SmartEnemy::goDown() {
    velocityY( fabs(velocityY()) );
}
