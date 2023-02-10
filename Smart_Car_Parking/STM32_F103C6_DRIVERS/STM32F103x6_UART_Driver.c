//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6_UART_Driver.h"



USART_Config_t* Global_USART_Config[3] = {NULL, NULL, NULL};
//void (*GP_IRQ_CallBack)(void);

//===============APIs===================//
//*********Global Functions*********//
uint8_t Get_USART_Index(USART_TypeDef* USARTx){

	if(USARTx == USART1)
		return USART1_INDEX;
	else if(USARTx == USART2)
		return USART2_INDEX;
	else if(USARTx == USART3)
		return USART3_INDEX;

}
/**================================================================
* @Fn- MCAL_USART_init
* @brief 		-Initializes the USARTx PINy according to the specified parameters of PinConfig
* @param [in] 	-USARTx : where x can be (A..E depending on device used) to select USART peripheral
*  @param [in]	-PinConfig : Pointer to USART_PinConfig_t which contains
 * 				 the configuration info for specified USART
* @retval -
* Note			-STM32F103C6 MCU has USART A,B,C,D,E ports
 * 				 but LQFP48 Package has A,B ,Part of C&D
*/

void  MCAL_USART_init (USART_TypeDef* USARTx ,USART_Config_t* USART_Config){

	uint32_t Pclk, BRReg;
	//enable USART clock
	if (USARTx == USART1){
		RCC_USART1_CLOCK_EN();
		Global_USART_Config[USART1_INDEX] = USART_Config;
	}
	else if (USARTx == USART2){
		RCC_USART2_CLOCK_EN();
		Global_USART_Config[USART2_INDEX] = USART_Config;
	}
	else if (USARTx == USART3){
		RCC_USART3_CLOCK_EN();
		Global_USART_Config[USART3_INDEX] = USART_Config;
	}
	//enable USART Module
	//Bit 13 UE: USART enable
	//When this bit is cleared the USART prescalers and outputs are stopped
	USARTx -> CR1 |= 1<<13 ;
	//enable USART send and receive
	//Bit 3 TE: Transmitter enable
	//Bit 2 RE: Receiver enable
	USARTx->CR1 |= USART_Config->USART_Mode;

	//select number of Stop Bits
	USARTx->CR1 |= USART_Config->StopBits;
	//enable or disable HW flow control modes
	USARTx->CR1 |= USART_Config->HWFlowCTRL;

	//configure USART communication baud rate
	if (USARTx == USART1)
		Pclk = MCAL_RCC_GetPCLCK2Freq();
	else
		Pclk = MCAL_RCC_GetPCLCK1Freq();
	BRReg = USART_BRR_Register(Pclk,USART_Config->BaudRate);
	USARTx->BRR = BRReg;

	//enable NVIC for USART IRQ
	if(USART_Config -> IRQ_Enable != USART_IRQ_Enable_NONE)
	{

		USARTx->CR1 |= USART_Config->IRQ_Enable;

		if (USARTx == USART1)
			NVIC_IRQ37_USART1_ENABLE();
		else if (USARTx == USART2)
			NVIC_IRQ38_USART2_ENABLE();
		else if (USARTx == USART3)
			NVIC_IRQ39_USART3_ENABLE();

	}

}


/**================================================================
 * @Fn			-MCAL_USART_Deinit
 * @brief 		-Reset all the USART registers
 * @param [in] 	-USARTx : where x can be (A..E depending on device used) to select USART peripheral
 * @retval	 	-none
 * Note			-none
 */

void MCAL_USART_Deinit (USART_TypeDef* USARTx ){


	//reset USART & disable USART clock
	if (USARTx == USART1){
		RCC_USART1_Reset();
		RCC_USART1_CLOCK_Disable();
	}
	else if (USARTx == USART2){
		RCC_USART2_Reset();
		RCC_USART2_CLOCK_Disable();
	}
	else if (USARTx == USART3){
		RCC_USART3_Reset();
		RCC_USART3_CLOCK_Disable();
	}

}

