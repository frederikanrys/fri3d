#include <Badge2020_TFT.h>
#include <vector>
Badge2020_TFT tft;


#define  BLACK   0x0000
//#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


#define GAMEON_UP             39
#define GAMEON_DOWN           15
#define GAMEON_LEFT           26
#define GAMEON_RIGHT          00
#define GAMEON_BUTTON         34
#define GAMEON_SELECT         36
#define GAMEON_START          32
#define GAMEON_A              13
#define GAMEON_B              12
#define GAMEON_SHOULDERLEFT   27
#define GAMEON_SHOULDERRIGHT  14

#define BUTTON_HIGH 1
#define BUTTON_LOW 0

int lastButtonState = BUTTON_LOW;
int currentButtonState = BUTTON_LOW;


int wing;
int fx, fy, fallRate;
int pillarPos, gapPos;
int score;
int highScore = 0;
bool running = false;
bool crashed = false;
bool scrPress = false;
long nextDrawLoopRunTime;

void setup(void) {
  
  // setup screen
  tft.init(240, 240);
  tft.setRotation( 2 );
  tft.fillScreen( ST77XX_CYAN );
  Serial.begin(115200);

  
  pinMode( GAMEON_DOWN, INPUT_PULLUP );
  pinMode( GAMEON_UP, INPUT_PULLUP );
  pinMode( GAMEON_LEFT, INPUT_PULLUP );
  pinMode( GAMEON_RIGHT, INPUT_PULLUP );
  pinMode( GAMEON_A, INPUT_PULLUP );

  
}

void loop() {

       if (millis() > nextDrawLoopRunTime ) {
           drawLoop();
           checkCollision();
           nextDrawLoopRunTime += 50;
        }

      bool buttonPressed = false;

    currentButtonState = digitalRead( GAMEON_A ) == LOW  > 0 ? BUTTON_HIGH : BUTTON_LOW;
    if (lastButtonState == BUTTON_HIGH && currentButtonState == BUTTON_LOW) {
      buttonPressed = true;
      Serial.println("button pressed");
    }
    lastButtonState = currentButtonState;


   if (buttonPressed) {
    if (!running) {
      startGame();
      running = true;
    } else {
      // fly up
      fallRate = -6;
    }
  }
}




