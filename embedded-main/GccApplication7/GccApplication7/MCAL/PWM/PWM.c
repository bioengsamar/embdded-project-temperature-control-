#include <avr/io.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include "PWM.h"


void PWM_init(void)
{
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	 DIO_vsetPINDir('B',3,1);

}

