#ifndef Game_h
#define Game_h

#include "Sprite.h"
#include <stdbool.h>

#define MAX_SPRITES 10

class Game {
  public:
    char* name;
    int score;
    bool gameOver;
    u8g_uint_t canvasWidth;
    u8g_uint_t canvasHeight;
    int _numSprites;
    Sprite sprites[MAX_SPRITES];

    Game(SCREEN screen, int animationSpeed);
    void draw(SCREEN screen);
    void drawGameOver(SCREEN screen);
    void addSprite(Sprite sprite);
    void animate();

  private:
    int _animationSpeed;
    unsigned long _timeToMove; 
    

  public:


};

#endif
