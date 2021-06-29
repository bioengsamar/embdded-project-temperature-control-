
#ifndef HAL_LCD_LCD_H
#define HAL_LCD_LCD_H
#include "../../MCAL/DIO/DIO.h"

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#define EN 0
#define RS 1
#define RW 2
#define FOUR_BITS 0x28

void LCD_intialize(void);
static void send_falling_edge(void);
void LCD_vSend_cmd(char cmd);
void LCD_vSend_char(char data);
void LCD_vSend_string(char *data);
void LCD_clearscreen();
void LCD_movecursor(char row,char coloumn);
void LCD_GoToPos(unsigned char Row, unsigned char Col);
void LCD_WriteString(unsigned char* Str, unsigned char Row, unsigned char Col);


#endif /* LCD_H_ */