void  MCAL_USART_SendData (USART_TypeDef *USARTx, char *pTxBuffer,enum Polling_Mechanism PollingEn)
{
	uint8_t USART_Index = Get_USART_Index(USARTx);
	//Bit 7 TXE: Transmit data register empty
	//wait until TXE flag is set
	if (PollingEn == Polling_Enable)
		while(!(USARTx->SR & 1 << 7));

	if (Global_USART_Config[USART_Index]->Payload_Length == USART_Payload_Length_9B )
	{
		USARTx-> DR = (*pTxBuffer&(uint16_t) 0x01FF);
	}else
	{
		// USART_Payload_Length_8B
		USARTx-> DR = (*pTxBuffer&(uint8_t) 0xFF);
	}
}

void  MCAL_USART_ReceiveChar (USART_TypeDef *USARTx,char* RxChar,enum Polling_Mechanism PollingEn)
{
	uint8_t USART_Index = Get_USART_Index(USARTx);
	//Bit 5 RXE:  Read data register not empty
	//wait until RXNE flag is set : Received data is ready to be read.
	if (PollingEn == Polling_Enable)
		while(!(USARTx->SR & 1 << 5));
	if (Global_USART_Config[USART_Index]->Payload_Length == USART_Payload_Length_9B )
	{
		if (Global_USART_Config[USART_Index]->Parity == USART_NONE_Parity ){
			//no parity so all 9bit are considered data
			*((char*)RxChar) = USARTx-> DR ;
		}else
		{
			//parity is used, 8bit is data bits and 1 bit is parity
			*((char*)RxChar) = (USARTx-> DR & (uint8_t)0xFF);
		}

	}else
	{
		//this is 8bit data
		if (Global_USART_Config[USART_Index]->Parity == USART_NONE_Parity )
		{
			*((char*)RxChar) = (USARTx-> DR & (uint8_t)0xFF);

		}else
		{
			//parity is used, 7 bits are only the data bits
			*((char*)RxChar) = (USARTx-> DR & (uint8_t)0x7F);
		}
	}
}


void  MCAL_USART_ReceiveString (USART_TypeDef *USARTx, uint16_t *pRxBuffer,enum Polling_Mechanism PollingEn)
{
	char get_char , i = 0;
	char data[10];
	MCAL_USART_ReceiveChar(USARTx, &get_char, PollingEn);
	while(get_char != '\0'|| get_char != '!' ){
		i++;
		MCAL_USART_ReceiveChar(USARTx, &get_char, Polling_Enable);
		data[i] = get_char;
	}
	data[i] = '\0';
	pRxBuffer = data;
}

void  MCAL_USART_ReceiveNum(USART_TypeDef *USARTx,uint16_t* RxNum, uint8_t Num_len)
{
	char get_char ;
	uint16_t Temp_RxNum;
	int Num_Digit = 1;
	MCAL_USART_ReceiveChar(USARTx, &get_char, Polling_Disable);
	MCAL_USART_SendData(USARTx, &get_char,Polling_Enable );
	while(log10(Temp_RxNum)+1 < Num_len) {
		get_char -= 112;
		if(get_char<=9 && get_char>=0){
			Temp_RxNum =  Temp_RxNum*Num_Digit+(get_char);
			 Num_Digit *= 10;
		}

	if(log10(Temp_RxNum)+1 < Num_len){
		MCAL_USART_ReceiveChar(USARTx, &get_char, Polling_Enable);
		MCAL_USART_SendData(USART1, &get_char,Polling_Enable );

	}
	* RxNum = Temp_RxNum;
	}
}

