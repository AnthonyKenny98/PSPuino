#include "Game.h"
#include "Brickbreaker.h"

SCREEN screen(12, 11, 9, 10); // SCK = 12, MOSI = 11, CS = 10, A0 = 9

// Init game
BrickBreaker game(screen, 20);

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

  game.setup();
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
