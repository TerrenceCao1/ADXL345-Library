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
    float accelArray[3];
    getAccel(accelArray);
    Serial.print("X ACCEL: "); Serial.println(accelArray[0]);
    Serial.print("Y ACCEL: "); Serial.println(accelArray[1]);
    Serial.print("Z ACCEL: "); Serial.println(accelArray[2]);
    delay(1000);
}
