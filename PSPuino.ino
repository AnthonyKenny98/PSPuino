#include "Game.h"

//  Define Control Button Pins
#define DOWN_BUTTON 2
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 3
#define UP_BUTTON 13
#define A_BUTTON 5
#define B_BUTTON 8

// Init screen
SCREEN screen(12, 11, 9, 10); // SCK = 12, MOSI = 11, CS = 10, A0 = 9

// Init game
Game game(screen, 20);


// Declare Global Game Variables
Sprite ball;
Sprite paddle;
Sprite brick;

void drawGame() {
  for (int i = 0; i < 3; i++) {
    if (game.sprites[i].show) game.sprites[i].draw(screen);
  }
}

void setupGame() {
  
  ball.xSize = 4;
  ball.ySize = 4;
  ball.x = 0;
  ball.y = 0;
  ball.xDirection = 1;
  ball.yDirection = 1;
  ball.show = true;

  paddle.xSize = 16;
  paddle.ySize = 2;
  paddle.x = game.canvasWidth / 2 - 16 / 2;
  paddle.y = game.canvasHeight - 2;
  paddle.xDirection = 1;
  paddle.yDirection = 0;
  paddle.show = true;

  brick.xSize = 12;
  brick.ySize = 6;
  brick.x = game.canvasWidth / 4;
  brick.y = game.canvasHeight / 4;
  brick.xDirection = 0;
  brick.yDirection = 0;
  brick.show = true;

  game.addSprite(paddle);
  game.addSprite(ball);
  game.addSprite(brick);

  game.gameOver = 0;

}

//void moveBall() {
//  ball.x += ball.xDirection;
//  if (ball.x >= (game.canvasWidth - ball.xSize) || ball.x <= 0) ball.xDirection = -ball.xDirection;
//  ball.y += ball.yDirection;
//  if (ball.y <= 0) ball.yDirection = -ball.yDirection;
//  if (ball.y >= (canvasHeight - ball.ySize)) {
//    if (ball.x >= paddle.x && ball.x <= paddle.x + paddle.xSize) ball.yDirection = -ball.yDirection;
//    else gameOver = 1;
//  }
//}

//void movePaddle() {
//  if (digitalRead(LEFT_BUTTON) == LOW && paddle.x > 0) {
//    paddle.x += -2;
//  }
//  if (digitalRead(RIGHT_BUTTON) == LOW && (paddle.x + paddle.xSize) < game.canvasWidth) {
//    paddle.x += 2;
//  }
//}

//bool pointInSprite(int x, int y, Sprite box) {
//  return (x >= box.x && x <= box.x + box.xSize && y >= box.y && y <= box.y + box.ySize);
//}

//void checkCollisions() {
//  if
//  (pointInSprite(ball.x, ball.y, brick) ||
//      pointInSprite(ball.x + ball.xSize, ball.y, brick) ||
//      pointInSprite(ball.x + ball.xSize, ball.y + ball.ySize, brick) ||
//      pointInSprite(ball.x, ball.y + ball.ySize, brick)) {
//    brick.show = false;
//    ball.yDirection = -ball.yDirection;
//  }
//}

void setup(void) {

  // Assign default screen color value
  if ( screen.getMode() == U8G_MODE_R3G3B2 ) screen.setColorIndex(255); // white
  else if ( screen.getMode() == U8G_MODE_GRAY2BIT ) screen.setColorIndex(3); // max intensity
  else if ( screen.getMode() == U8G_MODE_BW ) screen.setColorIndex(1); // pixel on
  else if ( screen.getMode() == U8G_MODE_HICOLOR ) screen.setHiColorByRGB(255, 255, 255);

  // Setup control buttons as input pullups
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(A_BUTTON, INPUT_PULLUP);
  pinMode(B_BUTTON, INPUT_PULLUP);

  setupGame();
}


void loop(void) {
  screen.firstPage();
  do {
    if (game.gameOver) {
      game.drawGameOver(screen);
      if (digitalRead(A_BUTTON) == LOW) setupGame();
    }
    else {
      game.draw(screen);
      game.animate();
    }
  } while ( screen.nextPage() );
}
