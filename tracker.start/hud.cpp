#include <cmath>
#include "hud.h"
#include "gamedata.h"
#include "clock.h"
#include "ioManager.h"
hud::hud():
  pos( Gamedata::getInstance().getXmlFloat("hud/positionX"),Gamedata::getInstance().getXmlFloat("hud/positionY")),
  hudthickness(Gamedata::getInstance().getXmlInt("hud/thickness")),
  hudWidth(Gamedata::getInstance().getXmlInt("hud/width")),
  hudHeight(Gamedata::getInstance().getXmlInt("hud/height")),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  screen(IOManager::getInstance(). getScreen() ),
  showed(true),
  hided(false)
  
{ }

void hud::draw() const { 
//const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  if(showed)
{
  
   Draw_AALine(screen,pos[0], pos[1]+hudHeight/2, 
                      pos[0]+hudWidth,pos[1]+hudHeight/2, 
                      hudHeight,0x80, 0xff, 0xff, 0xff/1.8); 
   Draw_AALine(screen, pos[0], pos[1], pos[0]+hudWidth,pos[1],
                          hudHeight/100,0, 0, 0xff/1.1, 0xff/1.1);
   Draw_AALine(screen, pos[0]+hudWidth, pos[1], pos[0]+hudWidth,pos[1]+hudHeight,
                          hudHeight/100,0, 0, 0xff/1.1, 0xff/1.1);
   Draw_AALine(screen, pos[0], pos[1], pos[0],pos[1]+hudHeight,
                          hudHeight/100,0, 0, 0xff/1.1, 0xff/1.1);
   Draw_AALine(screen, pos[0], pos[1]+hudHeight, pos[0]+hudWidth,pos[1]+hudHeight,
                          hudHeight/100,0, 0, 0xff/1.1, 0xff/1.1);
 

Clock::getInstance().draw();
IOManager::getInstance().printMessageAt(Gamedata::getInstance().getXmlStr("screenTitle"),10,380);
IOManager::getInstance().printMessageAt("press F to fire",10,50);
IOManager::getInstance().printMessageAt("press G to become god",10,100);
IOManager::getInstance().printMessageAt("press A to move left",10,150);
IOManager::getInstance().printMessageAt("press D to move right",10,200);
IOManager::getInstance().printMessageAt("press R to reset",10,250);
IOManager::getInstance().printMessageAt("press F1 to toggle the HUD",10,300);
}
}
void hud::show() {
     showed=true;
   //  hided=false;
    }

void hud::hide() {
    showed=false;   
    }

//void hud::update(Uint32 ticks) { }

//void hud::unhide() {
  //  hided=false;
   // }
//   void hud::update(Uint32 ticks){
       
//   }    
