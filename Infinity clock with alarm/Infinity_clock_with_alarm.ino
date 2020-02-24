#include "LedControl.h"
#include <FastLED.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

#define LED_PIN 8
#define NUM 60
#define BRIGHTNESS 100


CRGB leds[NUM];

int clockH = 23;
int clockM = 59;
int clockS = 0;
//long prevMillis = millis();

int hourLed = 0;

const int brightness = 1;
const int dinPin = 12;
const int clkPin = 11;
const int loadPin = 10;
const int noOfDrivers = 1;
LedControl lc = LedControl(dinPin, clkPin, loadPin, noOfDrivers);

const int buttonPin[5] = {2, 3, 4, 5, 6};
bool buttonState[5] = {0, 0, 0 , 0, 0};
bool lastButtonState[5] = {0, 0, 0 , 0, 0};
bool lastDebounceTime[5] = {0, 0, 0 , 0, 0};
int debounceDelay = 500;
int numOfButtons = 5;
bool buttonPressed = false;


int readingDelay = 100;
int lastRead = 0;
bool readingInput = false;
bool dpState = true;
int blinkDpInterval = 600;
long long int lastDpBlink = 0;

int alarmM = 0;
int alarmH = 0;

bool alarmLocked = false;

//song
const int buzzerPin = 9;

tmElements_t tm;

//function to light up the LED strip 
void showLeds() {
  hourLed = (clockH * 5) % 60 + clockM / 15;
  //this formula is used to correctly display the hour on the LED strip
  //the idea is that every hour on the clock every exact hour is form 5 to 5 LEDs 
  if (hourLed > 0) { // i have to decrement the hour led because the LEDs are mumbered from 0
    hourLed--;
  }
  leds[hourLed] = CRGB(120, 0, 0);//red
  if (clockM != 0 )
    leds[clockM] = CRGB(0, 120, 0);//green
  leds[clockS] = CRGB(0, 0, 120);//blue
  for (int i = 0; i < NUM; i++) {
    if (i != hourLed && i != clockM && i != clockS) {
      leds[i] = CRGB(0, 204, 150);
    }
  }
  FastLED.show();
  clockM++;
}
//function to print the alarm time on the 4 digits 7 segment display
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
//function to input the time from the RTC module
void changeHour()
{
  if (RTC.read(tm)) {
    clockS = tm.Second;
    clockM = tm.Minute;
    clockH = tm.Hour;
  }
}
//functions to change the value of the hours/minutes of the alarm
void increase(int & value) {
  value++;
}

void decrease(int &value) {
  value--;
}
void printOnDisplay(int alarmH, int alarmM, int dp)
{
  //to correctly identify the hour and the minutes on the display I used the second dp of the display
  //if the alarm is activated the dp will blink, otherwise it will be light up
  if (alarmH < 10) {
    lc.setDigit(0, 0, (byte) 0, false);
    lc.setDigit(0, 1, (byte) alarmH, dp);
  } else {
    int firstDig = alarmH / 10 % 10;
    int lastDig = alarmH % 10;
    lc.setDigit(0, 0, (byte) firstDig, false);
    lc.setDigit(0, 1, (byte) lastDig, dp);
  }

  if (alarmM < 10) {
    lc.setDigit(0, 2, (byte) 0, false);
    lc.setDigit(0, 3, (byte) alarmM, false);
  } else {
    int firstDig = alarmM / 10 % 10;
    int lastDig = alarmM % 10;
    lc.setDigit(0, 2, (byte) firstDig, false);
    lc.setDigit(0, 3, (byte) lastDig, false);
  }

}
//function to input the buttons states
void readFromButtons()
{
  int reading;
  for (int i = 0; i < numOfButtons; i++) {
    reading = digitalRead(buttonPin[i]);
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
      }
    }
    lastButtonState[i] = reading;
  }
  if (buttonState[3]) {
    if (alarmM == 59) {
      if (alarmH == 23) {
        alarmH = -1;
      }
      increase(alarmH);
      alarmM = -1;
    }
    increase(alarmM);

  }
  if (buttonState[2]) {
    if (alarmM == 0) {
      alarmM = 60;
      if (alarmH == 0) {
        alarmH = 24;
      }
      decrease(alarmH);

    }
    decrease(alarmM);
  }
  if (buttonState[1]) {
    if (alarmH == 23) {
      alarmH = -1;
    }
    increase(alarmH);
  }
  if (buttonState[0]) {
    if (alarmH == 0) {
      alarmH = 24;
    }
    decrease(alarmH);
  }
  if (buttonState[4] == false) { //the fifth button activates the alarm
    alarmLocked = !alarmLocked;
  }

  if (alarmLocked) {
    if (millis() - lastDpBlink > blinkDpInterval) {//changing the dp state
      lastDpBlink = millis();
      dpState = !dpState;
    }
    if (alarmH == clockH && alarmM == clockM) {
      singTheAlarm();
      alarmLocked = false;
      dpState = true;
    }
  } else {
    dpState = true;
  }

}
//function to read the input of the RTC module
bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}
void setup()
{
  //led strip
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM);
  FastLED.setBrightness(BRIGHTNESS);
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
  Serial.begin(9600);
  for (int i = 0; i < numOfButtons - 1; i++) {
    pinMode(buttonPin[i], INPUT);
  }
  pinMode(buttonPin[4], INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  getTime(__TIME__);
  tmElements_t tm;
  RTC.write(tm);
  
}

void loop() {
  changeHour();
  showLeds();
  delay(2);
  long long int currentMillis = millis();
  if (currentMillis - lastRead > readingDelay) {
    lastRead = currentMillis;
    readFromButtons();
  }
  printOnDisplay(alarmH, alarmM, dpState);
  lc.shutdown(0, true);
  lc.shutdown(0, false);

}
