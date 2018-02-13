#ifndef HUD__H
#define HUD__H
#include <iostream>
#include <string>
#include "vector2f.h"
#include "aaline.h"
#include "ioManager.h"
//#include "clock.h"

class hud {
public:
  hud();
  void draw() const;
  void update(Uint32 ticks);
  void show();
  void hide();
 // void undate();
private:
  Vector2f pos;
  int hudthickness;
  int hudWidth;
  int hudHeight;
  int worldWidth;
  int worldHeight;
  SDL_Surface * screen;
  bool showed;
  bool hided;
 };
#endif

