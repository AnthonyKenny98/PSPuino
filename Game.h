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
    Sprite* sprites[MAX_SPRITES];

    Game(SCREEN screen=NULL, int animationSpeed=NULL);
    void draw(SCREEN screen);
    void drawGameOver(SCREEN screen);
    void addSprite(Sprite sprite);
    void animate();
    void checkCollisions();
    void reset();

  protected:
    int _animationSpeed;
    unsigned long _timeToMove; 
    int _numSprites;
    void initGame(SCREEN screen, int animationSpeed);
};

#endif
