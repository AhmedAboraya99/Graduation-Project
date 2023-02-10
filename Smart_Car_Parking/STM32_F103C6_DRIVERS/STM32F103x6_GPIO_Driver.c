
//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6_GPIO_Driver.h"

//assisted functions
uint8_t Get_CRLH_Position(uint16_t PINNumber)
{
	switch (PINNumber)
	{
	//CRL
	case GPIO_PIN0:
		return 0;
		break;
	case GPIO_PIN1:
		return 4;
		break;
	case GPIO_PIN2:
		return 8;
		break;
	case GPIO_PIN3:
		return 12;
		break;
	case GPIO_PIN4:
		return 16;
		break;
	case GPIO_PIN5:
		return 20;
		break;
	case GPIO_PIN6:
		return 24;
		break;
	case GPIO_PIN7:
		return 28;
		break;

	//CRH
	case GPIO_PIN8:
		return 0;
		break;
	case GPIO_PIN9:
		return 4;
		break;
	case GPIO_PIN10:
		return 8;
		break;
	case GPIO_PIN11:
		return 12;
		break;
	case GPIO_PIN12:
		return 16;
		break;
	case GPIO_PIN13:
		return 20;
		break;
	case GPIO_PIN14:
		return 24;
		break;
	case GPIO_PIN15:
		return 28;
		break;
	}
	return 0;
}

//APIs

/**================================================================
* @Fn- MCAL_GPIO_init
* @brief 		-Initializes the GPIOx PINy according to the specified parameters of PinConfig
* @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
*  @param [in]	-PinConfig : Pointer to GPIO_PinConfig_t which contains
 * 				 the configuration info for specified GPIO
* @retval -
* Note			-STM32F103C6 MCU has GPIO A,B,C,D,E ports
 * 				 but LQFP48 Package has A,B ,Part of C&D
*/
void  MCAL_GPIO_init (GPIO_TypeDef* GPIOx ,GPIO_PinConfig_t* PINConfig){

	volatile uint32_t *Config_Reg = NULL;
	uint8_t PIN = 0;

	//Port configuration Register low (GPIOx_CRL) configure pins 0 -> 7
	//Port configuration Register high (GPIOx_CRH)  configure pins 8 -> 15
	Config_Reg = (PINConfig->GPIO_PINNumber < GPIO_PIN8 )? &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNF[1:0] & MODE[1:0]
	(*Config_Reg) &= ~(0x0F << Get_CRLH_Position(PINConfig->GPIO_PINNumber));
	// GPIO PIN mode is output
	if ((PINConfig->GPIO_Mode == GPIO_Mode_AF_OUT_OD) || (PINConfig->GPIO_Mode == GPIO_Mode_AF_OUT_PP) || (PINConfig->GPIO_Mode == GPIO_Mode_OUT_OD) || (PINConfig->GPIO_Mode == GPIO_Mode_OUT_PP))
	{
		PIN = (((PINConfig -> GPIO_Mode - 4 )<< 2 ) | (PINConfig -> GPIO_Speed )) & 0x0F;
	}

	else {
		//GPIO PIN Mode is input / Analog
		if ((PINConfig->GPIO_Mode == GPIO_Mode_IN_Float) ||  (PINConfig->GPIO_Mode == GPIO_Mode_Analog))
			{
				PIN = ((PINConfig -> GPIO_Mode << 2 ) &0x0F) ;
			}
		else{
			PIN = ((PINConfig -> GPIO_Mode << 2 ) &0x0F) ;

			if (PINConfig -> GPIO_Mode == GPIO_Mode_IN_PU ){
				//ODR = 1 INPUT Pull Up
				GPIOx -> ODR.Reg |= PINConfig -> GPIO_PINNumber;
			}
			else{
				//ODR = 0 INPUT Pull Down
				GPIOx -> ODR.Reg &= ~(PINConfig -> GPIO_PINNumber);
			}

		}
	}
	//write on CRL or CRH
	(*Config_Reg) |= (PIN << Get_CRLH_Position(PINConfig->GPIO_PINNumber));
}


/**================================================================
 * @Fn			-MCAL_GPIO_Deinit
 * @brief 		-Reset all the GPIO Registers
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @retval	 	-none
 * Note			-none
 */

