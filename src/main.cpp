#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>


void setup() {
    Serial.begin(9600);
    Wire.begin();

    if(!checkForSensor())
    {
        while(1);
    }
    
    turnOn();
    setParams(2); //change to 2, 4, 8, 16 based on prefered range  
}

void loop() {
    int16_t accelArray[3];
    getAccel(accelArray);

    delay(1000);
}
