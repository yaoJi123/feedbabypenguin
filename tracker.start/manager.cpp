#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "multisprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "twowaysprite.h"
#include "collisionStrategy.h"

SDLSound sound;

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  delete player;
  delete friendd;
  SDL_FreeSurface(orbSurface);
  for (unsigned i = 0; i < orbs.size(); ++i) {
    delete orbs[i];
  }
  orbs.clear();
  
  std::list<MultiSprite*>::iterator ptrd = smartE.begin();
    while(ptrd != smartE.end()) {
        ptrd = smartE.erase(ptrd);
    }
  smartE.clear();
  
  std::list<Sprite*>::iterator ptrf = foods.begin();
    while (ptrf != foods.end()) {
        ptrf = foods.erase(ptrf);
    }
  foods.clear();
    // for (unsigned:w
    // i = 0; i < smartE.size(); ++i) {
   //     delete smartE[i];
   // } 
   // smartE.clear();
}

Manager::Manager() :
 // sound(),
  keystatus(),
  showtime(Gamedata::getInstance().getXmlInt("showtime")), 
  player(new TwoWaySprite("penguin")),
  friendd (new SmartFriend("dog", *player)),
  Hud(),
  poolHud(),
  endHud(),
  fpsflag(true),
  findfood(false),
  godmod(false),
  lost(false),
  win(false),
 // poolflag(true),
  fpssecond(0),
  bullet("bullet"),
  orbSurface( io.loadAndSet(Gamedata::getInstance().getXmlStr("snowball/file"), 
              Gamedata::getInstance().getXmlBool("snowball/transparency")) ),
  orbs(),
  smartE(),
  foods(),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  backback("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  frontback("firstback", Gamedata::getInstance().getXmlInt("firstback/factor") ),
  seaback("frontback", Gamedata::getInstance().getXmlInt("frontback/factor") ),
  seamback("seamback", Gamedata::getInstance().getXmlInt("seamback/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(0),
  

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  makeOrbs();
  makeEnemys();
  makeFoods();
  check4Collsions();
  check4die();
  check4food();
  check4Win();
  sprites.push_back( new Sprite("child") );
  viewport.setObjectToTrack(player);
}

void Manager::makeOrbs() {
  unsigned numberOfOrbs = Gamedata::getInstance().getXmlInt("numberOfOrbs");
  orbs.reserve( numberOfOrbs );
  for (unsigned i = 0; i < numberOfOrbs; ++i) {
    orbs.push_back( new ScaledSprite("snowball", orbSurface) );
  }
  sort(orbs.begin(), orbs.end(), ScaledSpriteCompare());
}

void Manager::makeEnemys() {
    unsigned numberOfEnemys = Gamedata::getInstance().getXmlInt("numberOfEnemys");
    //smartE.reserve(numberOfEnemys);
    for (unsigned i = 0; i < numberOfEnemys; i++) {
        smartE.push_back(new MultiSprite("cheese"));
    }
}

void Manager::makeFoods() {
    unsigned numberOfFoods = Gamedata::getInstance().getXmlInt("numberOfFoods");
    for (unsigned i = 0; i < numberOfFoods; i++) {
        foods.push_back(new Sprite("cheese2"));
    }
}

void Manager::check4Collsions() {
   // SDLSound sound;
    std::list<MultiSprite*>::iterator ptrc = smartE.begin();
    while (ptrc != smartE.end()) {
        if (bullet.collidedWith(*ptrc)) {
            (*ptrc) -> explode();
            sound[5];
        }
        ++ptrc;
    }
}
void Manager::check4die() {
//    SDLSound sound;
    std::list<MultiSprite*>::iterator ptrp = smartE.begin();
    while (ptrp != smartE.end()) {
        if ((*ptrp) ->  collidedWith (player)) {
            player -> explode();
            lost = true;
            sound[5];
        }
        ++ptrp;
    }
}

void Manager::check4food() {
    std::list<Sprite*>::iterator ptrff = foods.begin();
    while (ptrff != foods.end()) {
        if (player -> collidedWith (*ptrff)) {
        findfood = true;
            sound[2];
        }
        ptrff++;
    }
}

void Manager::check4Win() {
    if (!lost &&
       findfood &&
       (player -> getScore() > (Gamedata::getInstance().getXmlInt("win")))) {
       win = true;
           sound[7];
    }
}

void Manager::draw() const {
  backback.draw();
  for (unsigned i = 0; i < orbs.size()/5; ++i) {
    orbs[i]->draw();
  }
  seamback.draw();
  for (unsigned i = orbs.size()/5; i < (orbs.size()/3 * 2); ++i) {
    orbs[i]->draw();
  }
  frontback.draw();
  for (unsigned i = (orbs.size()/3 * 2); i < (orbs.size()/5 * 4); ++i) {
    orbs[i]->draw();
  }
  seaback.draw();
  
  poolHud.draw((int) bullet.bulletCount(), (int) bullet.freeCount());

  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  for (unsigned i = orbs.size()/5 * 4; i < orbs.size(); ++i) {
    orbs[i]->draw();
  }
    if (findfood) {
        std::list<MultiSprite*>::const_iterator prt = smartE.begin();
        while(prt != smartE.end()) {
            (*prt) -> draw();
            ++prt;
        }
    }
    //std::list<MultiSprite*>::const_iterator prt = smartE.begin();
    //while(prt != smartE.end()) {
    //    (*prt) -> draw();
    //    ++prt;
    //}
  
       std::list<Sprite*>::const_iterator ptrf2 = foods.begin();
       while(ptrf2 != foods.end()) {
          (*ptrf2) -> draw();
          ++ptrf2;
       }
   
     if (!findfood) {  
        io.printMessageAt("Please Find fish!", 350, 410);
 
    }
    if (!lost &&
        findfood &&
        !win) {  
        io.printMessageAt("You already find fish, bring fish to baby", 210, 410);
        io.printMessageAt("Watch out crows!", 350, 450);
    }
    if (godmod) {
        io.printMessageAt("You are god now", 350, 80);
    }
 // io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
 // io.printMessageValueAt("Fps: ", clock.getFps(), 10, 70);
 // io.printMessageAt("Press T to switch sprites", 10, 45);
 // io.printMessageAt(title, 10, 450);
 // viewport.draw();
  player->draw();
  friendd -> draw();
  bullet.draw();
  Hud.draw();
      if (lost) {
        endHud.draw(true, true);
    }
    if (win) {
        endHud.draw(true, false);
       // godmod = !godmod
        
    }
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(player);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();

  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    //switchSprite();
  }

  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  for (unsigned i = 0; i < orbs.size(); ++i) {
    orbs[i]->update(ticks);
  }

    if (findfood) {
        std::list<Sprite*>::iterator prtf = foods.begin();
        while (prtf != foods.end()) {
            (*prtf) -> update(ticks);
            ++prtf;
        }
    }
   // if (lost) {
   //     clock.pause();
   // }
    //std::list<Sprite*>::iterator prtf = foods.begin();
    //while (prtf != foods.end()) {
    //    (*prtf) -> update(ticks);
    //    ++prtf;
    //}

  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  player->update(ticks);
  friendd -> update(ticks);
  backback.update();
  seamback.update();
  frontback.update();
  seaback.update();
  if(clock.getSeconds()-fpssecond > showtime){
     Hud.hide();
     poolHud.hide();
     fpsflag=false;
   //  poolflag = false;
    }
  bullet.update(ticks);

    if (findfood) {
      std::list<MultiSprite*>::iterator prt1= smartE.begin();
      while(prt1 != smartE.end()) {
        (*prt1) -> update(ticks);
        ++prt1; 
      }
    }

    if (findfood && !godmod && !win) {
        check4die();
    }
  check4Collsions();
//  check4die();
   if (!win && !lost) {
       check4food();
   }
   if (!lost) {
      check4Win();
   }
  
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
 // SDLSound sound;
  bool done = false;
  clock.start();

  while ( not done ) {
    while ( SDL_PollEvent(&event) ) 
{    //Uint8 *keystate = SDL_GetKeyState(NULL);
      switch(event.type) 
      { case SDL_QUIT :
                done = true;
                     break;   
        case SDL_KEYDOWN:
          SDLKey keystate;
          keystate = event.key.keysym.sym;
          keystatus[keystate]= 1;
         if(
           event.key.keysym.sym==SDLK_q||event.key.keysym.sym==SDLK_ESCAPE)  
              done = true;
   
         if(event.key.keysym.sym==SDLK_t)  
              /*switchSprite();*/
                    break;
         
         if(event.key.keysym.sym==SDLK_p) 
        { if (clock.isPaused()) clock.unpause();
          else clock.pause();}
        if(event.key.keysym.sym==SDLK_z) 
        {  clock.toggleSloMo(); }
         if(event.key.keysym.sym==SDLK_F4 && !makeVideo)
        { std::cout << "Making video frames" << std::endl;
          makeVideo = true; }
       if (keystatus[SDLK_f]) {
           sound[3];
           Vector2f v(Gamedata::getInstance().getXmlInt("bullet/bulletSpeedX"),
                      Gamedata::getInstance().getXmlInt("bullet/bulletSpeedY"));
           Vector2f p = friendd -> getPosition();
           p[0] += 30;
           p[1] += 30;
           bullet.shoot(p,v);
       }
       if (event.key.keysym.sym == SDLK_g) 
       { godmod = !godmod; }
       if (event.key.keysym.sym == SDLK_r) { 
          // endHud.draw(false,true);
           findfood = false;
           godmod = false;
           lost = false;
           win = false;
           player -> reset();
           friendd -> reset();
          // clock.unpause();
       }
          if(event.key.keysym.sym==SDLK_a) 
        {  player->left();     }
        //  if(event.key.keysym.sym==SDLK_s)
        // {  player->down();    }
          if(event.key.keysym.sym==SDLK_d)
         {  player->right();    }
          if(keystatus[SDLK_a] && keystatus[SDLK_d])
         {  player->stopAll();    }
          if(keystatus[SDLK_a] && keystatus[SDLK_f])
         {  player->left();
             
           Vector2f v(Gamedata::getInstance().getXmlInt("bullet/bulletSpeedX"),
                      Gamedata::getInstance().getXmlInt("bullet/bulletSpeedY"));
           Vector2f p = friendd -> getPosition();
           p[0] += 30;
           p[1] += 30;

           bullet.shoot(friendd -> getPosition(),v);
         }
          if(keystatus[SDLK_d] && keystatus[SDLK_f])
         {  player->right();
         
           Vector2f v(Gamedata::getInstance().getXmlInt("bullet/bulletSpeedX"),
                      Gamedata::getInstance().getXmlInt("bullet/bulletSpeedY"));
           Vector2f p = friendd -> getPosition();
           p[0] += 30;
           p[1] += 30;

           bullet.shoot(p,v);
         }
         // if(event.key.keysym.sym==SDLK_w)
         //{   player->up();       }
          if(event.key.keysym.sym==SDLK_F1)
         {   if(fpsflag){ 
               Hud.hide();
               poolHud.hide();
               fpsflag=false;
              // poolflag=false;
             } else  {
               Hud.show();
               poolHud.show();
               fpsflag=true;
             }
           fpssecond=clock.getSeconds(); 
         }
         break;
         case SDL_KEYUP:
             keystate = event.key.keysym.sym;
           keystatus[keystate]= 0;
           if(keystatus[SDLK_d]==0)
            {   player->stopX();
                }
            //if(keystatus[SDLK_w]==0)
            //{ player->stopY();
            //    }
            if(keystatus[SDLK_a]==0)
            { player->stopX();
                }
           // if(keystatus[SDLK_s]==0)
           // { player->stopY();
           //     }
             if(keystatus[SDLK_d])
            {
                 player->right();
            }
           //  if(keystatus[SDLK_w])
           // { player->up();
           //     }
           if(keystatus[SDLK_a])
            { player->left();
                }
            if(keystatus[SDLK_f])
            {  Vector2f v(Gamedata::getInstance().getXmlInt("bullet/bulletSpeedX"),
                          Gamedata::getInstance().getXmlInt("bullet/bulletSpeedY"));
               Vector2f p = friendd -> getPosition();
               p[0] += 30;
               p[1] += 30;

               bullet.shoot(p,v);
                }
            //if(keystatus[SDLK_s])
            //{ player->down();
            //    }
             break;
       }   
     }
    draw();
    update();
  }
}
