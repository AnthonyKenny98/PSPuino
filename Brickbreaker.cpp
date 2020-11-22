/*
* @Author: AnthonyKenny98
* @Date:   2020-11-23 07:36:14
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2020-11-23 08:37:09
*/

#include "Brickbreaker.h"

BrickBreaker::BrickBreaker(SCREEN screen, int animationSpeed) {
    initGame(screen, animationSpeed);
}

void BrickBreaker::setup() {
    state_t ballInitialState = {4,4,0,0,1,1,true};
    bounds_t ballBounds = {0,false,canvasWidth,false,0,false,canvasHeight,true};
    Ball ball(ballInitialState, ballBounds);

    state_t paddleInitialState = {
        16,2,
        canvasWidth / 2 - 16 / 2,
        canvasHeight - 2,
        0,0, true};

    Paddle paddle(
        paddleInitialState,
        {0,false,canvasWidth,false,0,false,canvasHeight,false});

    Brick brick(
    {6,4,40,40, 0,0,true},
    {0,false,canvasWidth,false,0,false,canvasHeight,false});
    
    Brick brick1(
    {6,4,20,20, 0,0,true},
    {0,false, canvasWidth,false,0,false,canvasHeight,false});

    addSprite(paddle);
    addSprite(ball);
    addSprite(brick);
    addSprite(brick1);

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
