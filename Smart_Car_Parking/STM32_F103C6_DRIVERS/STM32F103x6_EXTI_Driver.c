//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6_EXTI_Driver.h"
//====================
//Generic Macros
//====================
#define AFIO_GPIO_EXTI_Mapping(x) 		(	(x=GPIOA)?0 :\
											(x=GPIOB)?1 :\
											(x=GPIOC)?2 :\
											(x=GPIOD)?3 :0)

//====================
//Generic Variables
//====================
void (*GP_IRQ_Callback[15])(void);
//====================
//Generic Function
//====================
void Enable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_ENABLE();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_ENABLE();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_ENABLE();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_ENABLE();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_ENABLE();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_ENABLE();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_ENABLE();
		break;
	}
}

void Disable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
			NVIC_IRQ6_EXTI0_DISABLE();
			break;
	case 1:
			NVIC_IRQ7_EXTI1_DISABLE();
			break;
	case 2:
			NVIC_IRQ8_EXTI2_DISABLE();
			break;
	case 3:
			NVIC_IRQ9_EXTI3_DISABLE();
			break;
	case 4:
			NVIC_IRQ10_EXTI4_DISABLE();
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
			NVIC_IRQ23_EXTI5_9_DISABLE();
			break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
			NVIC_IRQ40_EXTI10_15_DISABLE();
			break;
	}
}

void Update_EXTI(EXTI_pinConfig_t* EXTIConfig)
{
	//configure GPIO pin as AF input
	GPIO_PinConfig_t pinconfig;

	//MODE: init GPIOx pinx as input(reset state)
	//CNF: make PORTx pin x as floating input
	pinconfig.GPIO_PINNumber = EXTIConfig -> EXTI_Pin.GPIO_Pin;
	pinconfig.GPIO_Mode = GPIO_Mode_IN_Float;
	MCAL_GPIO_init (EXTIConfig -> EXTI_Pin.GPIO_Port,&pinconfig);
	//update AFIO routing to EXTI line with port A, B, C , D
	uint8_t	AFIO_EXTICR_Index = EXTIConfig->EXTI_Pin.EXTI_LineNumber / 4 ;
	uint8_t	AFIO_EXTICR_Position = (EXTIConfig->EXTI_Pin.EXTI_LineNumber % 4) * 4;

	//reset and set AFIO_EXTICR to select the source input for EXTIx external interrupt
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF<<AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTIConfig->EXTI_Pin.GPIO_Port) &0xF)<<AFIO_EXTICR_Position);

	//reset edge trigger registers
	EXTI->RTSR &= ~(1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber );
	EXTI->FTSR &= ~(1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber );

	if(EXTIConfig -> Trigger_state == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
	}
	else if(EXTIConfig -> Trigger_state == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |= (1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
	}
	else if(EXTIConfig -> Trigger_state == EXTI_Trigger_ANYCHANGE)
	{
		EXTI->RTSR |= (1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
		EXTI->FTSR |= (1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
	}
	//Update IRQ Handling Callback
	GP_IRQ_Callback[EXTIConfig->EXTI_Pin.EXTI_LineNumber] = EXTIConfig->P_IRQ_CallBack;

	//Enable / Disable IRQ & NVIC
	if(EXTIConfig -> IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI ->IMR |= (1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
		Enable_NVIC(EXTIConfig->EXTI_Pin.EXTI_LineNumber);
	}else
	{
		EXTI ->IMR &= ~(1<<EXTIConfig->EXTI_Pin.EXTI_LineNumber);
		Disable_NVIC(EXTIConfig->EXTI_Pin.EXTI_LineNumber);
	}
}

//APIs

/**================================================================
* @Fn			-	EXTI_GPIO_init
* @brief 		-	Initializes the EXTI according to the specified parameters of EXTIConfig

*  @param [in]	-	EXTIConfig : Pointer to EXTI_PinConfig_t which contains
 * 				 	the configuration info for specified EXTI
* @retval		-	None
* Note			- 	None
*/
void  MCAL_EXTI_init (EXTI_pinConfig_t* EXTIConfig){

	Update_EXTI(EXTIConfig);
}


/**================================================================
* @Fn			-	EXTI_GPIO_Deinit
* @brief 		-	reset EXTI registers

*  @param [in]	-	None
* @retval		-	None
* Note			- 	None
*/

void MCAL_EXTI_Deinit (void){

	// Reset registers by putting the reset value
	EXTI->IMR   = 0x00000000 ;
	EXTI->EMR   = 0x00000000 ;
	EXTI->RTSR  = 0x00000000 ;
	EXTI->FTSR  = 0x00000000 ;
	EXTI->SWIER = 0x00000000 ;
	EXTI->PR 	= 0xFFFFFFFF ;

	// Disable IRQ from NVIC
	NVIC_IRQ6_EXTI0_DISABLE() ;
	NVIC_IRQ7_EXTI1_DISABLE() ;
	NVIC_IRQ8_EXTI2_DISABLE() ;
	NVIC_IRQ9_EXTI3_DISABLE() ;
	NVIC_IRQ10_EXTI4_DISABLE() ;
	NVIC_IRQ23_EXTI5_9_DISABLE() ;
	NVIC_IRQ40_EXTI10_15_DISABLE() ;

}



/**================================================================
* @Fn			-	EXTI_GPIO_Update
* @brief 		-	Update the EXTI according to the specified parameters of EXTIConfig

*  @param [in]	-	EXTIConfig : Pointer to EXTI_PinConfig_t which contains
 * 				 	the configuration info for specified EXTI
* @retval		-	None
* Note			- 	None
*/
void MCAL_EXTI_Update (EXTI_pinConfig_t* EXTIConfig){

	Update_EXTI(EXTIConfig);

}

//====================
//ISR Functions
//====================

void EXTI0_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<0 ;
	//Call IRQ Call back function
	GP_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<1 ;
	//Call IRQ Call back function
	GP_IRQ_Callback[1]();
}

void EXTI2_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<2 ;
	//Call IRQ Call back function
	GP_IRQ_Callback[2]();
}
void EXTI3_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<3 ;
	//Call IRQ Call back function
	GP_IRQ_Callback[3]();
}
void EXTI4_IRQHandler(void){
	//Clear EXTI Pending Register by writing 1 to clear
	EXTI -> PR |= 1<<4 ;
	//Call IRQ Call back function
	GP_IRQ_Callback[4]();
}
void EXTI9_5_IRQHandler(void){
	if (EXTI->PR & 1<<5){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<5 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[5]();
	}
	if (EXTI->PR & 1<<6){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<6 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[6]();
	}
	if (EXTI->PR & 1<<7){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<7 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[7]();
	}
	if (EXTI->PR & 1<<8){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<8 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[8]();
	}
	if (EXTI->PR & 1<<9){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<9 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[9]();
	}
}
void EXTI15_10_IRQHandler(void){
	if (EXTI->PR & 1<<10){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<10 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[10]();
	}
	if (EXTI->PR & 1<<11){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<11 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[11]();
	}
	if (EXTI->PR & 1<<12){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<12 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[12]();
	}
	if (EXTI->PR & 1<<13){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<13 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[13]();
	}
	if (EXTI->PR & 1<<14){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<14 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[14]();
	}
	if (EXTI->PR & 1<<15){
		//Clear EXTI Pending Register by writing 1 to clear
		EXTI -> PR |= 1<<15 ;
		//Call IRQ Call back function
		GP_IRQ_Callback[15]();
	}
}
