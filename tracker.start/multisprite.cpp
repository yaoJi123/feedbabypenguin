#include <cmath>
#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "vector2f.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"

static CollisionStrategy* getStrategy(const string& name) {
    std::string sName = Gamedata::getInstance().getXmlStr(name+"Strategy");
    if (sName == "midpoint") return new MidPointCollisionStrategy;
    if (sName == "rectangular") return new RectangularCollisionStrategy;
    if (sName == "perpixel") return new PerPixelCollisionStrategy;
    throw std::string("No strategy");
}

void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}



MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f((rand()%2?4:-4)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/loc/x")), 
                    Gamedata::getInstance().getXmlInt(name+"/loc/y")), 
           Vector2f(//0,
                    (rand()%2?1:-0.1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/x")),
                   (rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                   Gamedata::getInstance().getXmlInt(name+"/speed/y"))
                   )
           ),
  explosion(NULL),
  strategy (getStrategy(name)),
  frames(FrameFactory::getInstance().getFrames(name)),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

MultiSprite::MultiSprite(const std::string& name,
                         const Vector2f& pos,
                         const Vector2f& vel,
                         const std::vector<Frame*>& fms) :
    Drawable(name, pos, vel),
    explosion(NULL),
    strategy (getStrategy(name)),
    frames(fms),
    worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
    worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
    //dt(0),
    currentFrame(0),
    numberOfFrames(Gamedata::getInstance().getXmlInt(name + "/frames")),
    frameInterval(Gamedata::getInstance().getXmlInt(name + "/frameInterval")),
    timeSinceLastFrame(0),
    frameWidth(fms[0] -> getWidth()),
    frameHeight(fms[0] -> getHeight())
{}

MultiSprite::MultiSprite(const MultiSprite& s):
    Drawable(s),
    explosion(s.explosion),
    strategy (s.strategy),
    frames(s.frames),
    worldWidth(s.worldWidth),
    worldHeight(s.worldHeight),
    currentFrame(s.currentFrame),
    numberOfFrames(s.numberOfFrames),
    frameInterval(s.frameInterval),
    timeSinceLastFrame(s.timeSinceLastFrame),
    frameWidth(s.frameWidth),
    frameHeight(s.frameHeight)
{}

MultiSprite::~MultiSprite() {
   // delete strategy;
    if(explosion)
        delete explosion;
}

void MultiSprite::draw() const { 
    if (explosion) {
        explosion -> draw();
        return;
    }
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  //frames[currentFrame]->draw(x, y);
  if(velocityX()>0){ 
	  frames[currentFrame%(numberOfFrames/2)]->draw(x,y);
     
  }
   
  if(velocityX()<0){ 
	  frames[currentFrame%(numberOfFrames/2)+(numberOfFrames/2)]->draw(x,y);
          
  }
}

void MultiSprite::update(Uint32 ticks) { 
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
     setPosition(Vector2f(X(), 0));
     //velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}

void MultiSprite::explode() {
    if (explosion) return ;
    Sprite sprite(getName(), getPosition(), getVelocity(), getFrame()) ;
    explosion = new ExplodingSprite(sprite);
}


bool MultiSprite::collidedWith(const TwoWaySprite* obj) {
    if (strategy -> execute(*this, *obj)) {
        return true;
    } 
    return false;
}
