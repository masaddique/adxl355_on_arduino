#ifndef _ADXL355_H_
#define _ADXL355_H_

#define DEVID_AD                 0x00
#define DEVID_MST                0x01
#define PARTID                   0x02
#define REVID                    0x03
#define STATUS                   0x04
#define FIFO_ENTRIES             0x05
#define TEMP2                    0x06
#define TEMP1                    0x07
#define XDATA3                   0x08
#define XDATA2                   0x09
#define XDATA1                   0x0A
#define YDATA3                   0x0B
#define YDATA2                   0x0C
#define YDATA1                   0x0D
#define ZDATA3                   0x0E
#define ZDATA2                   0x0F
#define ZDATA1                   0x10
#define FIFO_DATA                0x11
#define OFFSET_X_H               0x1E
#define OFFSET_X_L               0x1F
#define OFFSET_Y_H               0x20
#define OFFSET_Y_L               0x21
#define OFFSET_Z_H               0x22
#define OFFSET_Z_L               0x23
#define ACT_EN                   0x24
#define ACT_THRESH_H             0x25
#define ACT_THRESH_L             0x26
#define ACT_COUNT                0x27
#define FILTER                   0x28
#define FIFO_SAMPLES             0x29
#define INT_MAP                  0x2A
#define SYNC                     0x2B
#define RANGE                    0x2C
#define POWER_CTL                0x2D
#define SELF_TEST                0x2E
#define RESET                    0x2F

#define RANGE_2G 2.048
#define RANGE_4G 4.096
#define RANGE_8G 8.192

#include "Arduino.h"
#include "inttypes.h"

class ADXL355 {
private:
	uint8_t DEV_ADDRESS;
	float range;
public:
	ADXL355(uint8_t);
	float readX();
	float readY();
	float readZ();
	float readTemperature();
	uint8_t readData();
	uint8_t enable(uint8_t);
	uint8_t disable();
	uint8_t enableFIFO(uint8_t);
	uint8_t dataReady();
	float tilt(); //this tilt will be calculated in z axis
	float roll();
	float pitch();
	float x;
	float y;
	float z;

};


#endif
