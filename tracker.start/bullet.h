#ifndef __BULLET_H__
#define __BULLET_H__

#include <list>
#include "weapon.h"
#include "collisionStrategy.h"
#include "gamedata.h"
#include "frameFactory.h"


class Bullet {
public:
    Bullet(const std::string&);
    Bullet(const Bullet&);
    ~Bullet();
    void draw() const;
    void update(Uint32 ticks);
    void shoot(const Vector2f&,
               const Vector2f&);
    bool collidedWith(const MultiSprite *obj);

    unsigned int bulletCount() const {return bulletList.size();}
    unsigned int freeCount() const {return freeList.size();}
    bool shooting() const {return bulletList.empty();}

private:
    std::string name;
    CollisionStrategy* strategy;
    std::vector<Frame*> bulletFrame;
    float bulletInterval;
    float timeSinceLastFrame;
    std::list<Weapon> bulletList;
    std::list<Weapon> freeList;

    Bullet& operator = (const Bullet&);
};

#endif 
