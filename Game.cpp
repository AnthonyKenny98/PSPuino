/*
* @Author: AnthonyKenny98
* @Date:   2020-11-01 09:33:55
* @Last Modified by:   AnthonyKenny98
* @Last Modified time: 2020-11-01 20:59:13
*/
#include "Game.h"

bool pointInSprite(int x, int y, Sprite box) {
    return (x >= box.x && x <= box.x + box.xSize && y >= box.y && y <= box.y + box.ySize);
}

Game::Game(SCREEN screen, int animationSpeed) {
    canvasWidth = screen.getWidth();
    canvasHeight = screen.getHeight();
    _numSprites = 0;
    _animationSpeed = animationSpeed;
    gameOver = false;
}

void Game::addSprite(Sprite sprite) {
    // sprite.setLimits();
    sprite._bounds.xMax.limit = canvasWidth;
    sprite._bounds.yMax.limit = canvasHeight;
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
        for (int i=0; i<_numSprites; i++) {
            if (sprites[i].move() == 1) gameOver = true;;
        }
        checkCollisions();
    }
}

void Game::checkCollisions() {
    for (int i=0; i<_numSprites; i++) {
        for (int j=0; j<_numSprites; j++) {
            if (i!=j && sprites[j].show) {
                // // determine which edges collide
                // if (pointInSprite(sprites[i].x, sprites[i].y, sprites[j]) ||
                //         pointInSprite(sprites[i].x + sprites[i].xSize, sprites[i].y, sprites[j]) ||
                //         pointInSprite(sprites[i].x + sprites[i].xSize, sprites[i].y + sprites[i].ySize, sprites[j]) ||
                //         pointInSprite(sprites[i].x, sprites[i].y + sprites[i].ySize, sprites[j])) {
                
                //     sprites[i].collide();
                // }
                sprites[i].collide(sprites[j]);
            }
        }
    }
}
