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

#define I2C_ADDRESS 0x53    //device address
#define POWER_CTL 0x2D      //power control address (for waking up sensor)
#define DATA_FORMAT 0x31    //data format address (for setting range of data)

void sensorInit() //initate sensor communication
{
    //load the sensor ID (check this to make sure we have connection)
    //Store sensor settings into registers
        //Range is D1 and D0 of 0x31 register:
            //2g -> value of 00, 4g -> 01, 8g -> 10, 16g -> 11
        //Make the sensor wakeup 0x08 -> 0x2D register
}


#endif