//function to eat the food, increase the snake length
//and increment the score
void eatFood (bool matrix[8][8]) {
  snake[lenSnake].x = snake[lenSnake - 1].x;
  snake[lenSnake].y = snake[lenSnake - 1].y;
  matrix[snake[lenSnake].x][snake[lenSnake].y] = true;
  lenSnake++;
  foodEaten = true;
  switch (level)
  {
    case 1:{
      score += 3;
      break;
    }
    case 2:{
      score += 4;
      break;
    }
    case 3:{
      score += 5;
      break;
    }
    case 4:{
      score += 6;
      break;
    }
    case 5:{
      score += 7;
      break;
    }
  }
}
//function for spawning new food 
void newFood(bool matrix[8][8]){
  prevFoodX = foodX;
  prevFoodY = foodY;
  foodX = millis() % 8;//random(0, 8);
  foodY = millis() % 8;//random(0, 8);
  while (matrix[foodX][foodY] == true){
    foodX = millis() % 8;//random(0, 8);
    foodY = millis() % 8;//random(0, 8);
  }
  matrix[foodX][foodY] = true;
  if (foodEaten){
    matrix[prevFoodX][prevFoodY] = false;
    foodEaten = false;
  }
  
}

