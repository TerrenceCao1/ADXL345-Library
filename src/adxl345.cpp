#include <Arduino.h>
#include <Wire.h>
#include "adxl345.h"

#define DEVID_VALUE 0xE5

/*
    Function: checkForSensor -> read the DEVID register from the sensor, check that it's the right sensor, then proceed with communicating
    Input: void
    Output: 0 if successful, 1 if unsuccessful
*/
bool checkForSensor()
{
    uint8_t checkRegister = readRegister(DEVID_ADDRESS);

    if (checkRegister == DEVID_VALUE)
    {
        Serial.println("Sensor Detected!");
        return 0;
    }
    else
    {
        Serial.println("Yo this jit (ADXL345) isn't connected buddy.");
        return 1;
    }
}

/*
    Function: turnOn -> turn the sensor on, begin the I2C communication, wake the sensor by writing to POWER_CTL register
    Input: void
    Output: i2c communications get turned on :)
*/
void turnOn()
{
    Wire.begin(); //begin I2C comms
    //wake the sensor
        //write to POWER_CTL register (turn on measure, autosleep, wakeups)
    writeRegister(POWER_CTL, 0b00011000);
    uint8_t powerReg = readRegister(POWER_CTL);
    Serial.println(powerReg);
    if (powerReg == 0x18)
    {
        Serial.println("Sensor on!");
    }
}

/*
    Function: writeRegister -> write a value to a register in the sensor
    Input:
        reg: register on the device we want to write to
        value: what we want to write to the 
    Output: void, sensor gets registers changed
*/
void writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(I2C_ADDRESS); //writes start bit and device address
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

/*
    Function readRegister -> read a value from a register in the sensor
    Input: 
        reg: register we wanna read from
    Output: 
        byte inside of that register
*/
uint8_t readRegister(uint8_t reg)
{
    //to read from register we must first send slave address, then register we want to access
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();

    //then we send the slave address (with a read bit), then read the data
    //contains both beginTransmission, and endTransmission for the reading part
    Wire.requestFrom(I2C_ADDRESS, 1);
    uint8_t result = Wire.read();
    return result;
}