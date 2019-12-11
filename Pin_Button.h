#ifndef __PIN_BTN_H__
#define __PIN_BTN_H__
#include "Arduino.h"

#define BTN_DEB_CNT   20 
#define PRESS_BUFF_LEN  4
class PinBtn{
public:
    PinBtn();
    void Init(byte pin_nbr,char val);
    void Scan(void);
    char Read(void);
private:
    char key_buff[PRESS_BUFF_LEN];
    int key_buff_wr_ptr;
    int key_buff_rd_ptr;
    byte Buff_mask(byte buff_len);
    byte pin;
    char value;
    byte state;
    byte cntr;
    byte buff_mask;
};
#endif
