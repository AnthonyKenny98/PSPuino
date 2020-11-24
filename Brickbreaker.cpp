/*
* @Author: AnthonyKenny98
* @Date:   2020-11-23 07:36:14
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2020-11-24 20:21:09
*/

#include "Brickbreaker.h"

BrickBreaker::BrickBreaker(SCREEN screen, int animationSpeed) {
    initGame(screen, animationSpeed);
}

void BrickBreaker::setup() {
    
    // Define initial states
    state_t ballInitialState = {4,4,canvasWidth / 2 - 16 / 2,canvasHeight - 2,1,1,true};
    bounds_t ballBounds = {0,false,canvasWidth,false,0,false,canvasHeight,true};
    state_t paddleInitialState = {
        16,2,
        canvasWidth / 2 - 16 / 2,
        canvasHeight - 2,
        0,0, true};

    // Add sprites to game
    addSprite(new Ball(ballInitialState, ballBounds));
    addSprite(new Paddle(paddleInitialState, {0,false,canvasWidth,false,0,false,canvasHeight,false}));
    addSprite(new Brick({6,4,40,40, 0,0,true}, {0,false,canvasWidth,false,0,false,canvasHeight,false}));
    addSprite(new Brick({6,4,20,20, 0,0,true}, {0,false,canvasWidth,false,0,false,canvasHeight,false}));
}

Ball::Ball(state_t initialState, bounds_t bounds) {
    initSprite(initialState, bounds);
    _moveMode = MOVE_INERTIA;
    _collideMode = COLLIDE_REBOUND;
}

Paddle::Paddle(state_t initialState, bounds_t bounds) {
    initSprite(initialState, bounds);
    _moveMode = MOVE_CONTROL;
    _collideMode = COLLIDE_NONE;
}

Brick::Brick(state_t initialState, bounds_t bounds) {
    initSprite(initialState, bounds);    
    _moveMode = MOVE_INERTIA;
    _collideMode = COLLIDE_VANISH;
}

void Brick::collide(Sprite* obstacle) {
    bool xCollision = false;
    bool yCollision = false;

    // D
    if ((x + xSize == obstacle->x || x == obstacle->x + obstacle->xSize) && // If either x side collides with obstacle
        (y + ySize >= obstacle->y && y <= obstacle->y + obstacle->ySize)) { // and is within y range
        xCollision = true;
    }
    if ((y + ySize == obstacle->y || y == obstacle->y + obstacle->ySize) && // If either x side collides with obstacle
        (x + xSize >= obstacle->x && x <= obstacle->x + obstacle->xSize)) { // and is within y range
        yCollision = true;
    }

    // Act on collision
    if (xCollision || yCollision) {
        lives--;
        xSize--;
        ySize--;
        if (lives <= 0) {
            xDirection = 0;
            yDirection = 0;
            show = false;
        }
    }
}