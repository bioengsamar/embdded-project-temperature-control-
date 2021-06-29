
/*
 * prototype.h
 *
 * Created: 10/06/2021 03:42:38 م
 *  Author: ELPOSTAN
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/Keypad/keypad_driver.h"
#include "../MCAL/SPI/spi.h"
#include "../HAL/TC72/TC72.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/PWM/PWM.h"


void welcome_screen(void);
char IDLE_screen_states(void);
void read_tc72(int set_temperature , int s );
void standby(void);
void operation(void);
