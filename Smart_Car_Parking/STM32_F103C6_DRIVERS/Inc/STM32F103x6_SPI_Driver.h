/*
 * STM32F103Cx_SPI_Driver.h
 *
 *  Created on: Jul 16, 2022
 *      Author: Ahmed Aboraya
 */

#ifndef STM32F103CX_SPI_DRIVER_H_
#define STM32F103CX_SPI_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------


#include "STM32F103x6_GPIO_Driver.h"
#include "STM32F103x6_RCC_Driver.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------

//@ref SPI_IRQ_Src_define
struct SPI_IRQ_Src{
	uint8_t 	SPI_TXE:1;		//TX Buffer is Empty
	uint8_t		SPI_RXNE:1;		//RX Buffer is Not Empty
	uint8_t		SPI_ERRI:1;		//Error interrupt
	uint8_t		Reserved:5;
};

typedef struct{
	uint16_t SPI_Mode; 				//select SPI Master/Slave mode.
	//@ref SPI_Mode_define

	uint16_t Frame_Format;			//specifies Data be shifted out either MSB-first or LSB-first
	//@ref Frame_Format_define

	uint16_t Frame_Size;			//specifies the size of the data programmed 8-bit or 16_bit
	//@ref Frame_Size_define

	uint16_t Communication_Mode;	//specifies SPI Communication mode
	//@ref Communication_Mode_define

	uint16_t Clock_Polarity;		// specifies SPI clock Polarity idle on low or idle on high
	//@ref Clock_Polarity_define

	uint16_t Clock_Phase;			// specifies SPI clock Phase "first clock capture or second clock capture"
	//@ref Clock_Phase_define

	uint16_t NSS_Management;		// specifies slave select management by hardware or by software
	//@ref NSS_Management_define

	uint16_t BaudRate_Prescalar;		//  define the serial clock baud rate prescalar
	// @ref BaudRate_Prescalar_define

	uint16_t IRQ_Enable;				// enable or disable SPI interrupt request
	// @ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(struct SPI_IRQ_Src Curr_IRQ_Src );		//pointer to IRQ call back function which will be called once IRQ happened
	//specify the source of the IRQ @ref SPI_IRQ_Src_define


}SPI_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------


//@ref SPI_Mode_define
#define SPI_Mode_MASTER						(uint16_t) (1<<2)
#define SPI_Mode_SLAVE						(uint16_t) ~(1<<2)

//@ref Frame_Format_define
#define  Frame_Format_LSB_FIRST				(uint16_t) (1<<7)
#define  Frame_Format_MSB_FIRST				(uint16_t) (0)
//@ref Frame_Size_define
#define  Frame_Size_16BIT					(uint16_t) (1<<11)
#define  Frame_Size_8BIT					(uint16_t) (0)
//@ref Communication_Mode_define
#define  Data_Mode_UNIDI_Full_Duplex		(uint16_t) (0)
#define  Data_Mode_UNIDI_Receive_Only		(uint16_t) (1<<10)
#define  Data_Mode_BIDI_Receive_Only		(uint16_t) (1<<15)
#define  Data_Mode_BIDI_Transmit_Only		(uint16_t) (1<<15) | (1<<14)
//@ref Clock_Polarity_define
#define Clock_Polarity_Idle_LOW				(uint16_t) (0)
#define Clock_Polarity_Idle_HIGH			(uint16_t) (1<<1)

//@ref Clock_Phase_define
#define Clock_Phase_First_Capture			(uint16_t) (0)
#define Clock_Phase_Second_Capture			(uint16_t) (1<<0)

//@ref NSS_Management_define
//HARDWARE (SPI_CR2 Register)
#define NSS_Management_SLAVE_HW				(uint16_t) ~(1<<2)
#define NSS_Management_MASTER_HW_SS_OUT		(uint16_t) (1<<2)		//cannot work in a MultiMaster environment
#define NSS_Management_MASTER_HW_SS_IN		(uint16_t) ~(1<<2)			//the cell can work in multimaster configuration
//SOFTWARE(NSS is driven by software for master or slave)
//(SPI_CR1 Register)
#define NSS_Management_SW_SSI_SET			(uint16_t) ((1<<9) | (1<<8))
#define NSS_Management_SW_SSI_RESET 		(uint16_t) (1<<9)

// @ref BaudRate_Prescalar_define
#define BaudRate_Prescalar_PLCK_Divide_BY_2					(uint16_t) (0)
#define BaudRate_Prescalar_PLCK_Divide_BY_4					(uint16_t) (1<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_8					(uint16_t) (2<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_16				(uint16_t) (3<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_32				(uint16_t) (4<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_64				(uint16_t) (5<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_128				(uint16_t) (6<<3)
#define BaudRate_Prescalar_PLCK_Divide_BY_256				(uint16_t) (7<<3)

// @ref IRQ_Enable_define
#define SPI_IRQ_ENABLE_NONE					(uint16_t) ~(7<<5)			// IRQ Disable
#define SPI_IRQ_ENABLE_TXEIE				(uint16_t) (1<<7)		// TX buffer empty interrupt enable
#define SPI_IRQ_ENABLE_RXNEIE				(uint16_t) (1<<6)		// RX buffer not empty interrupt enable
#define SPI_IRQ_ENABLE_ERRIE				(uint16_t) (1<<5)		// Error interrupt enable

/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/

#define SPI1_INDEX				0
#define SPI2_INDEX				1


/*
* ==============================================================================
* 				  APIs Supported by "MCAL SPI DRIVER"
* ==============================================================================
*/

void MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config_t * SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef * SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_Send_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);
void MCAL_SPI_Recieve_Data(SPI_TypeDef * SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_En);

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_En);

#endif /* STM32F103CX_SPI_DRIVER_H_ */
