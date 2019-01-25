#include "..//tm4c123gh6pm.h"
#include "system_init.h"
#include "Nokia5110.h"
unsigned char name[10] ="sharara.." ;
unsigned char right[10] ="right....." ;
unsigned char left[10] ="left...." ;
unsigned char straight[10] ="straight.." ;
unsigned char gap[10] ="gap......" ;
unsigned char a[10] ="a...." ;
unsigned char bp[10] ="b...." ;
unsigned char c[10] ="c...." ;
unsigned char d[10] ="d...." ;
 int w=0
	,b=0  ;

void lcd_right ()
	{ if((!(GPIO_PORTF_DATA_R&0x01))&&(GPIO_PORTF_DATA_R&0x02))
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(right);}
}
void lcd_left ()
{
	
	if((GPIO_PORTF_DATA_R&0x01)&&(!(GPIO_PORTF_DATA_R&0x02)))
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(left);}
}
void lcd_gap()
{   if(((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))||((GPIO_PORTF_DATA_R&0x04)&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02)))
	{Nokia5110_SetCursor(0, 2);
	Nokia5110_OutString(gap);
		delay_10ms(25) ;
		if(GPIO_PORTF_DATA_R&0x04)
			b++;
		else
			w++ ;
	}
}	
void lcd_stright ()
{ if((!(GPIO_PORTF_DATA_R&0x01))&&(!(GPIO_PORTF_DATA_R&0x02)))
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
	{  delay_10ms(300) ;
		Nokia5110_SetCursor(0, 3);
	Nokia5110_OutString(c);}
}
void lcd_d ()
{    if(((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02)))
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
 lcd_stright ();
 lcd_name ();
 lcd_a ();
 lcd_b ();
 lcd_c ();
 lcd_d ();
}