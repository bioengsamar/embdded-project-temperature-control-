#include <avr/io.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include "spi.h"

void masterInit(void)
{
 DDRB=(1<<7)|(1<<5)|(1<<4);
 SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0)|(1<<CPHA);
}

void masterTransmit(char spiData)
{
	SPDR=spiData;
	while(!(SPSR&(1<<SPIF)));
	
}


char masterReceive(void)
{
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}