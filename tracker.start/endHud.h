#ifndef ENDHUD__H
#define ENDHUD__H
#include <iostream>
#include <string>
#include "vector2f.h"
#include "aaline.h"
#include "ioManager.h"
//#include "bullet.h"

class EndHud {
public:
  EndHud();
  void draw(bool shows, bool rst) const;

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
  bool shows;
  bool rst;
 };
#endif

