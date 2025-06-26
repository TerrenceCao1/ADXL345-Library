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
        return 1;
    }
    else
    {
        Serial.println("Yo this jit (ADXL345) isn't connected buddy.");
        return 0;
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

/*
    Function: getAccel -> gets acceleration data from sensor registers and stores it into buffer
    Input: 
        void
    Output: 
        Output's array 3 big of uint16_t's (arr[0] = x accel, arr[1] = y accel, arr[2] = z accel)
*/
void getAccel(float accelArray[]) //accelArray is length 3
{
    int8_t rawData[6];
    for (int i = 0; i < 6; i++)
    {
        int8_t buf = readRegister(0x32 + i);
        rawData[i] = buf;
    }
    
    int16_t RawXAccel = 0x0000;
    int16_t RawYAccel = 0x0000;
    int16_t RawZAccel = 0x0000;

    RawXAccel |= (rawData[0]);
    RawXAccel |= (rawData[1] << 8);
    RawYAccel |= (rawData[2]);
    RawYAccel |= (rawData[3] << 8);
    RawZAccel |= (rawData[4]);
    RawZAccel |= (rawData[5] << 8);


    //read the range value (to find the Scale Factor of the data)
        //0x00 -> 2g mode = 4.3
        //0x01 -> 4g mode = 8.7
        //0x02 -> 8g mode = 17.5
        //0x03 -> 16g mode = 34.5

    float scaleFactor;
    switch (uint8_t(readRegister(DATA_FORMAT) & 0x03))
    {
        case 0x00:
            scaleFactor = 3.9;
            break;
        
        case 0x01:
            scaleFactor = 7.8;
            break;
        
        case 0x02:
            scaleFactor = 15.6;
            break;
        
        case 0x03:
            scaleFactor = 31.2;
            break;
        
    }

    //raw accel values are mili-g's / LSB
    //muliply by 1000 and 9.81 for m/s^2
    float xAccel = RawXAccel * scaleFactor / 1000 * 9.8;
    float yAccel = RawYAccel * scaleFactor / 1000 * 9.8;
    float zAccel = RawZAccel * scaleFactor / 1000 * 9.8;

    accelArray[0] = xAccel;
    accelArray[1] = yAccel;
    accelArray[2] = zAccel;
}

/*
    Function setParams -> sets the settings for the sensor (and settings for interpreting data)
    Input:
        range: the range of the accelerometer (2g, 4, 8, or 16g)
    Output:
        void
*/
void setParams(int val)
{
    //function automatically sets I2C settings for the other bits 
    uint8_t byteToWrite = 0x08; //00001000, only Full Resolution bit on
    uint8_t rangeByte = 0x00;
    
    //ugly switch statement change later you bum
    switch (val)
    {
        case 2:
            rangeByte = 0x00;
            break;
        case 4:
            rangeByte = 0x01;
            break; 
        case 8:
            rangeByte = 0x02;
            break;
        case 16:
            rangeByte = 0x03;
            break;
        default:
            rangeByte = 0x00;
    }
    byteToWrite |= rangeByte;
    writeRegister(DATA_FORMAT, byteToWrite);
}

/*
    Function: Calibrate - find the offsets of the accelerometer and calibrate it
    Input: void
    Output: void
*/   

void calibrate(void){
    float avgXAccel = 0; 
    float avgYAccel = 0; 
    float avgZAccel = 0;

    float calibrationValues[3];
    for (int i = 0; i < 100; i++)
    {
        getAccel(calibrationValues);
        avgXAccel += calibrationValues[0];
        avgYAccel += calibrationValues[1];
        avgZAccel += calibrationValues[2];
        delay(10);
        Serial.println(calibrationValues[2]);
    }

    //all of these are m/s^2
    avgXAccel /= 100.;
    avgYAccel /= 100.;
    avgZAccel /= 100.;
    Serial.print("avgXAccel: "); Serial.println(avgXAccel, 3);
    Serial.print("avgYAccel: "); Serial.println(avgYAccel, 3);
    Serial.print("avgZAccel: "); Serial.println(avgZAccel, 3);

    delay(1000);
    //x m/s^2 = 6.54x LSB's (1 LSB = 15.6 milli g's, so do some math)
    int8_t offsetRegValues[3] = {avgXAccel * -6.54, avgYAccel * -6.54, avgZAccel * -6.54}; 

    //processing the offsets - if they're too small, just make them 0 lmao
    for (int i = 0; i < 3; i++)
    {
        if (offsetRegValues[i] < 0.5)
        {
            offsetRegValues[i] = 0;
        }
    }

    //THERES A FAT BUG THAT MAKES IT OVERFLOW -> small negative number + positive OFSZ -> zAccel > 256 and therefore overflows
    writeRegister(OFSX, (int8_t)round(avgXAccel*-6.54));
    writeRegister(OFSY, (int8_t)round(avgYAccel*-6.54));
    writeRegister(OFSZ, (int8_t)round(avgZAccel*-6.54));

    Serial.print("OFSX Reg: "); Serial.println(readRegister(OFSX), HEX);
    Serial.print("OFSY Reg: "); Serial.println(readRegister(OFSY), HEX);
    Serial.print("OFSZ Reg: "); Serial.println(readRegister(OFSZ), HEX);
    delay(1000);
    
    Serial.println("Calibrated!");
}