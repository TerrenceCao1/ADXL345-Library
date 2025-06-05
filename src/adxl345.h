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

typedef struct
{
    uint8_t sensor_address;
    TwoWire *i2cPort;
} ADXL345_Handle;



bool sensorInit(ADXL345_Handle *handle, uint8_t i2cAddress, TwoWire *wirePort); //initate sensor communication 
    //load the sensor ID (check this to make sure we have connection)
    //if we get the correct sensor ID, return 0
    //else, return 1, and print error message


void setParams(uint8_t range);
    //Store sensor settings into registers
        //Range is D1 and D0 of 0x31 register:
            //2g -> value of 00, 4g -> 01, 8g -> 10, 16g -> 11
        //Make the sensor wakeup 0x08 -> 0x2D register

void writeRegister(uint8_t reg, uint8_t value);

uint8_t readRegister(uint8_t reg);


#endif