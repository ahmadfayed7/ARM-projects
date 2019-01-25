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
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
	// Linked data structure
struct State {
//    void (*CmdPt)(void);
	int out ;
	//unsigned long out;
  unsigned long delay;     
  unsigned long next[4];};  
typedef const struct State StateType;
typedef StateType *StatePtr;
#define Center 0
#define Left 1
#define Right 2
	/*StateType fsm[3]={
  {0x03, 1, { Center, Left,   Right,  Center }},  // Center
  {0x01, 1, { Left,  Center, Right,  Center }},  // Left
  {0x02, 1, { Right, Left,   Center, Center }}   // Right
};*/
		StateType fsm[3]={
  {0x03, 1, { Center, Left,   Right,  Center }},  // Center
  {0x01, 1, { Center,  Center, Right,  Center }},  // Left
  {0x02, 1, { Center, Left,   Center, Center }}   // Right
};
  unsigned long H,L,F;
unsigned long S;       
unsigned long Input; 
unsigned long Output;
int main(void){
  TExaS_Init(SSI0_Real_Nokia5110_Scope);  // set system clock to 80 MHz
     DisableInterrupts();  
  PLL_Init();          
   Motor_Init();         
  Robot_Init();
	 
  //EnableInterrupts(); 
	 S = Center;
  Nokia5110_Init();
	
  while(1){
		//	Nokia5110_SetCursor(0, 0); 
		
	  lcd ();
     special () ;		
    //(fsm[S].CmdPt)();          
	  GPIO_PORTD_DATA_R=fsm[S].out ;
	 delay_10ms((fsm[S].delay)/10) ;
 		Input = Robot_Input();    // read sensors
	//	if(GPIO_PORTB_DATA_R &0x04==1)
    S = fsm[S].next[Input];	 
  }

}

#define INPUT GPIO_PORTF_DATA_R
unsigned long Robot_Input(void){
 
	return(INPUT&0x03);
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
#define output GPIO_PORTD_DATA_R
/*void SysTick_Handler(void){
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
*/
void center_r()
{
  GPIO_PORTD_DATA_R=0x03 ;
//	F=2 ;
	//DisableInterrupts();
  // Nokia5110_OutString(q); 
	 //lcd_straight();
}
void left_r()
{
	GPIO_PORTD_DATA_R=0x01 ;
	//F=1;
//	L=8000;
	//H=80000-L ;
	// EnableInterrupts(); 
	//Nokia5110_OutString(y);
	 //lcd_right ();
}
void right_r()
{
	GPIO_PORTD_DATA_R=0x02 ;
   // F=0;
	//L=8000;
	//H=80000-L ;
	 //EnableInterrupts(); 
//Nokia5110_OutString(z);
	 //lcd_left ();
}
/*void special ()
{  //lcd ();  
	 while((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))
	   {   GPIO_PORTD_DATA_R =0x03 ;
			 if(!(GPIO_PORTF_DATA_R&0x01))
			 {	 while(1) 
				 {GPIO_PORTD_DATA_R =0x02 ;
          if((GPIO_PORTF_DATA_R&0x01)) 
     			break ; 
		 }}
	 }
  //delay_10ms(10) ;		
}*/
void special ()
{  int i ;
	while((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))
	{   
	
		delay_10ms(25);
	}
}
/*void GPIOPortF_Handler(void){ // called on touch of either SW1 or SW2
   GPIO_PORTF_ICR_R = 0x04;  // acknowledge flag0
	if(GPIO_PORTF_RIS_R&0x04){  // SW2 touch
		//delay_10ms(25);
    if((!(GPIO_PORTF_DATA_R&0x04))&&(GPIO_PORTF_DATA_R&0x01)&&(GPIO_PORTF_DATA_R&0x02))
	   {   
			if((GPIO_PORTF_DATA_R&0x03)==0)
      	GPIO_PORTD_DATA_R =0x02 ;
       else 
     		GPIO_PORTD_DATA_R =0x02 ;		 
		 }
		 delay_10ms(25);
}}
*/