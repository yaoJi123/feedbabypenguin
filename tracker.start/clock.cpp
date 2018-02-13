#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  ticks(0),
  delayTicks(SDL_GetTicks()),
  totalTicks(0),
  started(false), 
  paused(false), 
  sloMo(false), 
  lastFrameTicks(SDL_GetTicks()),
  sumOfTicks(SDL_GetTicks()),
  pos( Gamedata::getInstance().getXmlInt("clock/locX"),
       Gamedata::getInstance().getXmlInt("clock/locY")),
  framesAreCapped(Gamedata::getInstance().getXmlBool("framesAreCapped")),
  frameCap(Gamedata::getInstance().getXmlInt("frameCap")),delay(0)
  {
  start();
}

void Clock::draw() const { 
  IOManager::getInstance().
    printMessageValueAt("Seconds: ", getSeconds(), pos[0], pos[1]);
  IOManager::getInstance().
    printMessageValueAt("fps: ", getFps(), pos[0], pos[1]+20);
}

void Clock::update() {
totalTicks = SDL_GetTicks();
ticks= totalTicks - lastFrameTicks;
lastFrameTicks = totalTicks;
int delay = std::max(0.0,1000.0/frameCap-(totalTicks-delayTicks));
SDL_Delay(delay);
delayTicks=SDL_GetTicks();
if(!paused) 
{sumOfTicks = sumOfTicks + ticks;}
}
unsigned int Clock::getTicksSinceLastFrame() const {
if(paused) {return 0;}
else if(sloMo) {return 1;}
else {return ticks;}
}

void Clock::toggleSloMo() {
  sloMo = ! sloMo;
}

int Clock::getFps() const { 
    if ( ticks > 0 ){return 1000/ticks;}
    return 0;
}

void Clock::start() { 
  started = true; 
  paused = false; 
}

void Clock::pause() { 
//  std::cout << "pause: Not implemented yet" << std::endl;
paused = true;   
}

void Clock::unpause() { 
//  std::cout << "unpause: Not implemented yet" << std::endl;
   paused = false; 
}

