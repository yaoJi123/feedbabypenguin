#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "sprite.h"
//#include "explodingSprite.h"

class ExplodingSprite;
class CollisionStrategy;

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite(const std::string&);
  TwoWaySprite(const TwoWaySprite&);
  virtual ~TwoWaySprite(); 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
   void up();
   void down();
   void left();
   void right();
   void stopX();
   void stopY();
   void stopAll();   
   void explode();
   void reset();
   bool collidedWith(const Sprite* obj);
   int getScore() const {return X();}

protected:
  ExplodingSprite* explosion;
  CollisionStrategy* strategy;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned lastFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  TwoWaySprite& operator=(const TwoWaySprite&);
};
#endif
