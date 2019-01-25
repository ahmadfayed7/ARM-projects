#include "..//tm4c123gh6pm.h"
#include "system_init.h"
#include "Nokia5110.h"
unsigned char name[20] =    "sharara..." ;
unsigned char right[20] =   "right....." ;
unsigned char left[20] =    "left......" ;
unsigned char straight[20] ="straight.." ;
unsigned char gap[20] =     "gap......." ;
unsigned char a[20] ="a...." ;
unsigned char bp[20] ="b...." ;
unsigned char c[20] ="c...." ;
unsigned char d[20] ="d...." ;
 int w=0
	,b=0  ;

void lcd_right ()
	{ if((GPIO_PORTF_DATA_R & 0x03) ==2)
	{
		Nokia5110_SetCursor(0, 2);
	 Nokia5110_OutString(right);
	}
}
void lcd_left ()
{
	
	if((GPIO_PORTF_DATA_R & 0x03) ==1)
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(left);}
}
void lcd_gap()
{   if(((GPIO_PORTF_DATA_R & 0x07) ==3)||((GPIO_PORTF_DATA_R & 0x07) ==7))
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(gap);
//		delay_10ms(25) ;
		if(GPIO_PORTF_DATA_R&0x04)
			b++;
		else
			w++ ;
	}
}	
void lcd_straight ()
{ if((GPIO_PORTF_DATA_R & 0x03) ==0)
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(straight);}
	
}
void lcd_name ()
{   
	{Nokia5110_SetCursor(0, 1);
	Nokia5110_OutString(name);}
}
void lcd_a ()
{   if(b==3)
	{Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString(a);}
}
void lcd_b ()
{  if(w==5)
	{
	Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString(bp);}
}
void lcd_c ()
{  if(w==5)
	{//  delay_10ms(300) ;
		Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString(c);}
}
void lcd_d ()
{    if((GPIO_PORTF_DATA_R & 0x07) ==3 )
	{
		Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString(d);
	}
}
void lcd ()
{
 lcd_right ();
 lcd_left ();
 lcd_gap();
 lcd_straight ();
 lcd_name ();
 lcd_a ();
 lcd_b ();
 lcd_c ();
 lcd_d ();
}