//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6_SPI_Driver.h"



/*
 *=======================================================================
 *						GENERIC VARIABLES
 *=======================================================================
 *
*/

SPI_Config_t* Global_SPI_Config[2] = {NULL,NULL} ;

/*
 *=======================================================================
 *						APIS FUNCTIONS DEFINITIONS
 *=======================================================================
 *
*/

/**================================================================
* @Fn- MCAL_SPI_init
* @brief 		-Initializes the SPIx according to the specified parameters of SPI_Config
* @param [in] 	-SPIx : where x can be (A..E depending on device used) to select SPI peripheral
*  @param [in]	-SPI_Config : Pointer to SPI_Config_t which contains
*  							  the configuration information for the specified SPI Module
 * 				 None
* Note			-STM32F103C6 MCU has SPI MASTER/Slave modes  & NSS Hardware/Software
 *
*/
void  MCAL_SPI_Init(SPI_TypeDef * SPIx, SPI_Config_t * SPI_Config){
	/* Safety for registers before the entire configuration be applied */
	uint16_t Temp_CR1 = 0;
	uint16_t Temp_CR2 = 0;

	//enable SPI clock
	if (SPIx == SPI1)
	{
		RCC_SPI1_CLOCK_EN();
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
	}
	else if (SPIx == SPI2){

		RCC_SPI2_CLOCK_EN();
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
	}

	//enable SPI Module
	//Bit 6 UE: SPI enable
	//When this bit is cleared the SPI prescalers and outputs are stopped
	Temp_CR1 |= 1<<6 ;
	////Select SPI Mode (MASTER/Slave)
	//Bit 2 MSTR:> 1: MASTER , 0: Slave
	if (SPI_Config-> SPI_Mode== SPI_Mode_MASTER)
		Temp_CR1 |= SPI_Config->SPI_Mode;
	else
		Temp_CR1 &= SPI_Config->SPI_Mode;

	//select SPI Frame Format(LSB First/MSB First)
	Temp_CR1 |= SPI_Config->Frame_Format;
	//Select Data Frame Size(8bit/16bit)
	Temp_CR1 |= SPI_Config->Frame_Size;
	//Select SPI Communication Mode
	Temp_CR1 |= SPI_Config->Communication_Mode;
	//Select Clock Polarity
	Temp_CR1 |= SPI_Config->Clock_Polarity;
	//Select Clock Phase
	Temp_CR1 |= SPI_Config->Clock_Phase;

	//Select NSS
	if(SPI_Config->NSS_Management==NSS_Management_SW_SSI_SET||SPI_Config->NSS_Management==NSS_Management_SW_SSI_RESET)
		Temp_CR1 |= SPI_Config->NSS_Management;
	else if (SPI_Config->NSS_Management==NSS_Management_MASTER_HW_SS_OUT)
		Temp_CR2 |= SPI_Config->NSS_Management;
	else
		Temp_CR2 &= SPI_Config->NSS_Management;

	//configure SPI communication clock baud rate(for MASTER)
	if (SPI_Config-> SPI_Mode== SPI_Mode_MASTER)
		Temp_CR1 |= SPI_Config->BaudRate_Prescalar;


	//enable NVIC for SPI IRQ
	if(SPI_Config-> IRQ_Enable != SPI_IRQ_ENABLE_NONE)
	{

		Temp_CR2 |= SPI_Config-> IRQ_Enable;

		if (SPIx == SPI1)
			NVIC_IRQ35_SPI1_ENABLE();
		else if (SPIx == SPI2)
			NVIC_IRQ36_SPI2_ENABLE();


	}else
		Temp_CR2 &= SPI_Config-> IRQ_Enable;

	SPIx-> SPI_CR1 = Temp_CR1;
	SPIx-> SPI_CR2 = Temp_CR2;
}


/**================================================================
 * @Fn			-MCAL_SPI_Deinit
 * @brief 		-Reset all the SPI registers
 * @param [in] 	-SPIx : where x can be (1..3 depending on device used) to select SPI peripheral
 * @retval	 	-none
 * Note			- Reset The module by RCC & Disable NVIC
 */

void MCAL_SPI_DeInit(SPI_TypeDef * SPIx) {


	//reset SPI & disable SPI clock
	if (SPIx == SPI1){
		RCC_SPI1_Reset();
		RCC_SPI1_CLOCK_Disable();
	}
	else if (SPIx == SPI2){
		RCC_SPI2_Reset();
		RCC_SPI2_CLOCK_Disable();
	}


}
/**================================================================
 * @Fn 				-	MCAL_SPI_Send_Data
 * @brief 			-	Send TX Buffer With SPI
 */
void  MCAL_SPI_Send_Data(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_EN)
{

	//Bit 1 TXE: Transmit data register empty

	if (Polling_EN == Polling_Enable)
		//wait until TXE flag is set
		while(!(SPIx->SPI_SR & 1 << 1));

	// Send Data to SPI Data register
	SPIx-> SPI_DR = (*pTxBuffer);

}

