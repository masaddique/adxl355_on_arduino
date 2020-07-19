#include <Wire.h>

#define DEV_ADDRESS               0X1D

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

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  Serial.println("Accessing");
  Wire.beginTransmission(0X1D);
  Wire.write(0X00);
  Wire.endTransmission();
  Wire.requestFrom(0X1D,0X05);
  while(Wire.available())
  {
    //Serial.println("Some Thing");
    uint8_t c = Wire.read();
    printHex(c);
  }
  Serial.println();
  Wire.beginTransmission(0X1D);
  Wire.write(0X2D);
  Wire.write(0X00);
  Wire.endTransmission();
  Serial.println("Reading Temperature");
  Serial.println(readTemperature());
  Serial.println();
  Serial.println("Reading Acceleros");
  Wire.beginTransmission(0X1D);
  Wire.write(0X08);
  Wire.endTransmission();
  Wire.requestFrom(0X1D,9);
  int i = 0;
  while(Wire.available())
  {
    //Serial.println("Some Thing");
    uint8_t c = Wire.read();
    printHex(c);
    if (i++==2) {
      Serial.println();
      i=0;
    }
  }
  */
  Serial.println();
  Serial.print(readX());
  Serial.print(",");
  Serial.print(readY());
  Serial.print(",");
  Serial.print(readZ());
  Serial.println(",");
  delay(50);
}

void serialEvent()
{
  while(Serial.available())
  {
    Serial.println(Serial.read());
  }
}

float readTemperature() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(TEMP2);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,2);
  uint32_t temperature = 0X0000;
  int t1 = Wire.available()?Wire.read():0;
  int t2 = Wire.available()?Wire.read():0;
  temperature = (t1<<8)|t2;
  float temp = 25.0;
  temp = -((float)temperature-1852)/9.05 + 25;
  return temp;
}

float readX() {
  
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(XDATA3);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
}

float readY() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(YDATA3);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
  
}

float readZ() {
  Wire.beginTransmission(DEV_ADDRESS);
  Wire.write(ZDATA3);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDRESS,3);
  uint32_t t1 = Wire.available()?Wire.read():0;
  uint32_t t2 = Wire.available()?Wire.read():0;
  uint32_t t3 = Wire.available()?Wire.read():0;
  uint32_t data = (t1<<16)|(t2<<8)|t3;
  data = data>>4;
  float value = (float)data;
  value = data>0X7FFFF?value-0XFFFFE:value;
  return value/0X7FFFF*2.048;
  
}
void printHex(uint8_t c) {
  uint8_t lower = c&0X0F;
  uint8_t upper = (c>>4)&0X0F;
  switch(upper)
  {
    case 0:
      Serial.print("0");
      break;
    case 1:
      Serial.print("1");
      break;
    case 2:
      Serial.print("2");
      break;
    case 3:
      Serial.print("3");
      break;
    case 4:
      Serial.print("4");
      break;
    case 5:
      Serial.print("5");
      break;
    case 6:
      Serial.print("6");
      break;
    case 7:
      Serial.print("7");
      break;
    case 8:
      Serial.print("8");
      break;
    case 9:
      Serial.print("9");
      break;
    case 10:
      Serial.print("A");
      break;
    case 11:
      Serial.print("B");
      break;
    case 12:
      Serial.print("C");
      break;
    case 13:
      Serial.print("D");
      break;
    case 14:
      Serial.print("E");
      break;
    case 15:
      Serial.print("F");
      break;
    default:
      Serial.print("X");
  }
  switch(lower)
  {
    case 0:
      Serial.print("0");
      break;
    case 1:
      Serial.print("1");
      break;
    case 2:
      Serial.print("2");
      break;
    case 3:
      Serial.print("3");
      break;
    case 4:
      Serial.print("4");
      break;
    case 5:
      Serial.print("5");
      break;
    case 6:
      Serial.print("6");
      break;
    case 7:
      Serial.print("7");
      break;
    case 8:
      Serial.print("8");
      break;
    case 9:
      Serial.print("9");
      break;
    case 10:
      Serial.print("A");
      break;
    case 11:
      Serial.print("B");
      break;
    case 12:
      Serial.print("C");
      break;
    case 13:
      Serial.print("D");
      break;
    case 14:
      Serial.print("E");
      break;
    case 15:
      Serial.print("F");
      break;
    default:
      Serial.print("X");
  }
  
}
