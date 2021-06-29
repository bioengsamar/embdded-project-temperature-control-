
#include "LCD.h"
#define  F_CPU 8000000UL 
#include "../../Service/std_macros.h"
#include <util/delay.h>

void LCD_intialize(void)
{
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('B',EN,1);
	DIO_vsetPINDir('B',RW,1);
	DIO_vsetPINDir('B',RS,1);
   	DIO_write('B',RW,0);
	LCD_vSend_cmd(RETURN_HOME); //return home
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); //4bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1);
	
}


static void send_falling_edge(void)
{
	DIO_write('B',EN,1);
	_delay_ms(2);
	DIO_write('B',EN,0);
	_delay_ms(2);
}
void LCD_vSend_cmd(char cmd)
{
	
	write_high_nibble('A',cmd>>4);
	DIO_write('B',RS,0);
	send_falling_edge();
	write_high_nibble('A',cmd);
	DIO_write('B',RS,0);
	send_falling_edge();
	_delay_ms(1);
}

void LCD_vSend_char(char data)
{	
	write_high_nibble('A',data>>4);
	DIO_write('B',RS,1);
	send_falling_edge();
	write_high_nibble('A',data);
	DIO_write('B',RS,1);
	send_falling_edge();
	_delay_ms(1);
}


void LCD_vSend_string(char *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
} 
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
/*void LCD_movecursor(char row,char coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
} */
void LCD_GoToPos(unsigned char Row, unsigned char Col)
{
	unsigned char Address;
	
	if (Row < 2 && Col < 16)
	{
		Address = (Row * (0x40)) + Col ;
		Address = SET_BIT(Address, 7);
		LCD_vSend_cmd(Address);
	}
}

void LCD_WriteString(unsigned char* Str, unsigned char Row, unsigned char Col)
{
	LCD_GoToPos(Row, Col);
	unsigned char index = 0;
	unsigned char line0 = 0;
	
	while (Str[index] != '\0' && ((Row * 16) + (index + Col)) < 32)
	{
		if (((Row * 16) + (index + Col)) < 16)
		{
			LCD_vSend_char(Str[index]);
			index = index + 1;
		}
		
		else if (((Row * 16) + (index + Col)) == 16 && line0 == 0)
		{
			LCD_GoToPos(1, 0);
			line0 = line0 + 1;
		}
		
		else if (((Row * 16) + (index + Col)) < 32 && line0 == 1)
		{
			LCD_vSend_char(Str[index]);
			index = index + 1;
		}
		
	}
}

