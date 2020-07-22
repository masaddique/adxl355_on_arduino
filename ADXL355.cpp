#include "ADXL355.h"
#include <Wire.h>

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
		}
	}
	Wire.beginTransmission(0X1D);
	Wire.write(POWER_CTL);
	Wire.write(0X00);
	Wire.endTransmission();
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
