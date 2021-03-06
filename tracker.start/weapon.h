#ifndef WEAPON__H
#define WEAPON__H

#include <iostream>
#include "multisprite.h"
#include "gamedata.h"
#include "viewport.h"
#include "vector2f.h"

class Weapon: public MultiSprite {
    public:
         Weapon(const string &,
               const Vector2f &,
               const Vector2f &,
               const std::vector<Frame*> &);
        // ~Weapon();
        virtual void update(Uint32 ticks);
        bool goneTooFar() const {return tooFar;}
        void reset();
    private:
       // MultiSprite sprite;
        float distance;
        float maxDistance;
        bool tooFar;
};
#endif
