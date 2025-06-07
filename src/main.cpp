#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>


void setup() {
    Serial.begin(9600);
    Wire.begin();

    if(checkForSensor() == 1)
    {
        while(1);
    }
    turnOn();
}

void loop() {
    delay(1000);
}
