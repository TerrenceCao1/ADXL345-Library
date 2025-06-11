#ifndef ADXL345_H_
#define ADXL345_H_

#define I2C_ADDRESS 0x53    //i2c device address
#define DEVID_ADDRESS 0x00  //device id (READ ONLY)
#define POWER_CTL 0x2D      //power control address (for waking up sensor)
#define DATA_FORMAT 0x31    //data format address (for setting range of data)

/*
    Function: checkForSensor -> read the DEVID register from the sensor, check that it's the right sensor, then proceed with communicating
    Input: void
    Output: 0 if successful, 1 if unsuccessful
*/
bool checkForSensor();

/*
    Function: turnOn -> turn the sensor on, begin the I2C communication, wake the sensor by writing to POWER_CTL register
    Input: void
    Output: i2c communications get turned on :)
*/
void turnOn();

/*
    Function setParams -> sets the settings for the sensor (and settings for interpreting data)
    Input:
        range: the range of the accelerometer (2g, 4, 8, or 16g)
    Output:
        void
*/
void setParams(int val);

/*
    Function: writeRegister -> write a value to a register in the sensor
    Input:
        reg: register on the device we want to write to
        value: what we want to write to the 
    Output: void, sensor gets registers changed
*/
void writeRegister(uint8_t reg, uint8_t value);

/*
    Function readRegister -> read a value from a register in the sensor
    Input: 
        reg: register we wanna read from
    Output: 
        byte inside of that register
*/
uint8_t readRegister(uint8_t reg);

/*
    Function: getAccel -> gets acceleration data from sensor registers and stores it into buffer
    Input: 
        void
    Output: 
        Output's array 3 big of uint16_t's (arr[0] = x accel, arr[1] = y accel, arr[2] = z accel)
*/
void getAccel(int16_t accelArray[]);

/*
    Function: Calibrate - find the offsets of the accelerometer and calibrate it
    Input: void
    Output: void
*/
void calibrate(void);

#endif