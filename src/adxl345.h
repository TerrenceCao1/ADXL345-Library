#ifndef ADXL345_H_
#define ADXL345_H_

/*
We need functions to:
    Initiate communication between Arduino and Sensor
    Set parameters inside the sensor's registers
    Read data from I2C from sensor
    Parse/interpret the data
        x, y, z acceleration
*/

#define I2C_ADDRESS 0x53    //i2c device address
#define DEVID_ADDRESS 0x00  //device id (READ ONLY)
#define POWER_CTL 0x2D      //power control address (for waking up sensor)
#define DATA_FORMAT 0x31    //data format address (for setting range of data)


bool checkForSensor();
void turnOn();

void setParams(int val);

void writeRegister(uint8_t reg, uint8_t value);

uint8_t readRegister(uint8_t reg);

void getAccel(uint8_t accelArray[]);
#endif