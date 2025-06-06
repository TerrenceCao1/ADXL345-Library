#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>

ADXL345_Handle accel;

void setup() {
    Serial.begin(9600);
}

void loop() {
    delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}