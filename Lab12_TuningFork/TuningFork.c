// TuningFork.c Lab 12
// Runs on LM4F120/TM4C123
// Use SysTick interrupts to create a squarewave at 440Hz.  
// There is a positive logic switch connected to PA3, PB3, or PE3.
// There is an output on PA2, PB2, or PE2. The output is 
//   connected to headphones through a 1k resistor.
// The volume-limiting resistor can be any value from 680 to 2000 ohms
// The tone is initially off, when the switch goes from
// not touched to touched, the tone toggles on/off.
//                   |---------|               |---------|     
// Switch   ---------|         |---------------|         |------
//
//                    |-| |-| |-| |-| |-| |-| |-|
// Tone     ----------| |-| |-| |-| |-| |-| |-| |---------------
//
// Daniel Valvano, Jonathan Valvano
// December 29, 2014

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */


#include "TExaS.h"
#include "..//tm4c123gh6pm.h"
unsigned long f;
unsigned long p;
unsigned long s;
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void Delay1ms(unsigned long msec);
// input from PA3, output from PA2, SysTick interrupts
void Sound_Init(void){ 
	unsigned long delay ;
	SYSCTL_RCGC2_R |= 0x00000001;
	delay=SYSCTL_RCGC2_R ;
	GPIO_PORTA_AMSEL_R &= ~0x0c;
	GPIO_PORTA_AFSEL_R &= ~0x0c;
	GPIO_PORTA_AMSEL_R &= ~0x00000000;
	GPIO_PORTA_DIR_R |= 0x04;
	GPIO_PORTA_DIR_R &= ~0x08;
	GPIO_PORTA_DEN_R |= 0x0c;
	GPIO_PORTA_IS_R &= ~0x08;
  GPIO_PORTF_IBE_R &= ~0x08;   
  GPIO_PORTF_IEV_R |= 0x08;
  GPIO_PORTA_DR8R_R |= 0x04;//DRIVE OUT TO 8 MA
	NVIC_ST_CTRL_R = 0 ;
	NVIC_ST_RELOAD_R =90908  ;
	NVIC_ST_CURRENT_R = 0 ;
	NVIC_SYS_PRI3_R &=0x00ffffff;
	NVIC_ST_CTRL_R = 7 ;
	EnableInterrupts(); 
}

// called at 880 Hz
void SysTick_Handler(void){	
	if(s==1)
	{GPIO_PORTA_DATA_R ^=0x04; 
	}
 if(s==0)
	{
		GPIO_PORTA_DATA_R &=~0x04;
	}
	 
}

int main(void){
  TExaS_Init(SW_PIN_PA3, HEADPHONE_PIN_PA2,ScopeOn);
  Sound_Init();	
  EnableInterrupts();   
	s=0;
	p=0;
  while(1){
if((GPIO_PORTA_DATA_R&0x08)==0x08)
{s=1;
	p=1;
	while((GPIO_PORTA_DATA_R&0x08)==0x08);
	while(p==1)
	{if((GPIO_PORTA_DATA_R&0x08)==0x08)
  { s=0 ;p=0;}
	}
 while((GPIO_PORTA_DATA_R&0x08)==0x08);
	
}
}}

void Delay1ms(unsigned long msec){
	  unsigned long count;
  while(msec > 0 ) { 
    count = 80000 /6; 
    while (count > 0) { 
      count--;
    } 
    msec--;
  }
  }








