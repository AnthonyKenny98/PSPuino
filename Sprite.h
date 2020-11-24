#ifndef Sprite_h
#define Sprite_h

#include "Arduino.h"
#include "config.h"

// ==== MODES ====
// Move modes
#define MOVE_CONTROL 1
#define MOVE_INERTIA 2

// Collide modes
#define COLLIDE_NONE 0
#define COLLIDE_REBOUND 1
#define COLLIDE_VANISH 2

typedef struct bound {
    u8g_uint_t limit;
    bool gameOver;
} bound_t;

typedef struct bounds {
    bound_t xMin, xMax, yMin, yMax;
} bounds_t;

typedef struct state {
    u8g_uint_t xSize;
    u8g_uint_t ySize;
    u8g_uint_t x;
    u8g_uint_t y;
    u8g_uint_t xDirection;
    u8g_uint_t yDirection;
    bool show;
} state_t;

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
    bounds_t _bounds;

    // Functions
    Sprite(
        state_t initialState={1,1,0,0,0,0,false},
        bounds_t bounds={0,0,0,0,0,0,0,0});
    void draw(SCREEN screen);
    int move();
    virtual void collide(Sprite* obstacle);
    void reset();

  protected:
    int _moveMode;
    int _collideMode;
    state_t _initialState;
    void initSprite(state_t initialState, bounds_t bounds);
    
};


#endif
