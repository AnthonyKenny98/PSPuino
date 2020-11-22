#ifndef Game_h
#define Game_h

#include "Sprite.h"
#include <stdbool.h>

#define MAX_SPRITES 10
#define MAX_PLAYERS 2

class Game {
  public:
    char* name;
    int score;
    bool gameOver;
    u8g_uint_t canvasWidth;
    u8g_uint_t canvasHeight;
    Sprite* sprites[MAX_SPRITES];
    // Sprite* sprote;

    Game(SCREEN screen, int animationSpeed);
    void draw(SCREEN screen);
    void drawGameOver(SCREEN screen);
    void addSprite(Sprite sprite);
    void animate();
    void checkCollisions();
    void reset();

  private:
    int _animationSpeed;
    unsigned long _timeToMove; 
    int _numSprites;
};

#endif
