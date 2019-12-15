#include "LedControl.h"

#include <LiquidCrystal.h>

//LCD display
const int rsPin = 9;
const int ePin = 8;
const int d4Pin = 5;
const int d5Pin = 4;
const int d6Pin = 3;
const int d7Pin = 2;

LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);

//LED Matrix
const int brightness = 1;
const int dinPin = 12;
const int clkPin = 11;
const int loadPin = 10;
const int noOfDrivers = 1;

//joystick
const int pinX = A0;
const int pinY = A1;
const int swPin = A2;
int xValue = 0;
int yValue = 0;
int switchValue = 0;
bool movedX = false;
bool movedY = false;
const int lowThreshold = 200;
const int highThreshold = 900;

//snake
struct bodySegment {
  int x;
  int y;
};
bodySegment snake[63];
int initialialHeadX = 3;
int initialialHeadY = 3;
int headX = 3;
int headY = 3;
int prevHeadX = 0;
int prevHeadY = 0;
bool movesLeft = false;
bool movesRight = true;
bool movesUp = false;
bool movesDown = false;
int lenSnake = 3;//4;
int passLevelLength = 6;//9;

//food
bool foodEaten = false;
int foodX = 3;//2;
int foodY = 6;//6;
int prevFoodX;
int prevFoodY;
int blinkFoodInterval = 200;
int curBlinkFoodMillis = 0;
int prevBlinkFoodMillis = 0;

//levels
int level = 1;//2;
bool levelStarted = false;
bool youCanPassLevel = false;



//map
//level 1
bool lvl1Matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
///level 2
bool lvl2Matrix[8][8] = {
  {1, 1, 1, 0, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 0, 0, 1, 1, 1}
};
//level 3
bool lvl3Matrix[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};
//level 4
bool lvl4Matrix[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};

//level 5
bool lvl5Matrix[8][8] = {
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1}
};


bool gameOverMatrix[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 0, 1}
};
bool gameOver = false;

//translation
int initialTranslationDelay = 200;//175;
int currentTranslationDelay = 0;

int currentMillis = 0;
int previousMillis = 0;


LedControl lc = LedControl(dinPin, clkPin, loadPin, noOfDrivers);

void printMap(bool matrix[8][8]) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, matrix[col][row]);
    }
  }

}

void printGameOverMatrix(){
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, gameOverMatrix[col][row]);
    }
  }
}

void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);//turn off power saving, enables display
  lc.setIntensity(0, brightness);//sets brightness (between 0, 15)
  lc.clearDisplay(0);
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, true);
      delay(25);
    }
  }
  lcd.begin(16, 2);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ci faci uai?");
}

void loop() {
  switch (level){
    case 1: {
      level1();
      break; 
    }
    case 2: {
      level1();
      break;
    }
    case 3: {
      level3();
      break;
    }
    case 4: {
      level4();
      break;
    }
    case 5: {
      level5();
      break;
    }
    default:{
      //ai terminat jocul
    }
  }
}
