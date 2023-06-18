#include "BtnPinOnOff.h"

BtnPinOnOff::BtnPinOnOff(){
   pin = 0;
   value ='x';
   state = 0;
   cntr = 0;
   key_buff_wr_ptr = 0;
   key_buff_rd_ptr = 0;
}

void BtnPinOnOff::Init(byte pin_nbr,char val){
    pin = pin_nbr;
    value = val;
    state = 0;
    cntr = 0;
    key_buff_wr_ptr = 0;
    key_buff_rd_ptr = 0;
    buff_mask = 0b00000011;
    pinMode(pin, INPUT_PULLUP);
};


void BtnPinOnOff::Scan(void){

	// run every 10ms
	Serial.print(state);
	switch(state){
		case 0:   // idle state
			if (digitalRead(pin) == LOW ) 
			{
			  cntr = 0;
			  state = 1;
			  pressed = PRESSED_NOT;
			}
			break;
		case 1:   // pressed, debounch         
			if (digitalRead(pin) == LOW ) 
			{
				if (cntr++ >= BTN_ON_CNT) 
				{
				  state = 2;
				  pressed = PRESSED_ON;		
				}
			}
			else 
			{
				state = 0;
			}
			break;
		  
		case 2:   // ON state        
			if (digitalRead(pin) == LOW ) 
			{
				if (cntr++ >= BTN_OFF_CNT) 
				{
					state = 3;
					pressed = PRESSED_OFF;
				}
			}
			else 
			{
				state = 10;
				cntr = 0;
			}
			break;

		case 3:   // OFF state        
			if (digitalRead(pin) == LOW ) 
			{
				  // just wait
			}
			else 
			{
				state = 10;
				cntr = 0;
			}
			break;
			    
		  
		case 10:   // released
			if (digitalRead(pin) == HIGH ) 
			{
				if (cntr++ > BTN_RELEASE_CNT) state = 11;
			}
			break;
		case 11:   // released, Store in buffer		
			key_buff[key_buff_wr_ptr]=value;
			if (pressed == PRESSED_OFF) key_buff[key_buff_wr_ptr] |= 0b10000000;
			//Serial.println(key_buff[key_buff_wr_ptr]);
			key_buff_wr_ptr = ++key_buff_wr_ptr & buff_mask;
			state = 0;
			break;
	}
     //Serial.print("Key: "); Serial.print(i);Serial.print("> ");
     //Serial.print(btn[i].state);
     //Serial.println();
}

char BtnPinOnOff::Read(void){
   char btn_pressed=0;
   // Serial.print(key_buff_wr_ptr);Serial.print(">");Serial.println(key_buff_rd_ptr);
   if (key_buff[key_buff_rd_ptr]){
       btn_pressed = key_buff[key_buff_rd_ptr];
       key_buff[key_buff_rd_ptr] = 0;
       key_buff_rd_ptr = ++key_buff_rd_ptr & buff_mask;  // ring buffer
       //Serial.println(btn_pressed);
   }
   return(btn_pressed);
}
