#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "twowaysprite.h"
#include "hud.h"
#include "poolhud.h"
#include "scaledSprite.h"
#include "bullet.h"
#include "smartenemy.h"
#include "smartfriend.h"
#include "endHud.h"
#include "sound.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  //SDL_Sound sound;
  std::map<Uint8, int> keystatus;
  int showtime;
  TwoWaySprite* player;
  SmartFriend* friendd;
  hud Hud;
  poolhud poolHud;
  EndHud endHud;
  bool fpsflag;
  bool findfood;
  bool godmod;
  bool lost;
  bool win;
  //bool collide;
 // bool poolflag;
  float fpssecond;
  Bullet bullet;
  SDL_Surface * const orbSurface;
  std::vector<ScaledSprite*> orbs;
  std::list<MultiSprite*> smartE;
  std::list<Sprite*> foods;
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World backback;
  World frontback;
  World seaback;
  World seamback;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  void update();
  void makeOrbs();
  void makeEnemys();
  void makeFoods();
  void check4Collsions();
  void check4die();
  void check4food();
  void check4Win();


  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
