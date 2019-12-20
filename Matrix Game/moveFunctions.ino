//when turn on and off the LED that represents the food
void blinkFood(bool matrix[8][8]) {
  curBlinkFoodMillis = millis();
  if (curBlinkFoodMillis - prevBlinkFoodMillis >= blinkFoodInterval) {
    prevBlinkFoodMillis = curBlinkFoodMillis;
    matrix[foodX][foodY] = !matrix[foodX][foodY];
  }
}
//this function turns off the last LED of the snake and turns on the new position of the head
//then it moves all the snake segments to the back with a position and this is how movement is created
//also in this function, if the new position of the head is on food, the snake eats it
void moveSnake(bool matrix[8][8], int newX, int newY) {
    matrix[snake[lenSnake - 1].x][snake[lenSnake - 1].y] = false; // turns off the last led form tail
    for (int i = lenSnake - 1; i >= 1; i--) {
      snake[i] = snake[i - 1]; 
    }
    if (newX == foodX && newY == foodY) {
        eatFood(matrix);
        currentTranslationDelay -= 5;
        newFood(matrix);
        //matrix[prevFoodX][prevFoodY] = false;
    }else{
      blinkFood(matrix);
    }
    if(matrix[newX][newY] == 0){ // we don't have collision
        snake[0].x = newX;
        snake[0].y = newY;
        matrix[newX][newY] = true;

    }else{
      if(newX != foodX && newY != foodY){
        //collision
        gameOver = true;
      }
    }
}
//this set of functions moves the head of the snake on the map
//taking care to put the head of the snake on the oposite side of the row/collum
//if it will get ou of the map
void moveRight(bool matrix[8][8]) {
  if (headX < 7) {
    headX++;
  } else {
    headX = 0;
    if(youCanPassLevel){
      level++;
      levelStarted = false;
      youCanPassLevel = false;
    }
  }
  moveSnake(matrix, headY, headX);
}
void moveLeft(bool matrix[8][8]) {
  if (headX > 0) {
    headX--;
  } else {
    headX = 7;
    if(youCanPassLevel){
      level++;
      levelStarted = false;
      youCanPassLevel = false;
    }
  }
  moveSnake(matrix, headY, headX);
}
void moveUp(bool matrix[8][8]) {
  if (headY < 7) {
    headY++;
  } else {
    headY = 0;
    if(youCanPassLevel){
      level++;
      levelStarted = false;
      youCanPassLevel = false;
    }
  }
  moveSnake(matrix, headY, headX);
}
void moveDown(bool matrix[8][8]) {
  if (headY > 0) {
    headY--;
  } else {
    headY = 7;
    if(youCanPassLevel){
      level++;
      levelStarted = false;
      youCanPassLevel = false;
    }
  }
  moveSnake(matrix, headY, headX);
}
//this function takes as input the joystick movement
//and calls the functions that move the head to left/right or up/down
void moveHead(bool matrix[8][8]) {
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
    if (currentMillis - previousMillis >= currentTranslationDelay) {
      moveLeft(matrix);
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesRight) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= currentTranslationDelay) {
      moveRight(matrix);
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesUp) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= currentTranslationDelay) {
      moveUp(matrix);
      previousMillis = currentMillis;
    }
    //delay(175);
  }
  if (movesDown) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= currentTranslationDelay) {
      moveDown(matrix);
      previousMillis = currentMillis;
    }
    //delay(175);
  }

}
