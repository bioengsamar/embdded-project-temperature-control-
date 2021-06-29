#include <avr/io.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include "ADC.h"

void ADC_Init(void)
{
	DDRA   = 0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX  = 0x40;			/* Vref: Avcc, ADC channel: 0 */
}


/*******/
/*******/
int ADC_Read(char channel)
{
	int Ain,AinLow;
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */
	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;
	Ain = Ain + AinLow;
	return(Ain);			/* Return digital value*/
}