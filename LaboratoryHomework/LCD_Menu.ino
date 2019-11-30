#include <LiquidCrystal.h>

const int rsPin = 12;
const int ePin = 11;
const int d4Pin = 5;
const int d5Pin = 4;
const int d6Pin = 3;
const int d7Pin = 2;

const int pinX = A0;
const int pinY = A1;
const int pinSw = A2;

int switchValue = 0;
int xValue = 0;
int yValue = 0;

const int lowThreshold = 250;
const int highThreshold = 700;

bool enterSelection = false;
//bool exitSelection = false;
bool movedX = false;
bool movedY = false;
int arrowPoz = 0;
int arrowPozIncreased = false;
int arrowPozDecreased = false;

char start[] = "Start Game";
char highScore[] = "HighScore";
char settings[] = "Settings";

char endingMessage[] = "Congratulations, you finished the game. Press button to exit.";
//Sections
bool inStart = true;
bool inHigh = false;
bool inSetings = false;
int page = 0;

int startingLevel = 0;
int lives = 3;
int level = 0;
int score = 0;
int hiScore = 0;
int incrementInterval = 2000;
int gamecurrPrintMillis = 0;
int gameprevPrintMillis = 0;
int gameStartedAtMillis = 0;
int gameOverInterval = 10000;
int thisChar = 0;


bool gameStarted = false;
bool gameOver = false;
int currentPrintMillis = 0;
int prevPrintMillis = 0;
int scrollInterval = 500;
LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);
void menuNav () {
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
  if (movedX == false) {
    if (arrowPoz == 2) {
      if (page == 1) {
        page = 0;
        arrowPoz = 0;
      } else {
        page++;
        arrowPoz = 1;
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
        arrowPoz = 0;
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
      lcd.print(highScore);
      lcd.setCursor(1, 1);
      lcd.print(settings);
    }
  }

}

void startSection() {
  //lcd.print("Sunt in Start");
  if (!gameOver) {
    if (!gameStarted) {
      gameStartedAtMillis = millis();
      level = startingLevel;
      gameStarted = true;
    }
    lcd.print("Lives:");
    lcd.setCursor(7, 0);
    lcd.print(lives);

    lcd.setCursor(9, 0);
    lcd.print("Lvl:");
    lcd.setCursor(14, 0);
    lcd.print(level);

    score = level * 3;
    lcd.setCursor(3, 1);
    lcd.print("Score:");
    lcd.setCursor(10, 1);
    lcd.print(score);

    if (gameStarted) {
      gamecurrPrintMillis = millis();
      if (gamecurrPrintMillis - gameprevPrintMillis >= incrementInterval) {
        gameprevPrintMillis = gamecurrPrintMillis;
        level++;
      }
    }
    if (gamecurrPrintMillis - gameStartedAtMillis >= gameOverInterval) {
      gameOver = true;
    }
  }
}

/*Actualizeaza highscore*/

void highScoreSection() {
  //lcd.print("Sunt in HighScore");
  lcd.print("HighScore:");
  if (score > hiScore){
    hiScore = score;
  }
  lcd.setCursor(11, 0);
  lcd.print(hiScore);
}
void settingsSection() {
  //lcd.print("Sunt in Settings");
  //lcd.setCursor(0, 0);
  lcd.print("Starting level: ");
  lcd.setCursor(0, 1);
  //lcd.print(0, 1);
  lcd.print(startingLevel);
  if (movedY == false) {
    if (yValue < lowThreshold) {
      if (startingLevel > 0) {
        startingLevel--;
      }
    }
    if (yValue > highThreshold) {
      if (startingLevel < 10) {
        startingLevel++;
      }
    }
    movedY = true;
  }
  if (yValue >= lowThreshold && yValue <= highThreshold) {
    movedY = false;
    //lcd.clear();
  }
  level = startingLevel;
}
void gameIsOver() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game over!");
  lcd.setCursor(11, 0);
  lcd.print("Press");
  lcd.setCursor(0, 1);
  lcd.print("button to exit.");
  //lcd.clear();
  switchValue = digitalRead(pinSw);
  if (!switchValue) {
    movedX = false;
    gameOver = false;
    gameStarted = false;
  }
}
void sectionNav() {
  if (enterSelection) {
    if (((page == 0 && arrowPoz == 0) || (page == 1 && arrowPoz == 1))) {
      if (page == 0 && arrowPoz == 0) {
        inStart = true;
        inHigh = false;
        inSetings = false;
      } else if (page == 1 && arrowPoz == 1) {
        inStart = false;
        inHigh = false;
        inSetings = true;

      }
    } else {
      inStart = false;
      inHigh = true;
      inSetings = false;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    if (inStart) {
      startSection();
    }
    if (inHigh) {
      highScoreSection();
    }
    if (inSetings) {
      settingsSection();
    }
  } else {
    inStart = false;
    inHigh = false;
    inSetings = false;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  lcd.begin(16, 2);

}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if (movedX == false) {
    if (xValue > highThreshold) {
      enterSelection = true;
      movedX = true;
    }

  }
  if (movedX == false) {
    menuNav();
  }
  else {
    sectionNav();
  }
  if (gameOver) {
    gameIsOver();

    //mesajul o sa fie mai lung decat dimensiunea dispaly-ului => fa cu scroll
    //aici o sa bag partea de switch
    //switchul trebuie sa ma intoarca in meniu
    if (score > hiScore){
      hiScore = score;
    }
  }
  if (xValue < lowThreshold) {
    movedX = false;
    enterSelection = false;
  }
  delay(20);

}
