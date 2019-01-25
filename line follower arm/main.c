#include "..//tm4c123gh6pm.h"
#include "Nokia5110.h"
#include"system_init.h"
unsigned long H1,L1,H2,L2;
unsigned char String[10];
unsigned long Robot_Input(void);         // Input from sensors
void center_r(void) ;
void right_r(void) ;
void left_r(void);
// Linked data structure
struct State {
    void (*CmdPt)(void);        // 2-bit output 
  unsigned long delay;      // time to delay in 10ms
  unsigned long next[8];};  // Next if 2-bit input is 0-3
typedef const struct State StateType;
typedef StateType *StatePtr;
#define center 0
#define left 1
#define right 2
StateType fsm[3]={
  {&center_r, 1, {center,right,center,right,left,right,left,center  }},  // Center
  {&left_r, 1, { left,left,center,left,left,right,left,center}},  // Left
  {&right_r, 1, { right,right,center,right,right,right ,right,center }}   // Right
};
 
unsigned long S;       // index to the current state 
unsigned long Input; 
unsigned long Output;
int main(void){ 
	  DisableInterrupts();  // disable interrupts while initializing
  PLL_Init();           // bus clock at 80 MHz
  Motor_Init();         // output from PA5, SysTick interrupts
  Switch_Init();        // arm PF4, PF0 for falling edge interrupts
  Robot_Init();
	Nokia5110_Init(); 
 EnableInterrupts(); 
	 S = center; 
  while(1){
		Nokia5110_SetCursor(0, 0); 
    (FSM[S].CmdPt)();           // call output function  
		 delay_10ms(fsm[S].delay) ;
    Input = Robot_Input();    // read sensors
    S = fsm[S].next[Input];   // next depends on input and state 
  }
}
// ********Robot_Input***************
// Input from sensors
// 0,0            Lost, off the line
// 0,1            off to right
// 1,0            off to left
// 1,1            on line
#define INPUT (*((volatile unsigned long *)0x40025044))
unsigned long Robot_Input(void){
 
	return(INPUT&0X7);
}
 

void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
 if(GPIO_PORTA_DATA_R&0x40){   // toggle PA6
    GPIO_PORTA_DATA_R &= ~0x40; // make PA6 low
    TIMER2_TAILR_R= L-1;     // reload value for low phase
  } else{
    GPIO_PORTA_DATA_R |= 0x40;  // make PA6 high
    TIMER2_TAILR_R= H-1;     // reload value for high phase
}
void SysTick_Handler(void){
  if(GPIO_PORTA_DATA_R&0x20){   // toggle PA5
    GPIO_PORTA_DATA_R &= ~0x20; // make PA5 low
    NVIC_ST_RELOAD_R = L-1;     // reload value for low phase
  } else{
    GPIO_PORTA_DATA_R |= 0x20;  // make PA5 high
    NVIC_ST_RELOAD_R = H-1;     // reload value for high phase
  }
}
// L range: 8000,16000,24000,32000,40000,48000,56000,64000,72000
// power:   10%    20%   30%   40%   50%   60%   70%   80%   90%
void center_r()
{
 L1=72000 ;
	H1=80000-L1; 
	L2=72000 ;
	H2=80000-L2; 
	Nokia5110_OutString("center");
}
void left_r()
{
 L1=40000 ;
	H1=80000-L1; 
	L2=72000 ;
	H2=80000-L2; 
	Nokia5110_OutString("lefttt");
}
void right_r()
{
 L1=72000 ;
	H1=80000-L1; 
	L2=40000 ;
	H2=80000-L2; 
	Nokia5110_OutString("right");
	
}