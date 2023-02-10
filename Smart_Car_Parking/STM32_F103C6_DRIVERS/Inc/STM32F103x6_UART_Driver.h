#ifndef _STM32F103X6_UART_H_
#define _STM32F103X6_UART_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6_GPIO_Driver.h"
#include "STM32F103x6_RCC_Driver.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

//-----------------------------
//Configure structure for USART
//-----------------------------


enum USART_IRQ_Event
{
	USART_IRQ_TXE,	//transmit data register empty
	USART_IRQ_TC,	//Transmission complete
	USART_IRQ_RXNE,	//received data ready to be read
	USART_IRQ_ORE,	//overrun error detected
	USART_IRQ_PE     //Parity error
};


typedef struct {
	uint8_t USART_Mode;   		//select USART TX/RX mode.
								//@ref USART_Mode_define

	uint32_t BaudRate;			//configure USART communication baud rate
								//@ref BaudRate_define

	uint8_t Payload_Length;			//select transmitted or received data word length (8 or 9 bits)
									// @ref Payload_Length_define

	uint8_t Parity;					//select parity mode
									//@ref Parity_define

	uint8_t StopBits;					//select number of Stop Bits
									//@ref StopBits_define

	uint8_t HWFlowCTRL;					//enable or disable HW flow control modes
										//@ref HWFlowCTRL_define

	uint8_t IRQ_Enable;				//enable or disable USART IRQ TX/RX
										//@ref IRQ_Enable_define

	void (*P_IRQ_CallBack)(enum USART_IRQ_Event );		//pointer to IRQ call back function which will be called once IRQ happened

}USART_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------



//@ref USART_Mode_define
#define USART_MODE_RX		(uint32_t) (1<<2)	//RE = 1
#define USART_MODE_TX		(uint32_t) (1<<3)	//TE = 1
#define USART_MODE_TX_RX	(uint32_t) (1<<2)|(1<<3)

//@ref BaudRate_define
#define USART_BaudRate_2400				2400
#define USART_BaudRate_9600				9600
#define USART_BaudRate_19200			19200
#define USART_BaudRate_57600			57600
#define USART_BaudRate_115200			115200
#define USART_BaudRate_230400			230400
#define USART_BaudRate_460800			460800
#define USART_BaudRate_921600			921600
#define USART_BaudRate_2250000			2250000
#define USART_BaudRate_4500000			4500000

// @ref Payload_Length_define

//Bit 12 M: Word length

#define USART_Payload_Length_8B			(uint32_t) (0)
#define USART_Payload_Length_9B			(uint32_t) (1<<12)

//@ref Parity_define
//Bit 10 PCE: Parity control enable
//Bit 9 PS: Parity selection
#define  USART_NONE_Parity				(uint32_t) (0<<10)
#define  USART_EVEN_Parity				(uint32_t) (1<<10)|(0<<9)
#define  USART_ODD_Parity				(uint32_t) (1<<10)|(1<<9)

//@ref StopBits_define
//Bits 13:12 STOP: STOP bits
#define  USART_1_StopBit				(uint32_t) (0)
#define  USART_Half_StopBit				(uint32_t) (1<<12)
#define  USART_2_StopBit				(uint32_t) (2<<12)
#define  USART_1_Half_StopBit			(uint32_t) (3<<12)

//@ref HWFlowCTRL_define
//Bit 9 CTSE: CTS enable
//Bit 8 RTSE: RTS enable
#define  USART_HWFlowCTRL_CTS			(uint32_t) (1<<9)|(0<<8)
#define  USART_HWFlowCTRL_NONE			(uint32_t) (0<<9)|(0<<8)
#define  USART_HWFlowCTRL_CTS_RTS		(uint32_t) (1<<9)|(1<<8)
#define  USART_HWFlowCTRL_RTS			(uint32_t) (0<<9)|(1<<8)

//@ref IRQ_Enable_define
//Bit 7 TXEIE: TXE interrupt enable
//Bit 6 TCIE: Transmission complete interrupt enable
//Bit 5 RXNEIE: RXNE interrupt enable
//Bit 8 PEIE: PE interrupt enable
#define  USART_IRQ_Enable_NONE			(uint32_t) (0)
#define  USART_IRQ_Enable_TXE			(uint32_t) (1<<7)
#define  USART_IRQ_Enable_TC			(uint32_t) (1<<6)
#define  USART_IRQ_Enable_RXNE			(uint32_t) (1<<5)
#define  USART_IRQ_Enable_PE			(uint32_t) (1<<8)



//@ref USART_IRQ_EN_define
#define  USART_IRQ_ENABLE							1
#define  USART_IRQ_DISABLE							0


/*
 *=======================================================================
 *						GENERIC MACROS
 *=======================================================================
 *
*/

//USART Indexes
#define USART1_INDEX				0
#define USART2_INDEX				1
#define USART3_INDEX				2

/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/

//initialization APIs
void  MCAL_USART_init (USART_TypeDef *USARTx,USART_Config_t* USARTConfig);
void  MCAL_USART_Deinit (USART_TypeDef *USARTx);
void  MCAL_USART_SendData (USART_TypeDef *USARTx, char *pTxBuffer,enum Polling_Mechanism PollingEn);
void  MCAL_USART_ReceiveChar (USART_TypeDef *USARTx,char* RxChar, enum Polling_Mechanism PollingEn);
void  MCAL_USART_ReceiveString (USART_TypeDef *USARTx, uint16_t* pRxBuffer,enum Polling_Mechanism PollingEn);
void  MCAL_USART_ReceiveNum(USART_TypeDef *USARTx, uint16_t* RxNum, uint8_t Num_len);
void  MCAL_USART_GPIO_SetPins (USART_TypeDef *USARTx);


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//BaudRate Calculation
#define USARTDIV(PCLK,BAUD)					(uint32_t) (PCLK/(16*BAUD))
#define USARTDIV_MUL100(PCLK,BAUD)			(uint32_t) (25*PCLK/(4*BAUD))
#define Mantissa_MUL100(PCLK,BAUD)			(uint32_t) (USARTDIV(PCLK,BAUD)*100)
#define Mantissa(PCLK,BAUD)					(uint32_t) USARTDIV(PCLK,BAUD)
#define DIV_Fraction(PCLK,BAUD)				(uint32_t) ((USARTDIV_MUL100(PCLK,BAUD) - Mantissa_MUL100(PCLK,BAUD))*16)
#define USART_BRR_Register(PCLK,BAUD)		(uint32_t) ((Mantissa(PCLK, BAUD)) << 4) | ((DIV_Fraction(PCLK, BAUD)) & 0xF)


//====================
//Generic Variables
//====================
void (*GP_USART_IRQ_Callback[3])(void);


#endif
