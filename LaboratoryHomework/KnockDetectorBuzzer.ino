const int passiveBuzzerPin = A0;
const int activeBuzzerPin = 11;
const int pushButtonPin = 2;

int startActiveBuzzer = 0;
int passiveBuzzerValue = 0;
int activeBuzzerTone = 250;
int buttonState = 0;
int buttonPressed = 0;
int lowTreshold = 40;
int previousMillis = 0;
int interval = 5000;
int tresholdHit = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pushButtonPin, INPUT_PULLUP);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(passiveBuzzerPin, INPUT);
}

void loop() {
  passiveBuzzerValue = analogRead (passiveBuzzerPin);
  Serial.println(passiveBuzzerValue);
  if (passiveBuzzerValue >= lowTreshold && startActiveBuzzer == 0){
    tresholdHit = 1;
    previousMillis = millis();
  }
  if (tresholdHit && millis() - previousMillis == interval) {
    startActiveBuzzer = 1;
  }
  if (startActiveBuzzer){
    buttonState = digitalRead(pushButtonPin);
    Serial.println(buttonState);
    if (buttonState == 1){
       tone(activeBuzzerPin, activeBuzzerTone, 500);
      
    }else {
     noTone(activeBuzzerPin);
     startActiveBuzzer = 0;
     tresholdHit = 0;
    }
  }

  
}
