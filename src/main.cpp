#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>


void setup() {
    Serial.begin(9600);
    Wire.begin();
    checkForSensor();
}

void loop() {
    delay(1000);
}
