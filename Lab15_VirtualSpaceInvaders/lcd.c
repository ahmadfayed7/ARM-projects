#include "..//tm4c123gh6pm.h"
#include "system_init.h"
#include "Nokia5110.h"
unsigned char x[10] ="sharara" ;
 int w=0
	,b=0  ;

void lcd_right ()
	{ if((!(GPIO_PORTF_DATA_R&0x01))&&(GPIO_PORTF_DATA_R&0x02))
	{Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("right....");}
}
void lcd_left ()
{
	
	if((GPIO_PORTF_DATA_R&0x01)&&(!(GPIO_PORTF_DATA_R&0x02)))
	{Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("left.....");}
}
void lcd_gap()
{   if(((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))||((GPIO_PORTF_DATA_R&0x04)&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02)))
	{Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("gap.......");
		delay_10ms(25) ;
		if(GPIO_PORTF_DATA_R&0x04)
			b++;
		else
			w++ ;
	}
}	
void lcd_stright ()
{ if((!(GPIO_PORTF_DATA_R&0x01))&&(!(GPIO_PORTF_DATA_R&0x02)))
	{Nokia5110_SetCursor(1, 0);
	Nokia5110_OutString("stright....");}
	
}
void lcd_name ()
{   
	{Nokia5110_SetCursor(0, 0);
	Nokia5110_OutString(x);}
}
void lcd_a ()
{   if(b==3)
	{Nokia5110_SetCursor(3, 0);
	Nokia5110_OutString("a");}
}
void lcd_b ()
{  if(w==5)
	{
	Nokia5110_SetCursor(3, 0);
	Nokia5110_OutString("b");}
}
void lcd_c ()
{  if(w==5)
	{  delay_10ms(300) ;
		Nokia5110_SetCursor(3, 0);
	Nokia5110_OutString("c");}
}
void lcd_d ()
{    if(((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02)))
	{
		Nokia5110_SetCursor(3, 0);
	Nokia5110_OutString("d");
	}
}
void lcd ()
{
 lcd_right ();
 lcd_left ();
 lcd_gap();
 lcd_stright ();
 lcd_name ();
 lcd_a ();
 lcd_b ();
 lcd_c ();
 lcd_d ();
}