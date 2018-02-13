#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <string>
#include <SDL.h>

class Frame {
public:
  Frame( SDL_Surface*);

  // ExplodingSprite::makeChunks needs this constructor if
  // we are not going to keep each chunk on a separate surface:
  Frame(const Frame&);
  Frame( SDL_Surface* spr, Uint16 w, Uint16 h, Sint16 src_x, Sint16 src_y);
  Frame& operator=(const Frame&);

  SDL_Surface* getSurface() const { return surface; }
  void draw(Sint16 x, Sint16 y) const;

  // Chunk::draw needs the next function if the chunk is not
  // on a separate surface:
  void draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const;
  void draw(Sint16 x, Sint16 y, double angle) const;

  Uint16 getWidth()  const { return surface->w; }
  Uint16 getHeight() const { return surface->h; }
private:
  SDL_Surface * screen;
  SDL_Surface * surface;
  Uint16 width;
  Uint16 height;
  Sint16 sourceX;
  Sint16 sourceY;
  Frame();
};

#endif
