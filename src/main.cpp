#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>


void setup() {
    Serial.begin(9600);
    Wire.begin();

    if(checkForSensor())
    {
        while(1);
    }
    
    turnOn();
    setParams(2); //change to 2, 4, 8, 16 based on prefered range  
}

void loop() {
    uint8_t accelArray[6];
    getAccel(accelArray);

    delay(100);
}
