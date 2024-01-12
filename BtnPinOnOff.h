#ifndef __BTNPINONOFF_H__
#define __BTNPINONOFF_H__
#include "Arduino.h"

#define BTN_ON_CNT   	10 
#define BTN_OFF_CNT 	50 
#define BTN_RELEASE_CNT 10 

 
#define PRESS_BUFF_LEN  4
typedef enum
{
	PRESSED_NOT = 0,
	PRESSED_ON,
	PRESSED_OFF
} pressed_et;

class BtnPinOnOff{
public:
    BtnPinOnOff();
    void Init(byte pin_nbr,char val);
    void Scan(void);
    char Read(void);
private:
    char key_buff[PRESS_BUFF_LEN];
    int key_buff_wr_ptr;
    int key_buff_rd_ptr;
    byte pin;
    char value;
    byte state;
    byte cntr;
	pressed_et pressed;
    byte buff_mask;
};
#endif
