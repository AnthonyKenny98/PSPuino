#include "Game.h"

// Init screen
SCREEN screen(12, 11, 9, 10); // SCK = 12, MOSI = 11, CS = 10, A0 = 9

// Init game
Game game(screen, 20);

// Declare Global Game Variables



// Sprite paddle(MOVE_CONTROL);
// Sprite brick(MOVE_INERTIA, COLLIDE_VANISH);

void setupBrickBreaker(int numBricks=1) {

  state_t ballInitialState = {4,4,0,0,1,1,true};
  bounds_t ballBounds = {0,false,game.canvasWidth,false,0,false,game.canvasHeight,true};
  Sprite ball(ballInitialState, ballBounds, MOVE_INERTIA, COLLIDE_REBOUND);

  state_t paddleInitialState = {
    16,2,
    game.canvasWidth / 2 - 16 / 2,
    game.canvasHeight - 2,
    0,0, true};

  Sprite paddle(
    paddleInitialState,
    {0,false,game.canvasWidth,false,0,false,game.canvasHeight,false},
    MOVE_CONTROL,
    COLLIDE_NONE);

  game.addSprite(paddle);
  game.addSprite(ball);


  Sprite brick(
    {6,4,40,40, 0,0,true},
    {0,false,game.canvasWidth,false,0,false,game.canvasHeight,false},
    MOVE_INERTIA, COLLIDE_VANISH);
  game.addSprite(brick);
  Sprite brick1(
    {6,4,20,20, 0,0,true},
    {0,false,game.canvasWidth,false,0,false,game.canvasHeight,false},
    MOVE_INERTIA, COLLIDE_VANISH);
  game.addSprite(brick1);



  // for (int i=0;i<numBricks;i++) {
  //   int x = random(0, game.canvasWidth);
  //   int y = random(game.canvasHeight/4, game.canvasHeight);
  //   Sprite brick(
  //     {6,4,x,y, 0,0,true},
  //     {0,false,game.canvasWidth,false,0,false,game.canvasHeight,false},
  //     MOVE_INERTIA, COLLIDE_VANISH);
  //     game.addSprite(brick);
  // }

}


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

  setupBrickBreaker(2);
}


void loop(void) {
  screen.firstPage();
  do {
    if (game.gameOver) {
      game.drawGameOver(screen);
      if (digitalRead(A_BUTTON) == LOW) {
        game.reset();
      }
    }
    else {
      game.draw(screen);
      game.animate();
    }
  } while ( screen.nextPage() );
}
