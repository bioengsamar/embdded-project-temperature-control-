
/*
 * lcd_app.c
 *
 * Created: 6/8/2021 4:55:09 PM
 *  Author: ht
 */ 
#include "prototype.h"

	



//void LCD_intialize(void);


void welcome_screen()
{
	
	int j =0;
	while ( j <= 2)
	{
		for (int i = 9; i >= 0; i--)
		{
			LCD_WriteString("WELCOME", 0, i);
			_delay_ms(100);
			LCD_clearscreen();
		}
		
		for (int i = 0; i <= 9; i++)
		{
			LCD_WriteString("WELCOME", 0, i);
			_delay_ms(100);
			LCD_clearscreen();
		}
		
		j++;
	}
	
	LCD_WriteString("SET:25", 0, 0);   // set temperature
	LCD_WriteString("STATE:STANDBY", 1, 0);  // system state
}

void operation(void)
{
	unsigned char read_keypad_value = 0xff;
	
	do
	{
		read_keypad_value = keypad_check_press();
	} while (read_keypad_value == 0xff);
	
	if (read_keypad_value == (unsigned char) 12)
	{
		LCD_GoToPos(1,6);
		LCD_vSend_string("OPERATION");
	}
	
}
char IDLE_screen_states()
{
	keypad_Intialize();
	unsigned char read_sensor =0;
	unsigned char set_temperature = 0;
	unsigned char read_keypad_value = 0xff;
	
	LCD_GoToPos(0,4);
	
	do
	{
		read_keypad_value = keypad_check_press();
	} while (read_keypad_value == 0xff);
	
	set_temperature= (read_keypad_value * 10);
	_delay_ms(300);
	read_keypad_value = 0xff;
	
	do
	{
		read_keypad_value = keypad_check_press();
	} while (read_keypad_value == 0xff);
	
	set_temperature= (set_temperature + read_keypad_value);
	_delay_ms(300);
	
	LCD_vSend_char(((set_temperature/10)+48));
	LCD_vSend_char(((set_temperature%10)+48));
	
	//_delay_ms(300);
	
	/*read_keypad_value = 0xff;
	
	do
	{
		read_keypad_value = keypad_check_press();
	} while (read_keypad_value == 0xff);
	
	if (read_keypad_value == (unsigned char) 12)
	{
		LCD_GoToPos(1,6);
		LCD_vSend_string("OPERATION");
	}*/
	operation();
	
	
	return set_temperature;
}

void standby(void)
{
	
	unsigned char read_keypad_value = 0xff;
	
	do
	{
		read_keypad_value = keypad_check_press();
	} while (read_keypad_value == 0xff);
	if (read_keypad_value == (unsigned char) 12)
	{
		LCD_GoToPos(1,6);
		LCD_vSend_string("  STANDBY ");
	}
}
void read_tc72( int set_temperature , int s )
{
	char msb;
	
	
	unsigned char setTEM ;
	

	
    
    PWM_init();
	ADC_Init();
    _delay_ms(150);
	
   
   while(s)
	{
		
	    DIO_write( 'B',4,1);
		masterTransmit(0x02);
		masterTransmit(0x00);
	    DIO_write( 'B',4,0);
		_delay_ms(1);
		msb=masterReceive();
		

		double Current_Temperature = msb;
		/*operation(set_temperature , msb);*/
		double v_r;
		double Vt;
		double value;
		if ( set_temperature > Current_Temperature )
		{
			LCD_GoToPos(0, 10);
			LCD_vSend_string("CRT:");
			LCD_GoToPos(0,14);
			
			LCD_vSend_char(((msb/10)+48));
			LCD_vSend_char(((msb%10)+48));
			
			Vt = (((double)set_temperature-Current_Temperature) / 100) * 10;
			if ((set_temperature - Current_Temperature)< 5)
			{
				LCD_GoToPos(1,6);
				LCD_vSend_string("  Normal  ");
			}
			
		}
		else if (Current_Temperature >= set_temperature)
		{
			
			Vt = 0;
			if ((Current_Temperature -set_temperature)<= 5 )
			{
				LCD_GoToPos(0, 10);
				LCD_vSend_string("CRT:");
				
				LCD_GoToPos(0,14);
				LCD_vSend_char(((msb/10)+48));
				LCD_vSend_char(((msb%10)+48));
				LCD_GoToPos(1,6);
				LCD_vSend_string("  Normal  ");
				
				
			}
			if ((Current_Temperature -set_temperature)> 10)
			{
				LCD_clearscreen();
				LCD_GoToPos(1,0);
				LCD_vSend_string("STATE : error  ");
				read_tc72( 25 , 0);
			}
			if ((5<(Current_Temperature -set_temperature)) && ((Current_Temperature -set_temperature)<10))
			{
				LCD_GoToPos(0, 10);
				LCD_vSend_string("CRT:");
				
				LCD_GoToPos(0,14);
				LCD_vSend_char(((msb/10)+48));
				LCD_vSend_char(((msb%10)+48));
				LCD_GoToPos(1,6);
				LCD_vSend_string("OPERATION");
				
			}
			
		}
		
		
		value=  ADC_Read(0);
		v_r =   ((value*5.0)/1023.0)*100;
		
		OCR0 =  ((((v_r * 2)/10) * Vt) / 10)*100;
		
		
	    

		_delay_ms(200);
		
	
		/*_delay_ms(300);
		operation();*/
		
		
	}
	


}
	
/*void error(int set_temperature , int Current_Temperature )
{
	if (Current_Temperature >= set_temperature)
	{
		
	}
	
}*/
/*void operation(int set_temperature , int Current_Temperature )
{
	
	double v_r;
	double Vt;
    double value;
	if ( set_temperature > Current_Temperature )
	{
		
		
		Vt = (((double)set_temperature-Current_Temperature) / 100) * 10;
		if ((set_temperature - Current_Temperature)< 5)
		{
			LCD_GoToPos(1,6);
			LCD_vSend_string("  Normal  ");
		}
		
	}
	else if (Current_Temperature >= set_temperature)
	{
		
		Vt = 0;
		if ((Current_Temperature -set_temperature)<= 5 )
		{
			LCD_GoToPos(1,6);
			LCD_vSend_string("  Normal  ");
		}
		
	}
	
	value=  ADC_Read(0);
	v_r =   ((value*5.0)/1023.0)*100;
	
	OCR0 =  ((((v_r * 2)/10) * Vt) / 10)*100;
	
	}*/


