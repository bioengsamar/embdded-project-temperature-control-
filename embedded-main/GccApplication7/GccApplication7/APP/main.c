
#include "prototype.h"
int main(void)
{
	masterInit();
	tc72Init();
	LCD_intialize();
   	keypad_Intialize();
	
	welcome_screen();
	int set_temp = IDLE_screen_states();
	  read_tc72(set_temp , 1);
	 standby();
	/*error(set_temp ,current ); */
			
		
		
	 
	
	
	return 0;
	
	 
}



