#include <Arduino.h>
#include <Wire.h>
#include "adxl345.h"

#define DEVID_VALUE 0xE5



bool sensorInit(ADXL345_Handle *handle, uint8_t i2cAddress, TwoWire *wirePort) //initate sensor communication 
{
    handle->sensor_address = i2cAddress;
    handle->i2cPort = wirePort;
    handle->i2cPort->begin();

    //read the device ID then check if it's DEVID_VALUE
    //return 0 if successful, 1 if unsuccessful. 
}