/**================================================================
 * @Fn 				-	MCAL_SPI_Recieve_Data
 * @brief 			-	Receive data from SPI RX Buffer
 */

void  MCAL_SPI_Recieve_Data(SPI_TypeDef * SPIx, uint16_t *pRxBuffer, enum Polling_Mechanism Polling_EN){

	//Bit 0 RXNE:  Read data register not empty
	//wait until RXNE flag is set : Received data is ready to be read.
	if (Polling_EN == Polling_Enable)
		while(!(SPIx->SPI_SR & 1<<0));

	//receive data
	*((uint16_t*)pRxBuffer) = SPIx-> SPI_DR ;

}

/**================================================================
 * @Fn 				-	MCAL_SPI_TX_RX
 * @brief 			-	Transmit and Receive Data
 */
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_EN)
{
	//Bit 1 TXE: Transmit data register empty

	if (Polling_EN == Polling_Enable)
		//wait until TXE flag is set
		while(!(SPIx->SPI_SR & 1 << 1));

	// Send Data to SPI Data register
	SPIx-> SPI_DR = (*pTxBuffer);

	//wait until RXNE flag is set : Received data is ready to be read.
	if (Polling_EN == Polling_Enable)
		while(!(SPIx->SPI_SR & 1 ));

	//receive data
	*(pTxBuffer) = SPIx-> SPI_DR ;


}

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx){
	GPIO_PinConfig_t SPI_PinConfig;

	if(SPIx == SPI1)
	{

		//=========MASTER========//
		if(Global_SPI_Config[SPI1_INDEX]->SPI_Mode == SPI_Mode_MASTER){

			//	SPIx_SCK -> PA5
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN5;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//	SPIx_MISO -> PA6
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN6;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_MOSI -> PA7
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN7;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_NSS -> PA4
			if(Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_Management_MASTER_HW_SS_IN){

				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN4;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}
			else if (Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_Management_MASTER_HW_SS_OUT){
				//	SPI1_RTS PA12
				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN4;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
				SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}
		}
		//=========SLAVE========//
		else if(Global_SPI_Config[SPI1_INDEX]->SPI_Mode == SPI_Mode_SLAVE){
			//	SPIx_SCK -> PA5
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN5;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//	SPIx_MISO -> PA6
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN6;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_MOSI -> PA7
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN7;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_NSS -> PA4
			if(Global_SPI_Config[SPI1_INDEX]->NSS_Management == NSS_Management_SLAVE_HW){

				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN4;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}

		}
	}
	if(SPIx == SPI2)
	{

		//=========MASTER========//
		if(Global_SPI_Config[SPI2_INDEX]->SPI_Mode == SPI_Mode_MASTER){

			//	SPIx_SCK -> PA13
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN13;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//	SPIx_MISO -> PA14
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN14;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_MOSI -> PA15
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN15;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_NSS -> PA2
			if(Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_Management_MASTER_HW_SS_IN){

				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN12;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}
			else if (Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_Management_MASTER_HW_SS_OUT){

				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN12;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
				SPI_PinConfig.GPIO_Speed = GPIO_Speed_10MHZ;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}
		}
		//=========SLAVE========//
		else if(Global_SPI_Config[SPI2_INDEX]->SPI_Mode == SPI_Mode_SLAVE){
			//	SPIx_SCK -> PA13
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN13;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//	SPIx_MISO -> PA14
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN14;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_AF_OUT_PP;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_MOSI -> PA15
			SPI_PinConfig.GPIO_PINNumber = GPIO_PIN15;
			SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
			MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			//SPIx_NSS -> PA12
			if(Global_SPI_Config[SPI2_INDEX]->NSS_Management == NSS_Management_MASTER_HW_SS_IN){

				SPI_PinConfig.GPIO_PINNumber = GPIO_PIN12;
				SPI_PinConfig.GPIO_Mode = GPIO_Mode_IN_Float;
				MCAL_GPIO_init (GPIOA,&SPI_PinConfig);
			}

		}
	}
}

//ISR
void SPI1_IRQHandler (void)
{
	struct SPI_IRQ_Src irq_src;
	irq_src.SPI_TXE = ((SPI1->SPI_SR & (1<<1)) >> 1);
	irq_src.SPI_RXNE = ((SPI1->SPI_SR & (1<<0)) >> 0);
	irq_src.SPI_ERRI = ((SPI1->SPI_SR & (1<<4)) >> 4);
	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler()
{
	struct SPI_IRQ_Src irq_src;
	irq_src.SPI_TXE = ((SPI2->SPI_SR & (1<<1)) >> 1);
	irq_src.SPI_RXNE = ((SPI2->SPI_SR & (1<<0)) >> 0);
	irq_src.SPI_ERRI = ((SPI2->SPI_SR & (1<<4)) >> 4);
	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_src);
}



