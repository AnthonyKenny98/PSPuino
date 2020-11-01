/*
* @Author: AnthonyKenny98
* @Date:   2020-11-01 09:33:55
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2020-11-01 13:59:11
*/
#include "Game.h"

Game::Game(SCREEN screen, int animationSpeed) {
    canvasWidth = screen.getWidth();
    canvasHeight = screen.getHeight();
    _numSprites = 0;
    _animationSpeed = animationSpeed;
    gameOver = true;
}

void Game::addSprite(Sprite sprite) {
    sprites[_numSprites] = sprite;
    _numSprites++;
}

void Game::draw(SCREEN screen) {
    for (int i=0; i<_numSprites; i++) {
        if (sprites[i].show) sprites[i].draw(screen);
    }
}

void Game::drawGameOver(SCREEN screen) {
    screen.setFont(u8g_font_unifont);
    //u8g.setFont(u8g_font_osb21);
    screen.drawStr( 0, 22, "GAME OVER!");
    screen.drawStr( 0, 42, "A to restart");
}

void Game::animate() {
    if (millis() > _timeToMove) {
        _timeToMove = millis() + _animationSpeed;
    }
}