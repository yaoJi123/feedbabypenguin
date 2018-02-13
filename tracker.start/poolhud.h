#ifndef POOLHUD__H
#define POOLHUD__H
#include <iostream>
#include <string>
#include "vector2f.h"
#include "aaline.h"
#include "ioManager.h"
#include "bullet.h"

class poolhud {
public:
  poolhud();
  void draw(int x,int y) const;

  void show();
  void hide();
 
private:
  Vector2f pos;
  int hudthickness;
  int hudWidth;
  int hudHeight;
  int worldWidth;
  int worldHeight;
  SDL_Surface * screen;
  bool showes;
  int x;
  int y;
 };
#endif

