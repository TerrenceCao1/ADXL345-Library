#include <Arduino.h>
#include <adxl345.h>
#include <Wire.h>


float calArray[3]; //makes the calibration array global, so the setup and loop can both use it.
void setup() {
    //allows for serial monitor and for I2C communication
    Serial.begin(9600);
    Wire.begin();

    //checking for sensor existance
    if(!checkForSensor())
    {
        while(1);
    }
    
    //powering sensor
    turnOn();
    setParams(2); //change to 2, 4, 8, 16 based on prefered range  

    //calibrating sensor
    calibrate(calArray);
}

void loop() {
    float accelArray[3]; //getAccel function gets an array and fills it with current acceleration data 
    getAccel(accelArray, calArray); //in m/s^2

    Serial.print("X ACCEL: "); Serial.print(accelArray[0]);
    Serial.print(" Y ACCEL: "); Serial.print(accelArray[1]);
    Serial.print(" Z ACCEL: "); Serial.println(accelArray[2]);
    delay(100);
}
