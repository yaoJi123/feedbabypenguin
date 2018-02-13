#ifndef POOLHUD_H
#define POOLHUD_H
#include <iostream>
#include <string>
#include "vector2f.h"
#include "aaline.h"
#include "bullet.h"
#include "gamedata.h"

class PoolHud {
public:
    PoolHud();
    void draw(int x, int y) const;
    void show();
    void hide();

private:
    Vector2f pos;
    int hudthickness;
    int hudtWidth;
    int hudHeight;
    int worldWidth;
    int worldHeight;
    SDL_Surface* screen;
    bool shows;
    int x;
    int y;
};
#endif
