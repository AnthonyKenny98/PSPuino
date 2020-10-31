#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(12, 11, 9, 10); // SCK = 12, MOSI = 11, CS = 10, A0 = 9

//  Define Control Button Pins
#define DOWN_BUTTON 2
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 3
#define UP_BUTTON 13
#define A_BUTTON 8
#define B_BUTTON 5

//== Game Variables ==
u8g_uint_t courtWidth, courtHeight; // How wide and tall is our screen?

typedef struct rectangle {
  u8g_uint_t xSize;
  u8g_uint_t ySize;
  u8g_uint_t x;
  u8g_uint_t y;
  u8g_uint_t xDirection;
  u8g_uint_t yDirection;
  bool show;
} rectangle;

rectangle ball;
rectangle paddle;
rectangle brick;

unsigned long timeToMove; // Is it time to move the ball?
int animationSpeed = 20;
int gameOver = 0;

void drawGame(rectangle rectangles[]) {
  for (int i=0; i<3; i++) {
    if (rectangles[i].show) u8g.drawBox(rectangles[i].x, rectangles[i].y, rectangles[i].xSize, rectangles[i].ySize);
  }
  //  u8g.drawBox(paddle.x, paddle.y, paddle.xSize, paddle.ySize);
}

void drawGameOver() {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "GAME OVER!");
  u8g.drawStr( 0, 42, "A to restart");
}

void setupGame() {
  ball = {
    .xSize = 4,
    .ySize = 4,
    .x = 0,
    .y = 0,
    .xDirection = 1,
    .yDirection = 1,
    .show = true
  };
  
  paddle = {
    .xSize = 16,
    .ySize = 2,
    .x = courtWidth / 2 - 16/ 2,
    .y = courtHeight - 2,
    .xDirection = 1,
    .yDirection = 0,
    .show = true
  };
  
  brick = {
    .xSize = 12,
    .ySize = 6,
    .x = courtWidth/4,
    .y = courtHeight/4,
    .xDirection = 0,
    .yDirection = 0,
    .show = true
  };
  
  gameOver = 0;
  
}

void moveBall() {
  // millis is how long since we power up the Arduino.
  ball.x += ball.xDirection;
  if (ball.x >= (courtWidth - ball.xSize) || ball.x <= 0) ball.xDirection = -ball.xDirection;
  ball.y += ball.yDirection;
  if (ball.y <= 0) ball.yDirection = -ball.yDirection;
  if (ball.y >= (courtHeight - ball.ySize)) {
    if (ball.x >= paddle.x && ball.x <= paddle.x + paddle.xSize) ball.yDirection = -ball.yDirection;
    else gameOver = 1;
  }
}

void movePaddle() {
  if(digitalRead(LEFT_BUTTON) == LOW && paddle.x > 0) {
    paddle.x += -1.5;
  }
  if(digitalRead(RIGHT_BUTTON) == LOW && (paddle.x + paddle.xSize) < courtWidth) {
    paddle.x += 1.5;
  }
}

bool pointInRectangle(int x, int y, rectangle box) {
  return (x >= box.x && x <= box.x + box.xSize && y >= box.y && y <= box.y + box.ySize);
}

void checkCollisions() {
  if 
    (pointInRectangle(ball.x, ball.y, brick) || 
    pointInRectangle(ball.x + ball.xSize, ball.y, brick) || 
    pointInRectangle(ball.x + ball.xSize, ball.y + ball.ySize, brick) || 
    pointInRectangle(ball.x, ball.y + ball.ySize, brick)) {
      brick.show = false;
      ball.yDirection = -ball.yDirection;
    }
}

void animate() {
  checkCollisions();
  if (millis() > timeToMove) {
    timeToMove = millis() + animationSpeed;// Set the next time we'll need to move the ball again.
    movePaddle();
    moveBall();
  }
}

void setup(void) {

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255); // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3); // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1); // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  // setup control buttons as input pullups
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(A_BUTTON, INPUT_PULLUP);
  pinMode(B_BUTTON, INPUT_PULLUP);
  
  
  courtWidth = u8g.getWidth();
  courtHeight =  u8g.getHeight();
  setupGame();
}

void loop(void) {
  u8g.firstPage();
  do {
    rectangle sprites[] = {ball, brick, paddle};
    if (gameOver) {
      drawGameOver();
      if (digitalRead(A_BUTTON) == LOW) setupGame();
    }
    else {
      drawGame(sprites);
      animate();
    }
  } while ( u8g.nextPage() );
}
