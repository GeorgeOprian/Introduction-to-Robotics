#include "LedControl.h"

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
bool movedX = false;
bool movedY = false;
const int lowThreshold = 200;
const int highThreshold = 900;

//snake
int headX = 3;
int headY = 2;
int prevHeadX = 0;
int prevHeadY = 0;
bool movesLeft = false;
bool movesRight = true;
bool movesUp = false;
bool movesDown = false;
int lenSnake = 3;//4;

//food
bool foodEaten = false;
int foodX = 2;//2;
int foodY = 6;//6;
int prevFoodX;
int prevFoodY;
int blinkFoodInterval = 200;
int curBlinkFoodMillis = 0;
int prevBlinkFoodMillis = 0;


struct bodySegment {
  int x;
  int y;
};

bodySegment snake[63];


//map
bool matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};


//translation
int translationDelay = 175;

int currentMillis = 0;
int previousMillis = 0;


LedControl lc = LedControl(dinPin, clkPin, loadPin, noOfDrivers);

void blinkFood() {
  curBlinkFoodMillis = millis();
  if (curBlinkFoodMillis - prevBlinkFoodMillis >= blinkFoodInterval) {
    prevBlinkFoodMillis = curBlinkFoodMillis;
    matrix[foodX][foodY] = !matrix[foodX][foodY];
  }
}

void eatFood () {
  snake[lenSnake].x = snake[lenSnake - 1].x;
  snake[lenSnake].y = snake[lenSnake - 1].y;
  matrix[snake[lenSnake].x][snake[lenSnake].y] = true;
  lenSnake++;
  foodEaten = true;
}

void newFood(){
  prevFoodX = foodX;
  prevFoodY = foodY;
  foodX = random(0, 8);//millis() % 8;
  foodY = random(0, 8);//millis() % 8;
  matrix[foodX][foodY] = true;
  if (foodEaten){
    matrix[prevFoodX][prevFoodY] = false;
    foodEaten = false;
  }
}

void moveSnake(int newX, int newY) {
  //if(!collision()){
    matrix[snake[lenSnake - 1].x][snake[lenSnake - 1].y] = false; // turns off the last led form tail
    for (int i = lenSnake - 1; i >= 1; i--) {
      snake[i] = snake[i - 1];
      matrix[snake[i + 1].x][snake[i + 1].y] = true;
      
    }
    if (newX == foodX && newY == foodY) {
        eatFood();
        //newFood();
        //matrix[prevFoodX][prevFoodY] = false;
    }else{
      if (!foodEaten){
        //blinkFood();
      }
      if(matrix[newX][newY] == 0){ // we don't have collision
        snake[0].x = newX;
        snake[0].y = newY;
        matrix[newX][newY] = true;
        //matrix[snake[0].x][snake[0].y] = true;
      }else{

      }
    }
    
  //}

}


void moveRight() {
  //prevHeadX = headX;
  //prevHeadY = headY;
  if (headX < 7) {
    headX++;
  } else {
    headX = 0;
  }
  moveSnake(headY, headX);
  //matrix[headY][headX] = true;
  //matrix[prevHeadY][prevHeadX] = false;
  //lc.setLed(0, prevHeadY, prevHeadX, false);
  //lc.setLed(0, headY, headX, true);
}
void moveLeft() {
  //prevHeadX = headX;
  //prevHeadY = headY;
  if (headX > 0) {
    headX--;
  } else {
    headX = 7;
  }
  moveSnake(headY, headX);
  //matrix[headY][headX] = true;
  // matrix[prevHeadY][prevHeadX] = false;
  //lc.setLed(0, prevHeadY, prevHeadX, false);
  //lc.setLed(0, headY, headX, true);
}
void moveUp() {
  //prevHeadX = headX;
  //prevHeadY = headY;
  if (headY < 7) {
    headY++;
  } else {
    headY = 0;
  }
  moveSnake(headY, headX);
  //matrix[headY][headX] = true;
  //matrix[prevHeadY][prevHeadX] = false;

  //lc.setLed(0, prevHeadY, prevHeadX, false);
  //lc.setLed(0, headY, headX, true);
}
void moveDown() {
  //prevHeadX = headX;
  //prevHeadY = headY;
  if (headY > 0) {
    headY--;
  } else {
    headY = 7;
  }
  moveSnake(headY, headX);
  //matrix[headY][headX] = true;
  //matrix[prevHeadY][prevHeadX] = false;
  //lc.setLed(0, prevHeadY, prevHeadX, false);
  //lc.setLed(0, headY, headX, true);
}

