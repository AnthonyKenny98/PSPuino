#include "Sprite.h"

Sprite::Sprite(state_t initialState, bounds_t bounds) {
    
    initSprite(initialState, bounds);
    _collideMode = COLLIDE_NONE;
    _moveMode = MOVE_INERTIA;

}

void Sprite::initSprite(state_t initialState, bounds_t bounds) {
    
    xSize = initialState.xSize;
    ySize = initialState.ySize;
    x = initialState.x;
    y = initialState.y;
    xDirection = initialState.xDirection;
    yDirection = initialState.yDirection;
    show = initialState.show;

    _bounds = bounds;
    _initialState = initialState;
}

void Sprite::draw(SCREEN screen) {
    screen.drawBox(x, y, xSize, ySize);
}

void Sprite::collide(Sprite* obstacle) {

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

void Sprite::reset() {
    xSize = _initialState.xSize;
    ySize = _initialState.ySize;
    x = _initialState.x;
    y = _initialState.y;
    xDirection = _initialState.xDirection;
    yDirection = _initialState.yDirection;
    show = _initialState.show;
}
