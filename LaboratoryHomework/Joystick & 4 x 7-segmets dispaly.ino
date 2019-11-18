const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output
const int pinSw = A2; // digital pin connected to switch output

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;
const int lowThreshold = 200;
const int highThreshold = 700;

int dpState = LOW;

int numberOnDigit = 0;
int currentDigit = 0;
int switchValue = 0;
int xValue = 0;
int yValue = 0;
int digit = 3;

int currentMillis = 0;
int previousMillis = 0;

bool joyMovedX = false;
bool joyMovedY = false;
bool switchPressed = false;


int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte digitMatrix[noOfDigits][segSize - 1] = {
  // a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int digits[noOfDisplays] = {
  pinD4, pinD3, pinD2, pinD1
};
int digitValue[noOfDisplays] = {
  0, 0, 0, 0
};
int blinkInterval = 50;
void displayNumber(byte digit, byte decimalPoint) {
  //int currentMillis = 0;
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], LOW);
}

// activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);

  }
  digitalWrite(digits[num], LOW);
}



void setup() {
  pinMode(pinSw, INPUT_PULLUP);
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++) {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  switchValue = digitalRead(pinSw);

  if (switchValue == 0) {
    switchPressed = !switchPressed;
  }
  if (switchPressed) {
    if (joyMovedY == false) {
      if (yValue < lowThreshold) {
        if (digitValue[currentDigit] > 0) {
          digitValue[currentDigit]--;
        }
        else {
          digitValue[currentDigit] = 9;
        }
      }
      if (yValue > highThreshold) {
        if (digitValue[currentDigit] < 9) {
          digitValue[currentDigit]++;
        }
        else {
          digitValue[currentDigit] = 0;
        }
      }
      joyMovedY = true;
    }
    if (yValue >= lowThreshold && yValue <= highThreshold) {
      joyMovedY = false;
    }
  }
  else {
    if (joyMovedX == false) {
      if (xValue < lowThreshold) {
        if (currentDigit > 0) {
          currentDigit--;
        }
        else {
          currentDigit = 3;
        }
      }
      if (xValue > highThreshold) {
        if (currentDigit < 3) {
          currentDigit++;
        }
        else {
          currentDigit = 0;
        }
      }
      joyMovedX = true;
    }

    if (xValue >= lowThreshold && xValue <= highThreshold) {
      joyMovedX = false;
    }
  }
  
  if (digit >= 0) {
    showDigit(digit);

    displayNumber(digitValue[digit], HIGH);
    if (digit == currentDigit) {
      digitalWrite(pinDP, HIGH);
    }
    digit--;
  } else {
    digit = 3;
  }
}
