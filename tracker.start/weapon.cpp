#include <iostream>
#include <cmath>
#include "weapon.h"
#include "viewport.h"

Weapon::Weapon(const string &name, 
			   const Vector2f &pos,
               const Vector2f &vel,
			   const std::vector<Frame*> &fm):
    MultiSprite(name, pos, vel, fm),
    distance(0),
    maxDistance(Gamedata::getInstance().getXmlInt(name + "Distance")),
    tooFar(false)
    {}

//Weapon::~Weapon () {
//    delete sprite;
//}

void Weapon::update(Uint32 ticks) {
    Vector2f pos = getPosition();
    //Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    MultiSprite::update(ticks);
    distance += (hypot(X() - pos[0], Y() - pos[1]));
    if (distance > maxDistance) {
        tooFar = true;
    }
}

void Weapon::reset() {
    tooFar = false;
    distance = 0;
}
