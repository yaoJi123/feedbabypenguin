#include <iostream>
#include <cmath>
#include "bullet.h"

static CollisionStrategy* getStrategy(const string& name) {
    std::string sName = Gamedata::getInstance().getXmlStr(name+"Strategy");
    if (sName == "midpoint") return new MidPointCollisionStrategy;
    if (sName == "rectangular") return new RectangularCollisionStrategy;
    if (sName == "perpixel") return new PerPixelCollisionStrategy;
    throw std::string("No strategy");
}


Bullet::Bullet(const std::string& n):
    name(n),
    strategy (getStrategy(name)),
    bulletFrame (FrameFactory::getInstance().getFrames(name)),
    bulletInterval (Gamedata::getInstance().getXmlInt(name + "bulletInterval")),
    timeSinceLastFrame(0),
    bulletList(),
    freeList()
{}

Bullet::Bullet(const Bullet& b):
    name (b.name),
    strategy (b.strategy),
    bulletFrame(b.bulletFrame),
    bulletInterval(b.bulletInterval),
    timeSinceLastFrame(b.timeSinceLastFrame),
    bulletList(b.bulletList),
    freeList(b.freeList)
{}

Bullet::~Bullet() {
    delete strategy;
}

void Bullet::draw() const {
    std::list<Weapon>::const_iterator ptr = bulletList.begin();
    while (ptr != bulletList.end()) {
        ptr -> draw();
        ++ptr;
    }
}

void Bullet::update(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    std::list<Weapon>::iterator ptr = bulletList.begin();
    while (ptr != bulletList.end()) {
        ptr -> update(ticks);
        if (ptr -> goneTooFar()) {
            freeList.push_back(*ptr);
            ptr = bulletList.erase(ptr);
        } else {
            ++ptr;
        }
    }
} 

void Bullet::shoot(const Vector2f& position,
                   const Vector2f& velocity) {
    if (timeSinceLastFrame > bulletInterval) {
        if (freeList.empty()) {
            Weapon b(name, position, velocity, bulletFrame);
            bulletList.push_back(b);
        } else {
            Weapon b = freeList.front();
            freeList.pop_front();
            b.reset();
            b.setPosition(position);
          //  std::cout << velocity << std::endl;
            b.setVelocity(velocity);
            bulletList.push_back(b);
        }
        timeSinceLastFrame = 0;
    }
}

bool Bullet::collidedWith(const MultiSprite* obj) {
    std::list<Weapon>::iterator ptr = bulletList.begin();
    while (ptr != bulletList.end()) {
        if (strategy -> execute(*ptr, *obj)) {
            freeList.push_back(*ptr);
            ptr = bulletList.erase(ptr);
            return true;
        } else {
            ptr++;
        }
    }
    return false;
}


