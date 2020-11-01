#include "Sprite.h"
void Sprite::draw(SCREEN screen) {
    screen.drawBox(x, y, xSize, ySize);
}
// void Sprite::move() {
//     x += xDirection;
//     // if (x>=)
// }