void MCAL_GPIO_Deinit (GPIO_TypeDef* GPIOx ){

	//GPIOx->BRR = 0x00000000;
	//GPIOx->BSRR = 0x00000000;
	//GPIOx->CRH = 0x44444444;
	//GPIOx->CRL = 0x44444444;
	//GPIOx->LCKR = 0x00000000;
	//GPIOx->ODR.Reg= 0x00000000;

	/* use reset Controller APB2 peripheral reset Register (RCC_APB2RSTR)
	set and cleared by software */


	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);

	}
	else if (GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if (GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if (GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if (GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}

}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read specific GPIOx Pin value
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 	-PinNumber : set pin number to read
 * @retval	 	-The Reading value of the input pin
 * Note			-none
 */
uint8_t MCAL_GPIO_ReadPIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number)
{
	uint8_t BitStatus;
	if (( GPIOx->IDR.Reg & PIN_Number) != (uint32_t)GPIO_PIN_RESET)
	{
		BitStatus = GPIO_PIN_SET ;
	}else
	{
		BitStatus = GPIO_PIN_RESET ;
	}

	return BitStatus ;
}


/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief		-Read PORT Value
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @retval 		-The input PORT value (two values based on @ref GPIO_PIN_State)
 * Note 		-None
 */

uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef* GPIOx ){

	uint16_t PortVal;
		PortVal = (uint16_t) GPIOx -> IDR.Reg;
		return PortVal ;
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief		-Write value on specific PIN
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Write on according to @ref GPIO_PINS_Define
 * @param [in]	-Value : PIN value
 * @retval 		-None
 * Note 		-None
 */
void MCAL_GPIO_WritePIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number,uint8_t value )
{

	if (value != GPIO_PIN_SET )
		{
		//Port bit set/reset Register (GPIOx_BSRR)
		//BRy: Port x Reset bit y (y= 0 ... 15)
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		GPIOx -> BRR = (uint32_t) PIN_Number ;
		}
	else
		// Port bit set/reset Register (GPIOx_BSRR)
		// BSy: Port x Reset bit y (y= 0 ... 15)
		// 0: No action on the corresponding ODRx bit
		// 1: Set the corresponding ODRx bit
		GPIOx -> BSRR = (uint32_t) PIN_Number ;
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief		-Write value on PORT
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @param [in]	-Value : PORT value
 * @retval 		-None
 * Note 		-None
 */

void MCAL_GPIO_WritePort (GPIO_TypeDef* GPIOx, uint16_t value ){

	GPIOx->ODR.Reg = (uint32_t) value;
}
/**================================================================
 * @Fn			-MCAL_GPIO_WriteGroup
 * @brief		-Write value on Group of PORT pins
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @param [in]	-Value : Pins value
 * @param [in] 	- Mask : Determine which pins to write on
 * @retval 		-None
 * Note 		-None
 */

void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t Mask)
{
	GPIOx->ODR.Reg &= ~(Mask);				// clear the group value
	GPIOx->ODR.Reg |= (Value & Mask);		// put the new group value
}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief		-Toggle a specific PIN
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Toggled according to @ref GPIO_PINS_Define
 * @retval 		-None
 * Note 		-None
 */

void MCAL_GPIO_TogglePIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number){

	GPIOx->ODR.Reg ^= PIN_Number;
}

/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief		-Locking allows the IO configuration to be frozen
 * @param [in] 	-GPIOx : where x can be (A..E depending on device used) to select the GPIO Peripheral
 * @param [in]	-PinNumber : Specific Pin number to be Locked according to @ref GPIO_PINS_Define
 * @retval 		-Ok if lock is successful , Error if not (according to @ref GPIO_LOCK_State
 * Note 		-None
 */

uint8_t MCAL_GPIO_LockPIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number){

	//	LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR Register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked

	volatile uint32_t Temp_Key = 1<<16 ;

	//write 1
	GPIOx->LCKR |= Temp_Key ;
	//write 0
	GPIOx -> LCKR &= ~(Temp_Key);
	//write 1
	GPIOx->LCKR |= Temp_Key ;
	//read 0
	Temp_Key = GPIOx -> LCKR;
	//read 1
	if ((GPIOx -> LCKR | Temp_Key )== (uint32_t)GPIO_PIN_SET){

		return GPIO_LOCK_Enabled ;
	}
	else{
		return GPIO_LOCK_ERROR ;
	}


}
