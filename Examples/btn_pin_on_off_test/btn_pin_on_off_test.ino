#include "Arduino.h"
//#include "AVR_Watchdog.h"
#include <EEPROM.h>
#include <TaHa.h> 
#include "BtnPinOnOff.h"

TaHa TaHa_10ms;

BtnPinOnOff  Pin1;
BtnPinOnOff  BtnPin[4];


void setup() 
{
  delay(2000);
  Serial.begin(9600); 
  Serial.println("btn_pin_on_off_test.ino  2023");

  BtnPin[0].Init(3,'A');
  BtnPin[1].Init(4,'B');
  BtnPin[2].Init(5,'C');
  BtnPin[3].Init(6,'D');


  TaHa_10ms.set_interval(10, RUN_RECURRING, run_10ms); 
}

void loop() {
    // put your main code here, to run repeatedly:
    TaHa_10ms.run();

    for( uint8_t i= 0; i<4; i++)
    {
        char c = BtnPin[i].Read();
        if (c != 0x00) 
        {
            if ((c & 0b10000000) == 0) 
                Serial.print("On ");
            else 
                Serial.print("Off ");
            Serial.println(c & 0b01111111);

        }

    }
}


void run_10ms()
{
    for( uint8_t i= 0; i<4; i++)
    {
        BtnPin[i].Scan();

    }
}