void moveHead() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  ///am inversat apelul de stanga cu cel de dreata pt ca era mergea invers
  if (movedX == false && movedY == false) {
    if (xValue > highThreshold && (movesUp || movesDown)) {
      //moveRight();
      movedX = true;
      movesLeft = false;
      movesRight = true;
      movesUp = false;
      movesDown = false;
    }
    if (xValue < lowThreshold && (movesUp || movesDown)) {
      //moveLeft();
      movedX = true;
      movesLeft = true;
      movesRight = false;
      movesUp = false;
      movesDown = false;
    }
  }

  if (movedY == false && movedX == false) {
    if (yValue > highThreshold && (movesRight || movesLeft)) {
      //moveDown();
      movedY = true;
      movesLeft = false;
      movesRight = false;
      movesUp = false;
      movesDown = true;
    }
    if (yValue < lowThreshold && (movesRight || movesLeft)) {
      //moveUp();
      movedY = true;
      movesLeft = false;
      movesRight = false;
      movesUp = true;
      movesDown = false;
    }
  }

  if (yValue >= lowThreshold && yValue <= highThreshold && movedY) {
    movedY = false;
  }

  if (xValue >= lowThreshold && xValue <= highThreshold && movedX) {
    movedX = false;
  }
  if (movesLeft) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= translationDelay) {
      moveLeft();
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesRight) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= translationDelay) {
      moveRight();
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesUp) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= translationDelay) {
      moveUp();
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesDown) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= translationDelay) {
      moveDown();
      previousMillis = currentMillis;
    }
    //delay(175);
  }

}

void printMap() {
  /*if (foodX != 0 && foodY != 0) {
    matrix[0][0] = 0;
  }*/
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      //Serial.print(matrix[row][col]);
      //Serial.print(" ");

      lc.setLed(0, col, row, matrix[col][row]);
    }
    //Serial.println("");
  }
  //matrix[prevFoodX][prevFoodY] = false;
  //Serial.println("");

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
  ///la initializare vreau ca linia sa fie aceeasi, doar coloana sa varieze
  snake[0].x = headY;
  snake[0].y = headX;

  snake[1].x = headY;
  snake[1].y = headX - 1;

  snake[2].x = headY;
  snake[2].y = headX - 2;
  //snake[3].x = headY;
  //snake[3].y = headX - 3;
  //here I put the snake on the map
  /*matrix[snake[0].x][snake[0].y] = true;
    matrix[snake[1].x][snake[1].y] = true;
    matrix[snake[2].x][snake[2].y] = true;'
  */
  matrix[foodX][foodY] = true;

  // matrix[snake[3].x][snake[2].y] = true;
  /*for (int i =0; i < 3; i++){
    Serial.print("snakeX = ");
    Serial.println(snake[i].x);
    Serial.print(" snakeY = ");
    Serial.println(snake[i].y);
    }*/
  /*delay(50);
    for(int row = 0; row < 8; row++){
    for(int col = 0; col < 8; col++){
      lc.setLed(0, col, row, false);
      delay(25);
    }
    }*/
  //matrix[headY][headX] = true;
  // lc.setLed(0, headY, headX, true);
  //lc.setLed(0, 0, 1, true);
  //lc.setLed(0, 0, 3, true);
  //lc.setLed(0, 1, 7, true);
}

void loop() {
  moveHead();
  // moveSnake();
  //blinkFood();
  printMap();
  if (foodEaten){
    newFood();
  }
  //delay(00);
  //matrix[prevFoodX][prevFoodY] = false;
  ///snake states
  /*for (int i = 0; i < 3; i++) {
    Serial.print("snakeX = ");
    Serial.println(snake[i].x);
    Serial.print(" snakeY = ");
    Serial.println(snake[i].y);

    Serial.println("******");
  }*/
  /*for (int i =0; i < 3; i++){
    Serial.print("snakeX = ");
    Serial.print(snake[i].x);
    Serial.print(" snakeY = ");
    Serial.print(snake[i].y);
    }*/
  ///pui in matrice 1 pe pozitia headX headY
}