void drawFlappy(int x, int y) {

  int y_pos = y;

 //laag 1
  tft.fillRect( 114, y_pos, 18, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;
  
 //laag 2
  tft.fillRect( 114, y_pos , 6, 4, ST77XX_BLACK );
  tft.fillRect( 120, y_pos, 12, 4, ST77XX_YELLOW );
  tft.fillRect( 132, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 135, y_pos, 3, 4, ST77XX_WHITE );
  tft.fillRect( 138, y_pos, 3, 4, ST77XX_BLACK );
  
  y_pos = y_pos + 4;


 //laag 3
  tft.fillRect( 111, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 114, y_pos, 15, 4, ST77XX_YELLOW );
  tft.fillRect( 129, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 132, y_pos, 9, 4, ST77XX_WHITE );
  tft.fillRect( 141, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;
  
  //laag 4
  tft.fillRect( 105, y_pos, 12, 4, ST77XX_BLACK );
  tft.fillRect( 117, y_pos, 12, 4, ST77XX_YELLOW );
  tft.fillRect( 129, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 132, y_pos, 6, 4, ST77XX_WHITE );
  tft.fillRect( 138, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 141, y_pos, 3, 4, ST77XX_WHITE );
  tft.fillRect( 144, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;

 //laag 5
  tft.fillRect( 102, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 105, y_pos, 12, 4, ST77XX_WHITE );
  tft.fillRect( 117, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 120, y_pos, 9, 4, ST77XX_YELLOW );
  tft.fillRect( 129, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 132, y_pos, 6, 4, ST77XX_WHITE );
  tft.fillRect( 138, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 141, y_pos, 3, 4, ST77XX_WHITE );
  tft.fillRect( 144, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;
  
  //laag 6
  tft.fillRect( 102, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 105, y_pos, 15, 4, ST77XX_WHITE );
  tft.fillRect( 120, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 123, y_pos, 9, 4, ST77XX_YELLOW );
  tft.fillRect( 132, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 135, y_pos, 9, 4, ST77XX_WHITE );
  tft.fillRect( 144, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;

 //laag 7
  tft.fillRect( 102, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 105, y_pos, 3, 4, ST77XX_YELLOW );
  tft.fillRect( 108, y_pos, 9, 4, ST77XX_WHITE );
  tft.fillRect( 117, y_pos, 3, 4, ST77XX_YELLOW );
  tft.fillRect( 120, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 123, y_pos, 12, 4, ST77XX_YELLOW );
  tft.fillRect( 135, y_pos, 15, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;
  
  //laag 8
  tft.fillRect( 105, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 108, y_pos, 9, 4, ST77XX_YELLOW );
  tft.fillRect( 117, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 120, y_pos, 12, 4, ST77XX_YELLOW );
  tft.fillRect( 132, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 135, y_pos, 15, 4, ST77XX_RED );
  tft.fillRect( 150, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;


 //laag 9
  tft.fillRect( 108, y_pos, 9, 4, ST77XX_BLACK );
  tft.fillRect( 117, y_pos, 12, 4, ST77XX_ORANGE );
  tft.fillRect( 129, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 132, y_pos, 3, 4, ST77XX_RED );
  tft.fillRect( 135, y_pos, 15, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;


 //laag 9
  tft.fillRect( 108, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 111, y_pos, 15, 4, ST77XX_ORANGE );
  tft.fillRect( 126, y_pos, 3, 4, ST77XX_BLACK );
  tft.fillRect( 129, y_pos, 12, 4, ST77XX_RED );
  tft.fillRect( 141, y_pos, 3, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;

 //laag 10
  tft.fillRect( 111, y_pos, 6, 4, ST77XX_BLACK );
  tft.fillRect( 117, y_pos, 12, 4, ST77XX_ORANGE );
  tft.fillRect( 129, y_pos, 15, 4, ST77XX_BLACK );

  y_pos = y_pos + 4;

 //laag 11
  tft.fillRect( 117, y_pos, 12, 4, ST77XX_BLACK );

}

void drawScore() {
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setCursor(200, 10);
    tft.print(" ");
    tft.print(score);
}

void drawBorder () {
  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;
  tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);
}

void startGame() {
  fx = 100;
  fy = 10;
  fallRate = 1;
  pillarPos = 320;
  gapPos = 90;
  crashed = false;
  score = 0;

  tft.fillScreen(ST77XX_CYAN);
  int ty = 230;
  for (int tx = 0; tx <= 300; tx += 20) {
    tft.fillTriangle(tx, ty, tx + 10, ty, tx, ty + 10, GREEN);
    tft.fillTriangle(tx + 10, ty + 10, tx + 10, ty, tx, ty + 10, YELLOW);
    tft.fillTriangle(tx + 10, ty, tx + 20, ty, tx + 10, ty + 10, YELLOW);
    tft.fillTriangle(tx + 20, ty + 10, tx + 20, ty, tx + 10, ty + 10, GREEN);
  }
}
void drawPillar(int x, int gap) {
  tft.fillRect(x + 2, 2, 46, gap - 4, GREEN);
  tft.fillRect(x + 2, gap + 92, 46, 136 - gap, GREEN);

  tft.drawRect(x, 0, 50, gap, BLACK);
  tft.drawRect(x + 1, 1, 48, gap - 2, BLACK);
  tft.drawRect(x, gap + 90, 50, 140 - gap, BLACK);
  tft.drawRect(x + 1, gap + 91 , 48, 138 - gap, BLACK);
}

void clearPillar(int x, int gap) {
  tft.fillRect(x + 45, 0, 5, gap, ST77XX_CYAN);
  tft.fillRect(x + 45, gap + 90, 5, 140 - gap, ST77XX_CYAN);
}

void clearFlappy(int x, int y) {
  tft.fillRect(x, y, 55, 50, ST77XX_CYAN);
}

void checkCollision() {
  
  int width = 55;
  int height = 50;

  //tft.fillRect(fx, fy, width, height, RED);


  // Collision with ground
  if (fy > 195) crashed = true;

  // Collision with pillar
  if (fx + width > pillarPos && fx < pillarPos + 50)
    if (fy < gapPos || fy + height > gapPos + 90)
      crashed = true;

  if (crashed) {
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(75, 75);
    tft.print("Game Over!");
    tft.setCursor(75, 125);
    tft.print("Score:");
    tft.setCursor(220, 125);
    tft.print(score);

    // stop animation
    running = false;

    // delay to stop any last minute clicks from restarting immediately
    delay(100);
  }
}



void drawLoop() {
  // clear moving items
  clearPillar(pillarPos, gapPos);
  clearFlappy(fx, fy);

  // move items
  if (running) {
    fy += fallRate;
    fallRate++;

    pillarPos -= 5;
    if (pillarPos == 0) {
      score++;
    }
    else if (pillarPos < -50) {
      pillarPos = 320;
      gapPos = random(20, 120);
    }
  }

  // draw moving items & animate
  drawPillar(pillarPos, gapPos);
  drawFlappy(fx, fy);
  drawScore();

}
