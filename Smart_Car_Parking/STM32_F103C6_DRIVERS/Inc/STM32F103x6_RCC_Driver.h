#ifndef _STM32F103X6_RCC_H_
#define _STM32F103X6_RCC_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define HSE_Clock 			(uint32_t)16000000
#define HSI_RC_Clk 			(uint32_t)8000000


//-----------------------------
//Configure structure for RCC
//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLOCK_EN() 	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLOCK_EN() 	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLOCK_EN() 	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLOCK_EN() 	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLOCK_EN() 	(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLOCK_EN() 	(RCC->APB2ENR |= 1<<0)

//Bit USARTEN: USART clock enable
//1: USART1 clock enabled
#define RCC_USART1_CLOCK_EN() 	(RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLOCK_EN() 	(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLOCK_EN() 	(RCC->APB1ENR |= 1<<18)
//0: USART clock disabled
#define RCC_USART1_CLOCK_Disable() 	(RCC->APB2ENR &=~(1<<14))
#define RCC_USART2_CLOCK_Disable() 	(RCC->APB1ENR &=~(1<<17))
#define RCC_USART3_CLOCK_Disable() 	(RCC->APB1ENR &=~(1<<18))

/**RCC Reset **/
//USARTRST: USART reset
//0: No effect
//1: Reset USART
#define RCC_USART1_Reset() 	(RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_Reset() 	(RCC->APB1RSTR |= 1<<17)
#define RCC_USART3_Reset() 	(RCC->APB1RSTR |= 1<<18)

//Bit SPIEN: SPI clock enable
//1: SPI clock enabled
#define RCC_SPI1_CLOCK_EN() 	(RCC->APB2ENR |= 1<<12)
#define RCC_SPI2_CLOCK_EN() 	(RCC->APB1ENR |= 1<<14)

//0: SPI clock disabled
#define RCC_SPI1_CLOCK_Disable() 	(RCC->APB2ENR &= ~(1<<12))
#define RCC_SPI2_CLOCK_Disable() 	(RCC->APB1ENR &= ~(1<<14))

#define RCC_TIMER2_CLOCK_EN() 	(RCC->APB1ENR |= 1<<0)
#define RCC_TIMER2_CLOCK_Disable() 	(RCC->APB1ENR &= ~(1<<0))
#define RCC_TIMER2_Reset() 	(RCC->APB1RSTR |= (1<<0))

//SPIRST: SPI reset
//0: No effect
//1: Reset SPI
#define RCC_SPI1_Reset() 	(RCC->APB2RSTR |= 1<<12)
#define RCC_SPI2_Reset() 	(RCC->APB1RSTR |= 1<<14)

//-----------------------------
//Macros Configuration References
//-----------------------------



/*
* ===============================================
* APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/

//initialization APIs

uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetHCLCKFreq(void);
uint32_t MCAL_RCC_GetPCLCK1Freq(void);
uint32_t MCAL_RCC_GetPCLCK2Freq(void);



#endif
