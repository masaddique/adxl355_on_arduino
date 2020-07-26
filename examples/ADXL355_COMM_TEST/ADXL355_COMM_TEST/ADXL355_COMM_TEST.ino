#include <ADXL355.h>
#include <DS3231.h>
#include <Wire.h>

ADXL355 dev(0X1D);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Started");
  dev.enable(0X00);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.println("Accessing");
  readRTC();
  Serial.println();
  Serial.print("Temperature: ");
  Serial.println(dev.readTemperature());
  
  Serial.print(dev.readX()); Serial.print(",");
  Serial.print(dev.readY()); Serial.print(",");
  Serial.print(dev.readZ()); 
  Serial.println();  

  Serial.println(dev.tilt());
  Serial.println(dev.pitch());
  Serial.println(dev.roll());
  delay(1000);
}

void serialEvent()
{
  while(Serial.available())
  {
    Serial.println(Serial.read());
  }
}
