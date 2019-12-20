//sets the matrix that will be dispalyed at every level
//initialize the snake, every new level the length of the snake will be 3
//sets the default movement of the snake to left
//spawns food on map
void initializeLevel(bool matrix[8][8]){
  headX = initialialHeadX;
  headY = initialialHeadY;
  snake[0].x = headY;
  snake[0].y = headX;

  snake[1].x = headY;
  snake[1].y = headX - 1;

  snake[2].x = headY;
  snake[2].y = headX - 2;
  lenSnake = 3;
  movesLeft = false;
  movesRight = true;
  movesUp = false;
  movesDown = false;
  currentTranslationDelay = initialTranslationDelay;
  matrix[foodX][foodY] = true;
  prevFoodX = foodX;
  prevFoodY = foodY;
  youCanPassLevel = false;
}
//functions level1...5 call initializeLevel() before starting the level
//they also verify if the game is over
void level1(){
  if (!levelStarted){
    initializeLevel(lvl1Matrix);
    levelStarted = true;
  }
  if(!gameOver){
    moveHead(lvl1Matrix);
    printMap(lvl1Matrix);
    if (lenSnake >= passLevelLength){
      youCanPassLevel = true;
    }
  }else{
    printGameOverMatrix();
  }
}
void level2(){
  if (!levelStarted){
    initializeLevel(lvl2Matrix);
    levelStarted = true;
  }
  if(!gameOver){
    moveHead(lvl2Matrix);
    printMap(lvl2Matrix);
    if (lenSnake >= passLevelLength){
      youCanPassLevel = true;
    }
  }else{
    printGameOverMatrix();
  }
}
void level3(){
  if (!levelStarted){
    initializeLevel(lvl3Matrix);
    levelStarted = true;
  }
  if(!gameOver){
    moveHead(lvl3Matrix);
    printMap(lvl3Matrix);
    if (lenSnake >= passLevelLength){
      youCanPassLevel = true;
    }
  }else{
    printGameOverMatrix();
  }
}
void level4(){
  if (!levelStarted){
    initializeLevel(lvl4Matrix);
    levelStarted = true;
  }
  if(!gameOver){
    moveHead(lvl4Matrix);
    printMap(lvl4Matrix);
    if (lenSnake >= passLevelLength){
      youCanPassLevel = true;
    }
  }else{
    printGameOverMatrix();
  }
}
void level5(){
  if (!levelStarted){
    initializeLevel(lvl5Matrix);
    levelStarted = true;
  }
  if(!gameOver){
    moveHead(lvl5Matrix);
    printMap(lvl5Matrix);
    /*if (lenSnake >= passLevelLength){
      youCanPassLevel = true;
    }*/
  }else{
    printGameOverMatrix();
  }
}