#include "ADXL355.h"
#include <Wire.h>
#include <math.h>

ADXL355::ADXL355(uint8_t c=0X1D) {
	DEV_ADDRESS=c;			
}

float ADXL355::readX() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(XDATA3);
  Wire.endTransmission();
  Wire.requestFrom((int)DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
}

float ADXL355::readY() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(YDATA3);
  Wire.endTransmission();
  Wire.requestFrom((int)DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
}

float ADXL355::readZ() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(ZDATA3);
  Wire.endTransmission();
  Wire.requestFrom((int)DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
}

uint8_t ADXL355::enable(uint8_t c = 0X00) {
	Wire.beginTransmission(DEV_ADDRESS);
	if (Wire.endTransmission()==0) {
		Wire.beginTransmission(DEV_ADDRESS);
		Wire.write(0X00);
		Wire.endTransmission();	
		Wire.requestFrom((int)DEV_ADDRESS,1);
		if (Wire.available()) {
			if (Wire.read()==0XAD) {
				Serial.println("Device found");
			}
			else {
			  return 1;
			}
		}
	}
	else {
	  return 0;
	}
	Wire.beginTransmission(0X1D);
	Wire.write(POWER_CTL);
	Wire.write(c);
	Wire.endTransmission();
	range = RANGE_2G;
	return 1;
}

uint8_t ADXL355::disable() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(POWER_CTL);
  Wire.write(0X01);
  if (Wire.endTransmission()==0) {
    return 1;
  }
  else {
    return 0;
  }
}

float ADXL355::readTemperature() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(0X06);
  Wire.endTransmission();
  Wire.requestFrom((int)DEV_ADDRESS,2);
  uint32_t temperature = 0X0000;
  int t1 = Wire.available()?Wire.read():0;
  int t2 = Wire.available()?Wire.read():0;
  temperature = (t1<<8)|t2;
  float temp = 25.0;
  temp = -((float)temperature-1852)/9.05 + 25;
  return temp;
}

uint8_t ADXL355::readData() {
  while(dataReady()==0);
  uint32_t d3,d2,d1,data;
  float value;
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(XDATA3);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,9);
  
  d3 = Wire.available()?Wire.read():0;
  d2 = Wire.available()?Wire.read():0;
  d1 = Wire.available()?Wire.read():0;
  data = (d3<<16)|(d2<<8)|d1;
  data = data>>4;
  value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  x = value/0X7FFFF*range;
  
  d3 = Wire.available()?Wire.read():0;
  d2 = Wire.available()?Wire.read():0;
  d1 = Wire.available()?Wire.read():0;
  data = (d3<<16)|(d2<<8)|d1;
  data = data>>4;
  value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  y = value/0X7FFFF*range;
  
  d3 = Wire.available()?Wire.read():0;
  d2 = Wire.available()?Wire.read():0;
  d1 = Wire.available()?Wire.read():0;
  data = (d3<<16)|(d2<<8)|d1;
  data = data>>4;
  value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  z = value/0X7FFFF*range;
  
  return 0;
}

uint8_t ADXL355::dataReady() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(STATUS);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,1);
  return Wire.available()?Wire.read()&0X01:0X00;
}

float ADXL355::tilt() {
  // calculate tilt in z axis
  // if new=0 get new values
  // if new=1 use previous values
  readData();
  float sqrtA = sqrt(x*x + y*y + z*z);
  float tilt = acos(z/sqrtA);
  return tilt*180/3.14159;
}

float ADXL355::roll() {
  readData();
  return atan2(y,z)*180/3.14159;
}

float ADXL355::pitch() {
  readData();
  return atan2(-x,sqrt(x*x + y*y + z*z))*180/3.14159;
}
