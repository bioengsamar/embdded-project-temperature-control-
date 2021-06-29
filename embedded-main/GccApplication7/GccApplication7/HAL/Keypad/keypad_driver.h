

#ifndef HAL_Keypad_KEYPAD_DRIVER_H
#define HAL_Keypad_KEYPAD_DRIVER_H

#define NOTPRESSED 0xff
#include "../../MCAL/DIO/DIO.h"
void keypad_Intialize();
char keypad_check_press();



#endif /* KEYPAD_DRIVER_H_ */