void MCAL_USART_GPIO_SetPins (USART_TypeDef *USARTx){
	GPIO_PinConfig_t UART_PinConfig;
	if(USARTx == USART1)
	{
		//	USART1_TX  PA9
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN9;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
		UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
		MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		//	USART1_RX  PA10
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN10;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
		MCAL_GPIO_init (GPIOA,&UART_PinConfig);

		if(Global_USART_Config[USART1_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS ||
					Global_USART_Config[USART1_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART1_CTS PA11
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN11;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		}
		else if (Global_USART_Config[USART1_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_RTS ||
					Global_USART_Config[USART1_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART1_RTS PA12
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN12;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		}
	}
	if(USARTx == USART2)
	{
		//	USART2_TX  PA2
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN2;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
		UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
		MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		//	USART1_RX  PA3
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN3;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
		MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		if(Global_USART_Config[USART2_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS ||
			Global_USART_Config[USART2_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART2_CTS PA0
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN0;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		}
		else if (Global_USART_Config[USART2_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_RTS ||
						Global_USART_Config[USART2_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART2_RTS PA1
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN1;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&UART_PinConfig);
		}
	}
	if(USARTx == USART3)
	{
		//	USART3_TX  PB10
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN10;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
		UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
		MCAL_GPIO_init (GPIOB,&UART_PinConfig);
		//	USART3_RX  PA11
		UART_PinConfig.GPIO_PINNumber = GPIO_PIN11;
		UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
		MCAL_GPIO_init (GPIOB,&UART_PinConfig);
		if(Global_USART_Config[USART3_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS ||
					Global_USART_Config[USART3_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART3_CTS PA13
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN13;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOB,&UART_PinConfig);
		}
		else if (Global_USART_Config[USART3_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_RTS ||
						Global_USART_Config[USART3_INDEX]->HWFlowCTRL == USART_HWFlowCTRL_CTS_RTS){
			//	USART3_RTS PA14
			UART_PinConfig.GPIO_PINNumber = GPIO_PIN14;
			UART_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			UART_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOB,&UART_PinConfig);
		}
	}
}

//ISR
void USART1_IRQHandler (void)
{
	enum USART_IRQ_Event flag;
	//received data ready to be read
	if (USART1->SR & 1<<5){
		flag = USART_IRQ_RXNE;
	}
	//Transmission complete
	else if (USART1->SR & 1<<6){
		flag = USART_IRQ_TC;
	}
	//transmit data register empty
	else if (USART1->SR & 1<<7){
		flag = USART_IRQ_TXE;
	}
	//overrun error detected
	else if (USART1->SR & 1<<3){
		flag = USART_IRQ_ORE;
	}
	//Parity error
	else if (USART1->SR & 1<<0){
		flag = USART_IRQ_PE;
	}

	Global_USART_Config[USART1_INDEX]->P_IRQ_CallBack(flag);

}

void USART2_IRQHandler()
{
	enum USART_IRQ_Event flag;
	//transmit data register empty
	if (USART2->SR & 1<<7)
		flag = USART_IRQ_TXE;
	//Transmission complete
	else if (USART2->SR & 1<<6){
		flag = USART_IRQ_TC;
	}
	//received data ready to be read
	else if (USART2->SR & 1<<5){
		flag = USART_IRQ_RXNE;
	}
	//overrun error detected
	else if (USART2->SR & 1<<3){
		flag = USART_IRQ_ORE;
	}
	//Parity error
	else if (USART2->SR & 1<<0){
		flag = USART_IRQ_PE;
	}
	Global_USART_Config[USART2_INDEX]->P_IRQ_CallBack(flag);

}

void USART3_IRQHandler()
{
	enum USART_IRQ_Event flag;
	//transmit data register empty
	if (USART3->SR &1<<7)
		flag = USART_IRQ_TXE;
	//Transmission complete
	else if (USART3->SR & 1<<6){
		flag = USART_IRQ_TC;
		USART3 -> SR = ~(1<<6);
	}
	//received data ready to be read
	else if (USART3->SR & 1<<5){
		flag = USART_IRQ_RXNE;
		USART3 -> SR = ~(1<<5);
	}
	//overrun error detected
	else if (USART3->SR & 1<<3){
		flag = USART_IRQ_ORE;
	}
	//Parity error
	else if (USART3->SR & 1<<0){
		flag = USART_IRQ_PE;
	}

	Global_USART_Config[USART3_INDEX]->P_IRQ_CallBack(flag);

}

