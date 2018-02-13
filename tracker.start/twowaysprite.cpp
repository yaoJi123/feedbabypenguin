#include "twowaysprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "explodingSprite.h"
#include "vector2f.h"
#include "collisionStrategy.h"

static CollisionStrategy* getStrategy(const string& name) {
    std::string sName = Gamedata::getInstance().getXmlStr(name + "Strategy");
    if (sName == "midpoint") return new MidPointCollisionStrategy;
    if (sName == "rectangular") return new RectangularCollisionStrategy;
    if (sName == "perpixel") return new PerPixelCollisionStrategy;
    throw std::string("No Strategy");
}

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
  if(velocityX()>0){ 
	 // frames[currentFrame%(numberOfFrames/2)]->draw(x,y);
      lastFrame = 1;
  }
   
  if(velocityX()<0){ 
	//  frames[currentFrame%(numberOfFrames/2)+(numberOfFrames/2)]->draw(x,y);
      lastFrame = (numberOfFrames/2) + 1;    
  }

}

TwoWaySprite::TwoWaySprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  explosion(NULL),
  strategy (getStrategy(name)),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
 
  currentFrame(0),
  lastFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  explosion(s.explosion),
  strategy(s.strategy),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
 
  currentFrame(s.currentFrame),
  lastFrame(s.lastFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

TwoWaySprite::~TwoWaySprite() {
    delete strategy;
    if (explosion) {
        delete explosion;
    }
    
}




void TwoWaySprite::draw() const { 
    if (explosion) {
        explosion -> draw();
        return;
    }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(velocityX()>0){ 
	  frames[currentFrame%(numberOfFrames/2)]->draw(x,y);
      
  }
   
  if(velocityX()<0){ 
	  frames[currentFrame%(numberOfFrames/2)+(numberOfFrames/2)]->draw(x,y);
         
  }
   if(velocityX()==0){ 
       
       frames[lastFrame] -> draw(x, y);
	  
  }


//  frames[currentFrame]->draw(x, y);
}


void TwoWaySprite::update(Uint32 ticks) { 
    if (explosion) {
        explosion -> update(ticks);
        if (explosion -> chunkCount() == 0) {
            delete explosion;
            explosion = NULL;
        }
        return;
    }
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  

}

void TwoWaySprite::up(){
    velocityY(-200);
  
}
void TwoWaySprite::down(){
    velocityY(+200);
}
void TwoWaySprite::left(){
    velocityX(-200);
   
}
void TwoWaySprite::right(){
    velocityX(200);
   
}
void TwoWaySprite::stopX(){
    velocityX(0);
}
void TwoWaySprite::stopY(){
    velocityY(0);
}
void TwoWaySprite::stopAll(){
    velocityX(0);
    velocityY(0);
}

void TwoWaySprite::explode() {
    if (explosion) return;
    Sprite sprite (getName(), getPosition(),getVelocity(), getFrame());
    explosion = new ExplodingSprite(sprite);
}

bool TwoWaySprite::collidedWith(const Sprite* obj) {
    if (strategy -> execute(*this, *obj)) {
        return true;
    }
    return false;
}

void TwoWaySprite::reset() {
    explosion = NULL;
    X(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/x"));
    Y(Gamedata::getInstance().getXmlInt(getName()+"/startLoc/y")); 
}


