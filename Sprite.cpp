#include "Sprite.h"

Sprite::Sprite(int moveMode, int collideMode) {
    
    xSize = 1;
    ySize = 1;
    x = 0;
    y = 0;
    setDefaultLimits();
    xDirection = 0;
    yDirection = 0;
    show = true;
    _moveMode = moveMode;
    _collideMode = collideMode;
}

void Sprite::setDefaultLimits() {
    _bounds.xMin.limit = 0;
    _bounds.xMax.limit = 1;
    _bounds.yMin.limit = 0;
    _bounds.yMax.limit = 1;
    _bounds.xMin.gameOver = false;
    _bounds.xMax.gameOver = false;
    _bounds.yMin.gameOver = false;
    _bounds.yMax.gameOver = false;
}

void Sprite::draw(SCREEN screen) {
    screen.drawBox(x, y, xSize, ySize);
}

void Sprite::collide(Sprite obstacle) {

    bool xCollision = false;
    bool yCollision = false;

    // Determine collision
    // if (x == obstacle.x || x == obstacle.x + obstacle.xSize
    //     || x + xSize == obstacle.x || x + xSize == obstacle.x + obstacle.xSize) {
    //     if (y >= obstacle.y && y <= obstacle.y + obstacle.ySize) xCollision = true;
    // }
    // if (y == obstacle.y || y == obstacle.y + obstacle.ySize
    //     || y + ySize == obstacle.y || y + ySize == obstacle.y + obstacle.ySize) {
    //     if (x >= obstacle.x && x <= obstacle.x + obstacle.xSize) yCollision = true;
    // }
    if ((x + xSize == obstacle.x ||
        x == obstacle.x + obstacle.xSize) &&
        (y + ySize >= obstacle.y &&
        y <= obstacle.y + obstacle.ySize)) {
        xCollision = true;
    }
    if ((y + ySize == obstacle.y ||
        y == obstacle.y + obstacle.ySize) &&
        (x + xSize >= obstacle.x &&
        x <= obstacle.x + obstacle.xSize)) {
        yCollision = true;
    }


    // Act on collision
    if (_collideMode == COLLIDE_VANISH && (xCollision || yCollision)) {
        xDirection = 0;
        yDirection = 0;
        show = false;
    }
    else if (_collideMode == COLLIDE_REBOUND) {
        if (xCollision) xDirection = -xDirection;
        if (yCollision) yDirection = -yDirection;
    }
}

int Sprite::move() {
    if (_moveMode == MOVE_INERTIA) {
        x += xDirection;
        if (x <= _bounds.xMin.limit) {
            if (_bounds.xMin.gameOver) return 1;
            xDirection = -xDirection;
        }
        if (x >= (_bounds.xMax.limit - xSize)) {
            if (_bounds.xMax.gameOver) return 1;
            xDirection = -xDirection;
        }
        y += yDirection;
        if (y <= _bounds.yMin.limit) {
            if (_bounds.yMin.gameOver) return 1;
                yDirection = -yDirection;
        }
        if (y >= (_bounds.yMax.limit - ySize)) {
            if (_bounds.yMax.gameOver) return 1;
                yDirection = -yDirection;
        }
    }

    else if (_moveMode == MOVE_CONTROL) {
        if (digitalRead(LEFT_BUTTON) == LOW && x > 0) x += -2;
        if (digitalRead(RIGHT_BUTTON) == LOW && (x + xSize) < _bounds.xMax.limit) x += 2;
    }
    return 0;
}
