void blinkFood(bool matrix[8][8]) {
  curBlinkFoodMillis = millis();
  if (curBlinkFoodMillis - prevBlinkFoodMillis >= blinkFoodInterval) {
    prevBlinkFoodMillis = curBlinkFoodMillis;
    matrix[foodX][foodY] = !matrix[foodX][foodY];
  }
}

void eatFood (bool matrix[8][8]) {
  snake[lenSnake].x = snake[lenSnake - 1].x;
  snake[lenSnake].y = snake[lenSnake - 1].y;
  matrix[snake[lenSnake].x][snake[lenSnake].y] = true;
  lenSnake++;
  foodEaten = true;
}

void newFood(bool matrix[8][8]){
  prevFoodX = foodX;
  prevFoodY = foodY;
  foodX = random(0, 8);//millis() % 8;
  foodY = random(0, 8);//millis() % 8;
  while (matrix[foodX][foodY] == true){
    foodX = random(0, 8);//millis() % 8;
    foodY = random(0, 8);//millis() % 8;
  }
  matrix[foodX][foodY] = true;
  if (foodEaten){
    matrix[prevFoodX][prevFoodY] = false;
    foodEaten = false;
  }
  
}

