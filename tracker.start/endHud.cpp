#include <cmath>
#include "endHud.h"
#include "gamedata.h"
#include "clock.h"
#include "ioManager.h"
EndHud::EndHud():
  pos( Gamedata::getInstance().getXmlFloat("endhud/positionX"),Gamedata::getInstance().getXmlFloat("endhud/positionY")),
  hudthickness(Gamedata::getInstance().getXmlInt("endhud/thickness")),
  hudWidth(Gamedata::getInstance().getXmlInt("endhud/width")),
  hudHeight(Gamedata::getInstance().getXmlInt("endhud/height")),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  screen(IOManager::getInstance(). getScreen() ),
  shows(false),
  rst (false)
 // sword()
  
{ }

void EndHud::draw(bool shows, bool rst) const { 
//const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);  
    if(shows){
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
       if (rst) {
          IOManager::getInstance().printMessageAt("YOU LOST, PRESS R TO RESTART", 260, 250);
       }
       if (!rst) {
          IOManager::getInstance().printMessageAt("YOU WIN!!!!! ", 350, 250);
       }
    }
}

//void EndHud::show() {
//   showes=true;
//}

//void EndHud::hide() {
//   showes=false;   
//}


