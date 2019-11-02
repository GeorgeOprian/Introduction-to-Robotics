const int redPotPin = A0;
const int redLedPin = 9;

int redPotValue = 0;
int redLedValue = 0;

const int greenPotPin = A1;
const int greenLedPin = 10;

int greenPotValue = 0;
int greenLedValue = 0;

const int bluePotPin = A2;
const int blueLedPin = 11;

int bluePotValue = 0;
int blueLedValue = 0;

void setup() {
  pinMode (redLedPin, OUTPUT);
  pinMode (greenLedPin, OUTPUT);
  pinMode (blueLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  redPotValue = analogRead(redPotPin);
  redLedValue = map(redPotValue, 0, 1023, 0, 255);

  greenPotValue = analogRead(greenPotPin);
  greenLedValue = map(greenPotValue, 0, 1023, 0, 255); 

  bluePotValue = analogRead(bluePotPin);
  blueLedValue = map(bluePotValue, 0, 1023, 0, 255);
  
  setColor(redLedValue, greenLedValue, blueLedValue);
}
void setColor (int redValue, int greenValue, int blueValue)
{
  analogWrite(redLedPin, redValue);
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
}
