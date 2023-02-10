/*
 * Timer.h
 *
 *  Created on: Oct 10, 2021
 *      Author: Mostafa Elshiekh
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_


#include "STM32F103x6_GPIO_Driver.h"
#include "STM32F103x6_RCC_Driver.h"

#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_Base+0x1C)
#define RCC_APB2ENR                           *( volatile uint32_t *)(RCC_Base+0x18)





//TIMER2
#define TIM2_timer_Base                        0x40000000
#define TIM2_CNT                              *( volatile uint32_t *)(TIM2_timer_Base+0x24)
#define TIM2_CR1                              *( volatile uint32_t *)(TIM2_timer_Base+0x00)
#define TIM2_PSC                              *( volatile uint32_t *)(TIM2_timer_Base+0x28)
#define TIM2_SR                               *( volatile uint32_t *)(TIM2_timer_Base+0x10)
#define TIM2_DIER                             *( volatile uint32_t *)(TIM2_timer_Base+0x0c)
#define TIM2_ARR                              *( volatile uint32_t *)(TIM2_timer_Base+0x2c)



/*=================Timer2======================*/
void Timer2_init(void);
void Timer_dus(int us);
void Timer_dms(int ms);

#endif /* INC_TIMER_H_ */
