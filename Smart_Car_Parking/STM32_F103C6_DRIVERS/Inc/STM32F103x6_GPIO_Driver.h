#ifndef _STM32F103X6_GPIO_H_
#define _STM32F103X6_GPIO_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------

//-----------------------------
//Configure structure for GPIO
//-----------------------------


typedef struct {
	uint16_t GPIO_PINNumber;   	//pin number of GPIO Port
	//this parameter can be a value of  @ref GPIO_Pins_define

	uint8_t GPIO_Mode;			//mode of GPIO selected pins
	//this parameter can be a value of  @ref GPIO_Mode_define

	uint8_t GPIO_Speed;			//speed of GPIO selected pins
	//this parameter can be a value of  @ref GPIO_Speed_define

}GPIO_PinConfig_t;
//-----------------------------
//Macros Configuration References
//-----------------------------

/*@ref GPIO_Mode_define
 * 0 : Analog Mode
 * 1 : floating input (reset state)
 * 2 : Input with pull-up
 * 3 : Input with Pull-down
 * 4 : General purpose Output Push-pull
 * 5 : General purpose Output Open-drain
 * 6 : Alternate function Output Push-pull
 * 7 : Alternate function Output Open-drain
 * 8 : Alternate function Input
*/

#define GPIO_Mode_Analog				0x00000000U
#define GPIO_Mode_IN_Float				0x00000001U
#define GPIO_Mode_IN_PU					0x00000002U
#define GPIO_Mode_IN_PD					0x00000003U
#define GPIO_Mode_OUT_PP				0x00000004U
#define GPIO_Mode_OUT_OD				0x00000005U
#define GPIO_Mode_AF_OUT_PP				0x00000006U
#define GPIO_Mode_AF_OUT_OD				0x00000007U
#define GPIO_Mode_AF_IN					0x00000008U


/*@ref GPIO_Speed_define

  0 : Output mode, max speed 10 MHz.
  1 : Output mode, max speed 2 MHz.
  2 : Output mode, max speed 50 MHz.

*/
#define GPIO_Speed_NONE					0x00000000U //in condition of input
#define GPIO_Speed_10MHZ				0x00000001U
#define GPIO_Speed_2MHZ					0x00000002U
#define GPIO_Speed_50MHZ				0x00000003U

//@ref GPIO_Pins_define

#define GPIO_PIN0			 	((uint16_t)0x0001)
#define GPIO_PIN1				((uint16_t)0x0002)
#define GPIO_PIN2				((uint16_t)0x0004)
#define GPIO_PIN3				((uint16_t)0x0008)
#define GPIO_PIN4				((uint16_t)0x0010)
#define GPIO_PIN5				((uint16_t)0x0020)
#define GPIO_PIN6				((uint16_t)0x0040)
#define GPIO_PIN7				((uint16_t)0x0080)
#define GPIO_PIN8				((uint16_t)0x0100)
#define GPIO_PIN9				((uint16_t)0x0200)
#define GPIO_PIN10				((uint16_t)0x0400)
#define GPIO_PIN11				((uint16_t)0x0800)
#define GPIO_PIN12				((uint16_t)0x1000)
#define GPIO_PIN13				((uint16_t)0x2000)
#define GPIO_PIN14				((uint16_t)0x4000)
#define GPIO_PIN15				((uint16_t)0x8000)
#define GPIO_All_PINs			((uint16_t)0xFFFF)

#define GPIO_PIN_Mask				0x0000FFFFU //pin mask to test


//@ref GPIO_LOCK_state

#define  GPIO_LOCK_ERROR							0
#define  GPIO_LOCK_Enabled							1

//@ref GPIO_PIN_State

#define  GPIO_PIN_RESET								0
#define  GPIO_PIN_SET								1


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

//initialization APIs
void  MCAL_GPIO_init (GPIO_TypeDef* GPIOx ,GPIO_PinConfig_t* PINConfig);
void  MCAL_GPIO_Deinit (GPIO_TypeDef* GPIOx );

void MCAL_GPIO_SetPIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number,uint8_t mode,uint8_t speed );


//Read APIs
uint8_t MCAL_GPIO_ReadPIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number);
uint16_t MCAL_GPIO_ReadPort (GPIO_TypeDef* GPIOx );

//Write APIs
void MCAL_GPIO_WritePIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number,uint8_t value );
void MCAL_GPIO_WritePort (GPIO_TypeDef* GPIOx, uint16_t value );
void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t Mask);

void  MCAL_GPIO_TogglePIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number);

uint8_t  MCAL_GPIO_LockPIN (GPIO_TypeDef* GPIOx ,uint16_t PIN_Number);

uint8_t Get_CRLH_Position(uint16_t PINNumber);

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

enum Polling_Mechanism
{
	Polling_Disable,
	Polling_Enable
};


#endif
