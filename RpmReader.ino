#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;
byte frame[8][12];

const int inputPin = 4;

unsigned long pulseLow;
unsigned long pulseHigh;

unsigned long pulseLen;


void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  Serial.begin(9600);

  pinmode(inputPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.renderBitmap(frame, 8, 12);
  resetFrame();

  pulseLow = pulseIn(inputPin, LOW, 20000);
  pulseHigh = pulseIn(inputPin, HIGH, 20000);

  pulseLen = pulseLow + pulseHigh;

  long freq = pulseLen / 4;

  long rpm = freq;

  Serial.print("rpm: ");
  Serial.print(rpm);
  Serial.print(" pulseLen: ");
  Serial.print(pulseLen);
  Serial.println();


  // char text[5];
  // itoa(rpm, text, 10);
  // displayText(text);

  displayPixel(0, rpm/1000);
  displayPixel(1, freq);

  if (digitalRead(inputPin) == HIGH) {
    displayPixel(2, 2);
  } else if (digitalRead(inputPin) == LOW) {
    displayPixel(2, 1);
  } else {
    displayPixel(2, 0);
  }
  

}

void displayPixel(int x, int y) {
  frame[x][y] = 1;

}


void displayText(char text[]) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();
}

void resetFrame() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = 0;
    }
  }
}