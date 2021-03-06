#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "twowaysprite.h"

//#include "weapon.h"
//#include "explodingSprite.h"

class ExplodingSprite;
class CollisionStrategy;

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string& );
  MultiSprite(const std::string&, 
              const Vector2f&,
              const Vector2f&,
              const std::vector<Frame*>& );
  MultiSprite(const MultiSprite&);
  virtual ~MultiSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void explode();
 // void reset();
  bool collidedWith(const TwoWaySprite* obj);

protected:
  ExplodingSprite* explosion;
  CollisionStrategy* strategy;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  MultiSprite& operator=(const MultiSprite&);
};
#endif
