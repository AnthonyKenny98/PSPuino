#ifndef Brickbreaker_h
#define Brickbreaker_h

#include "Sprite.h"
#include "Game.h"

class BrickBreaker : public Game
{
    public:
        BrickBreaker(SCREEN screen, int animationSpeed);
        void setup();
};

class Ball : public Sprite 
{
    public:
        Ball(state_t initialState, bounds_t bounds);

};

class Paddle : public Sprite 
{
    public:
        Paddle(state_t initialState, bounds_t bounds);
};

class Brick : public Sprite 
{
    public:
        Brick(state_t initialState, bounds_t bounds);
        void collide(Sprite* obstacle);

    private:
        int _lives = 4;
};

#endif