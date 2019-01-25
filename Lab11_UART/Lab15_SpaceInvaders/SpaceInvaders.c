#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "TExaS.h"
#include "system_init.h"
#include "lcd.h"
	void center_r(void) ;
void right_r(void) ;
void left_r(void);
void special (void) ;
void DisableInterrupts(void); 
void EnableInterrupts(void);  
unsigned long Robot_Input(void);         
/*StateType fsm[3]={
  {&center_r, 1, {center,left,center,left,right,center,right,center  }},  // Center
  {&left_r, 1, { right,right,center,right,right,center,left,center}},  // Left
  {&right_r, 1, { left,left,center,right,left,center ,left,center }}   // Right
};*/

	// Linked data structure
struct State {
    void (*CmdPt)(void);        
	//unsigned long out;
  unsigned long delay;     
  unsigned long next[4];};  
typedef const struct State StateType;
typedef StateType *StatePtr;
#define Center 0
#define Left 1
#define Right 2
	StateType fsm[3]={
  {&center_r, 1, { Right, Left,   Right,  Center }},  // Center
  {&left_r, 1, { Left,  Center, Right,  Center }},  // Left
  {&right_r, 1, { Right, Left,   Center, Center }}   // Right
};
  unsigned long H,L,F;
unsigned long S;       
unsigned long Input; 
unsigned long Output;
int main(void){ 
	  DisableInterrupts();  
 	Nokia5110_Init(); 
PLL_Init();          
  Motor_Init();         
    lcd_name ();
  Robot_Init();

   //EnableInterrupts(); 
	 S = Center;
Nokia5110_OutString("right....");	
  while(1){
		Nokia5110_SetCursor(0, 0); 
		Nokia5110_OutString("right....");	
		   //lcd ();
       special () ;		
    (fsm[S].CmdPt)();          
	
		 delay_10ms(fsm[S].delay) ;
 		Input = Robot_Input();    // read sensors
	//	if(GPIO_PORTB_DATA_R &0x04==1)
    S = fsm[S].next[Input];  
	//	else 
	//	S=Right;
	  
	/*	 Input = Robot_Input(); 
		if(Input==0)
   	center_r();
		if(Input==1)
   		right_r();
		if(Input==2)
   		center_r();
		if(Input==3)
   		left_r();
		if(Input==4)
   		left_r();
		if(Input==5)
   		center_r();
		if(Input==6)
   		left_r();
		if(Input==7)
   		center_r();*/
		
  }
}

#define INPUT GPIO_PORTF_DATA_R
unsigned long Robot_Input(void){
 
	return(INPUT&0x3);
}
 

/*void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 if(GPIO_PORTD_DATA_R&0x01){   // toggle PA6
    GPIO_PORTD_DATA_R &= ~0x01; // make PA6 low
    TIMER2_TAILR_R= L2-1;     // reload value for low phase
  } else{
    GPIO_PORTD_DATA_R |= 0x01;  // make PA6 high
    TIMER2_TAILR_R= H2-1;     // reload value for high phase
}
	}*/
void SysTick_Handler(void){
	if(F==0)
	{
  if(GPIO_PORTD_DATA_R&0x01){   
    GPIO_PORTD_DATA_R &= ~0x01; //clear
    NVIC_ST_RELOAD_R = L-1;     
  } else{
    GPIO_PORTD_DATA_R |= 0x01;  //set
    NVIC_ST_RELOAD_R = H-1;     
  }
}
	if(F==1)
	{
		 if(GPIO_PORTD_DATA_R&0x02){  
    GPIO_PORTD_DATA_R &= ~0x02; 
   NVIC_ST_RELOAD_R = L-1;     
  } else{
    GPIO_PORTD_DATA_R |= 0x02;  
    NVIC_ST_RELOAD_R = H-1;     
	}
}
	}
// L range: 8000,16000,24000,32000,40000,48000,56000,64000,72000
// power:   10%    20%   30%   40%   50%   60%   70%   80%   90%

void center_r()
{
  GPIO_PORTD_DATA_R=0x03 ;
	F=2 ;
	DisableInterrupts();
	//Nokia5110_OutString(String1); 
	 lcd ();
}
void left_r()
{
	GPIO_PORTD_DATA_R=0x01 ;
	F=1;
	L=16000;
	H=80000-L ;
	 EnableInterrupts(); 
	//Nokia5110_OutString(String2);
	 lcd ();
}
void right_r()
{
	GPIO_PORTD_DATA_R=0x02 ;
    F=0;
	L=16000;
	H=80000-L ;
	 EnableInterrupts(); 
//Nokia5110_OutString(String3);
	 lcd ();
}
void special ()
{  lcd ();  
	if((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))
	   {  right_r();
			 delay_10ms(100);
		 }
		
}