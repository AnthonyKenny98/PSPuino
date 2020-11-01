#ifndef Sprite_h
#define Sprite_h

#include "Arduino.h"
#include "config.h"

class Sprite
{
  public:
    // Attributes
    u8g_uint_t xSize;
    u8g_uint_t ySize;
    u8g_uint_t x;
    u8g_uint_t y;
    u8g_uint_t xDirection;
    u8g_uint_t yDirection;
    bool show;

    // Functions
    // Sprite();
    void draw(SCREEN screen);
    void move();

  private:
    u8g_uint_t _xlim;
    u8g_uint_t _ylim;

    
};


#endif
