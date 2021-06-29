#include <avr/io.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include "TC72.h"



void tc72Init(void)
{
	DIO_write( 'B',4,1);
	masterTransmit(0x80);
	masterTransmit(0x04);
	DIO_write( 'B',4,0);
	_delay_ms(150);
}



	
	

	
