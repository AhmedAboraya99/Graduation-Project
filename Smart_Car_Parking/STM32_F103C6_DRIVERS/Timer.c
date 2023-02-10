/*
 * Timer.c
 *
 *  Created on: Nov 10, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */


#include "Timer.h"


void Timer2_init(void)
{
	RCC_TIMER2_CLOCK_EN();     //Enable Rcc for tim2
	TIM2_PSC = 7;             //Clk_input=(8M/(7+1))=1MHZ
	TIM2_ARR = 0xC350;        //to make interrupt after 50000 tike(50000*10^-6)=0.05s
	TIM2_CR1 |=(1<<0);
	while(!(TIM2_SR)&(1<<0));
}

void Timer_dus(int us)
{
	TIM2_CNT=0;
	while(TIM2_CNT<us);
}

void Timer_dms(int ms)
{
	int i=0;
	for(i=0;i<ms;i++)
	{
		Timer_dus(1000);
	}
}

