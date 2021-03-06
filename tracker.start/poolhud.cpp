#include <cmath>
#include "poolhud.h"
#include "gamedata.h"
#include "clock.h"
#include "ioManager.h"
poolhud::poolhud():
  pos( Gamedata::getInstance().getXmlFloat("poolhud/positionX"),Gamedata::getInstance().getXmlFloat("poolhud/positionY")),
  hudthickness(Gamedata::getInstance().getXmlInt("poolhud/thickness")),
  hudWidth(Gamedata::getInstance().getXmlInt("poolhud/width")),
  hudHeight(Gamedata::getInstance().getXmlInt("poolhud/height")),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  screen(IOManager::getInstance(). getScreen() ),
  showes(true),
  x(0),
  y(0)
 // sword()
  
{ }

void poolhud::draw(int x,int y) const { 
//const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  if(showes)
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
 
IOManager::getInstance().printMessageValueAt("BULLET LIST: ", x, 650, 20);
IOManager::getInstance().printMessageValueAt("FREE LIST: ", y, 650, 40);

}
}
void poolhud::show() {
     showes=true;
   
    }

void poolhud::hide() {
    showes=false;   
    }


