#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

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


//menu
int arrowPoz = 0;
int arrowPozIncreased = false;
int arrowPozDecreased = false;

int page = 0;

//categories
char start[] = "Play game";
char highScore[] = "HighScore";
char settings[] = "Settings";
char info[] = "Info";
char gameInfo[] = "bit.ly/2Pnk8wV";


//joystick
const int pinX = A0;
const int pinY = A1;
const int swPin = A2;
int xValue = 0;
int yValue = 0;
int switchValue = 0;
bool switchPressed = false;
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
int lenSnake = 3;
int passLevelLength = 9;

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
int level = 1;
bool levelStarted = false;
bool youCanPassLevel = false;


//score
int score = 0;
int highScoreStored = 0;

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
bool initialLvl1Matrix[8][8] = {
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
bool initialLvl2Matrix[8][8] = {
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
bool intialLvl3Matrix[8][8] = {
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
bool initialLvl4Matrix[8][8] = {
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
bool initialLvl5Matrix[8][8] = {
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1}
};
bool gameOver = false;
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


//translation
int initialTranslationDelay = 200;//175;
int currentTranslationDelay = 0;

int currentMillis = 0;
int previousMillis = 0;

//settings
int intialSpeed = 1;
int startingLevel = 1;
int settingsArrrowPoz = 0;

LedControl lc = LedControl(dinPin, clkPin, loadPin, noOfDrivers);

//menu
bool enterSelection = false;
bool inStart = true;
bool inHigh = false;
bool inSetings = false;
bool inInfo = false;


bool gameStarted = false;

//this function turns on the LEDs of the matrix when the snake is on those positions
void putSnakeOnMatrix(bool matrix[8][8]){
  for(int i = 0; i < lenSnake; i++){
    matrix[snake[i].x][snake[i].y] = true;
  }
}

//lights up the physical matrix from the virtual one
void printMap(bool matrix[8][8]) {
  putSnakeOnMatrix(matrix);
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, matrix[col][row]);
    }
  }
}
//this function prints a matrix which will inform you that the game is over
void printGameOverMatrix(){
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, col, row, gameOverMatrix[col][row]);
    }
  }
}
//resets the contet of the current matrix to the intial one
void reinitialize(bool initial[8][8], bool current[8][8]){
  for(int i = 0; i< 8; i++){
    for(int j = 0; j<8; j++){
      current[i][j] = initial[i][j];
    }
  }
}
//resets all the matrices when a new game is starting
void reinitializeMatrices(){
  reinitialize(initialLvl1Matrix, lvl1Matrix);
  reinitialize(initialLvl2Matrix, lvl2Matrix);
  reinitialize(intialLvl3Matrix, lvl3Matrix);
  reinitialize(initialLvl4Matrix, lvl4Matrix);
  reinitialize(initialLvl5Matrix, lvl5Matrix);
}
//this is the first page of the menu
void page1(){
    arrowPoz = 1;//pe prima linie
    
    lcd.setCursor(1, 0);
    lcd.print(start);
    lcd.setCursor(1, 1);
    lcd.print(highScore);
}
//this is the second page of the menu
void page2(){
    arrowPoz = 1;//pe prima linie
    lcd.setCursor(0, arrowPoz);
    lcd.print(">");
    lcd.setCursor(1, 0);
    lcd.print(settings);
    lcd.setCursor(1, 1);
    lcd.print(info);
}
//this function changes the pages of the menu from the arrow position
void changePage(){
    if(arrowPoz == 2){
        page++;
    }
    if(arrowPoz == -1){
        page--;
    }
    if(page == 3){
        page = 1;
    }
    if(page == -1) {
        page = 2;
    }
}
///fuction that stars the game and print Score on LCD
void startSection() {
  if (switchPressed){
    gameOver = true;
    gameStarted = false;
  }
  if(!gameOver){
    switch (level){
      case 1: {
        level1();
        break; 
      }
      case 2: {
        level2();
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
    }
    gameStarted = true;
  }else{
    printGameOverMatrix();
    gameStarted = false;
    reinitializeMatrices();
  }
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(7, 0);
  lcd.print(score);
 }
//prints the highscore on LCD when the user enters the high score section
void highScoreSection() {
  lcd.clear();
  highScoreStored = EEPROM.read(0);
  if (score > highScoreStored){
    highScoreStored = score;
  }
  lcd.print("HighScore: ");
  lcd.print(highScoreStored);
  EEPROM.write(0, highScoreStored);
}
//in this function you suppose to adjust the starting level and the speed but is unimplented
void settingsSection() {
  lcd.clear();
  lcd.setCursor(0, settingsArrrowPoz);
  lcd.print(">");
  lcd.setCursor(1, 0);
  lcd.print("StartingSpeed: ");
  lcd.setCursor(15, 0);
  lcd.print(intialSpeed);
  /*lcd.setCursor(1, 1);
  lcd.print("StartingLevel: ");
  lcd.setCursor(15, 1);
  lcd.print(startingLevel);*/
  /*



            Daca se misca Y creste viteza initiala cred ca ar fi suficient pentru setari
            Modifica translation delay si scorul



  */
}
//prints the information of the game such as creator's name, game name and a github link
void infoSection(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("George  *Snake*");
  lcd.setCursor(0, 1);
  lcd.print(gameInfo);

}
//function that stops the game
void gameIsOver() {
  gameStarted = false;
  gameOver = false;
}
///this function selects the section to display on the LCD 
void sectionNav() {
  if (page == 0){
    if (arrowPoz == 0){
      startSection();
      gameStarted = true;
    }else{
      highScoreSection();
    }
  }else{
    if (arrowPoz == 0){
      settingsSection();
    }else{
      infoSection();
    }
  }
}
//this functon moves the arrow, selects the page and prints the main interface of the menu
void menuNav () {
  if (xValue > highThreshold) {
    enterSelection = true;
  }
  if (xValue < lowThreshold) {
    enterSelection = false;
  }
  if (movedY == false) {
    if (yValue < lowThreshold) {
      arrowPoz++;
      arrowPozIncreased = true;
    }
    if (yValue > highThreshold) {
      arrowPoz--;
      arrowPozDecreased = true;
    }
    movedY = true;
  }
  if (yValue >= lowThreshold && yValue <= highThreshold) {
    movedY = false;
    lcd.clear();
  }
  if (enterSelection == false) {
    if (arrowPoz == 2) {
      if (page == 1) {
        page = 0;
        arrowPoz = 0;
      } else {
        page++;
        arrowPoz = 0;
      }
      if (page == 0) {
        arrowPoz = 0;
      }
    }

    if (arrowPoz == -1) {
      if (page == 0) {
        arrowPoz = 1;
        page = 1;
      }
      else {
        page--;
        arrowPoz = 1;
      }
      if (page == 1) {
        arrowPoz = 1;
      }
    }
    page = page % 2;
    lcd.setCursor(0, arrowPoz);
    lcd.print(">");
    if (page == 0) {
      lcd.setCursor(1, 0);
      lcd.print(start);
      lcd.setCursor(1, 1);
      lcd.print(highScore);
    }
    else {
      lcd.setCursor(1, 0);
      lcd.print(settings);
      lcd.setCursor(1, 1);
      lcd.print(info);
    }
  }else{
    sectionNav();
  }
  delay(50);
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
  highScoreStored = EEPROM.read(0);
  if(highScoreStored == 255){
    EEPROM.write(0, 0);
    highScoreStored = EEPROM.read(0);
  }
  //EEPROM.write(0,0);
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  switchValue = analogRead(swPin);
  
  if(!gameStarted){
    menuNav();
  }else{
      startSection();
  }  
}
