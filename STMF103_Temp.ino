
#include <OLED_I2C.h>
#define  STM32F103CC
#include<Wire.h>
#include <SparkFunHTU21D.h>
HTU21D myHumidity;

//OLED12864/32 
//OLED:   CS  RST  DC  D1(SDA)  D0(SCL)   VCC    GND
//STM32:  -   PA3  -    PA1      PA2     3.3/5V  0V
//ZION    -   23        49       50

//OLED_12832  myOLED(SDA, SCL, 8);   //use hwi2c
//OLED_12864  myOLED(SDA, SCL, 8);   //use hwi2c
//OLED_12832  myOLED(PC5, PC4, PC1); //use soft i2c  12832
//OLED_12864  myOLED(PC5,PC4,PC1);   //use soft i2c  12864

//pb5:rst 
//pb6:scl  
//pb7:sda 

 OLED_12864  myOLED(SDA,SCL,PB5);   //use soft i2c  12864
 TwoWire myWire(PB11,PB10);
 
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];


void setup()
{
//  ADC_TempSensorEn();
  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.printxy("LoRaM4-2.4", CENTER, 0);
  myOLED.printxy("External Temp Sensor", CENTER,  8);
  //myOLED.printNumF(24.8,2,0,34);
  //myOLED.setFont(MediumNumbers);
  myWire.begin();
  myHumidity.begin(myWire);
}


void loop()
{

  //myOLED.printNumF(88.8, 2, CENTER, 16);
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  myOLED.printNumF(temp, 2, CENTER, 24);
  myOLED.printNumF(humd, 2, CENTER, 32);
  myOLED.update();
}
