/*
 * keypad_driver.h
 *
 *  Author: BAYOUMII
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_
#define NOTPRESSED 0xff
#include "DIO.h"
void keypad_vInit();
char keypad_u8check_press();



#endif /* KEYPAD_DRIVER_H_ */