#ifndef _STM32F103X6_H_
#define _STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "Bit_Math.h"
#include "Platform_Types.h"
//-----------------------------
//Base addresses for Memories
//-----------------------------

#define Flash_Memory_Base 				0x08000000UL
#define	System_Memory_Base				0x1FFFF000UL

#define	SRAM_Base						0x20000000UL
#define Peripherals_Base 				0x40000000UL
#define Cortex_M3_Peripherals_Base 		0xE0000000UL


//-----------------------------
//Base addresses for ABP2 Peripherals
//-----------------------------
//GPIO

//0x4001 1400 - 0x4001 17FF GPIO Port D
//0x4001 1000 - 0x4001 13FF GPIO Port C
//0x4001 0C00 - 0x4001 0FFF GPIO Port B
//0x4001 0800 - 0x4001 0BFF GPIO Port A
//0x4001 0400 - 0x4001 07FF EXTI Section
//0x4001 0000 - 0x4001 03FF AFIO

#define GPIOA_Base		(Peripherals_Base+0x00010800UL)
#define GPIOB_Base		(Peripherals_Base+0x00010C00UL)
#define GPIOC_Base		(Peripherals_Base+0x00011000UL)
#define GPIOD_Base		(Peripherals_Base+0x00011400UL)
#define GPIOE_Base		(Peripherals_Base+0x00011800UL)

#define EXTI_Base		(Peripherals_Base+0x00010400UL)
#define AFIO_Base		(Peripherals_Base+0x00010000UL)

#define USART1_Base		(Peripherals_Base+0x00013800UL)



//SPI1
#define SPI1_Base				(Peripherals_Base+0x00013000UL)
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base		(Peripherals_Base+0x00021000UL)

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_Base		(Peripherals_Base+0x00004400UL)
#define USART3_Base		(Peripherals_Base+0x00004800UL)

//SPI2
#define SPI2_Base			(Peripherals_Base+0x00003800UL)


//NVIC
#define NVIC_BASE						0xE000E100UL
#define NVIC_ISER0						*(vuint32_t*)(NVIC_BASE + 0x000)
#define NVIC_ISER1						*(vuint32_t*)(NVIC_BASE + 0x004)
#define NVIC_ISER2						*(vuint32_t*)(NVIC_BASE + 0x008)
#define NVIC_ICER0						*(vuint32_t*)(NVIC_BASE + 0x080)
#define NVIC_ICER1						*(vuint32_t*)(NVIC_BASE + 0x084)
#define NVIC_ICER2						*(vuint32_t*)(NVIC_BASE + 0x088)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	vuint32_t CRL;
	vuint32_t CRH;
	union{
		struct{
			vuint32_t Pin0:1;
			vuint32_t Pin1:1;
			vuint32_t Pin2:1;
			vuint32_t Pin3:1;
			vuint32_t Pin4:1;
			vuint32_t Pin5:1;
			vuint32_t Pin6:1;
			vuint32_t Pin7:1;
			vuint32_t Pin8:1;
			vuint32_t Pin9:1;
			vuint32_t Pin10:1;
			vuint32_t Pin11:1;
			vuint32_t Pin12:1;
			vuint32_t Pin13:1;
			vuint32_t Pin14:1;
			vuint32_t Pin15:1;
			uint32_t  Reserved:16;
		}Pins;
		vuint32_t Reg;
	}IDR;
	union{
		struct{
			vuint32_t Pin0:1;
			vuint32_t Pin1:1;
			vuint32_t Pin2:1;
			vuint32_t Pin3:1;
			vuint32_t Pin4:1;
			vuint32_t Pin5:1;
			vuint32_t Pin6:1;
			vuint32_t Pin7:1;
			vuint32_t Pin8:1;
			vuint32_t Pin9:1;
			vuint32_t Pin10:1;
			vuint32_t Pin11:1;
			vuint32_t Pin12:1;
			vuint32_t Pin13:1;
			vuint32_t Pin14:1;
			vuint32_t Pin15:1;
			uint32_t  Reserved:16;
		}Pins;
		vuint32_t Reg;
	}ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;

}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR[4];
	uint32_t 	RESERVED0;
	vuint32_t MAPR2;

}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;

}EXTI_TypeDef;


typedef struct{

	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;

}USART_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	vuint32_t SPI_CR1;
	vuint32_t SPI_CR2;
	vuint32_t SPI_SR;
	vuint32_t SPI_DR;
	vuint32_t SPI_CRCPR;
	vuint32_t SPI_RXCRCR;
	vuint32_t SPI_TXCRCR;
	vuint32_t SPI_I2SCFGR;
	vuint32_t SPI_I2SPR;
}SPI_TypeDef;
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{

	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
	vuint32_t AHBSTR;
	vuint32_t CFGR2;

}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA						((GPIO_TypeDef*)GPIOA_Base)
#define GPIOB						((GPIO_TypeDef*)GPIOB_Base)
#define GPIOC						((GPIO_TypeDef*)GPIOC_Base)
#define GPIOD						((GPIO_TypeDef*)GPIOD_Base)
#define GPIOE						((GPIO_TypeDef*)GPIOE_Base)
//GPIO_TypeDef *GPIOA = 	(GPIO_TypeDef *) GPIOA_Base;
//GPIO_TypeDef *GPIOB = 	(GPIO_TypeDef *) GPIOB_Base;
//GPIO_TypeDef *GPIOC = 	(GPIO_TypeDef *) GPIOC_Base;
//GPIO_TypeDef *GPIOD = 	(GPIO_TypeDef *) GPIOD_Base;
//GPIO_TypeDef *GPIOE = 	(GPIO_TypeDef *) GPIOE_Base;

#define EXTI						((EXTI_TypeDef *)  EXTI_Base)
#define AFIO						((AFIO_TypeDef *)  AFIO_Base)
#define RCC							((RCC_TypeDef *)   RCC_Base)
#define USART1						((USART_TypeDef *) USART1_Base)
#define USART2						((USART_TypeDef *) USART2_Base)
#define USART3						((USART_TypeDef *) USART3_Base)

#define SPI1						((SPI_TypeDef *)   SPI1_Base)
#define SPI2						((SPI_TypeDef *)   SPI2_Base)

//EXTI_TypeDef *EXTI  =	(EXTI_TypeDef *)  EXTI_Base;
//AFIO_TypeDef *AFIO  = 	(AFIO_TypeDef *)  AFIO_Base;
//RCC_TypeDef  *RCC   = 	(RCC_TypeDef *)   RCC_Base;
//
//USART_TypeDef  *USART1   = (USART_TypeDef *)   USART1_Base;
//USART_TypeDef  *USART2   = (USART_TypeDef *)   USART2_Base;
//USART_TypeDef  *USART3   = (USART_TypeDef *)   USART3_Base;
//
//SPI_TypeDef *SPI1 = (SPI_TypeDef *)   SPI1_Base;
//
//SPI_TypeDef *SPI2 = (SPI_TypeDef *)   SPI2_Base;



//-*-*-*-*-*-*-*-*-*-*-*-
//IVT Macros
//-*-*-*-*-*-*-*-*-*-*-*
// @ref IVT_IRQ_Number
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39

//SPI
#define SPI1_IRQ		35
#define SPI2_IRQ		36

// NVIC_IRQ Enable / Disable
#define NVIC_IRQ6_EXTI0_ENABLE()			(NVIC_ISER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_ENABLE()			(NVIC_ISER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_ENABLE()			(NVIC_ISER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_ENABLE()			(NVIC_ISER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_ENABLE()			(NVIC_ISER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_ENABLE()			(NVIC_ISER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_ENABLE()		(NVIC_ISER1 |= 1<<8) 	//40-32

#define NVIC_IRQ6_EXTI0_DISABLE()			(NVIC_ICER0 |= 1<<EXTI0_IRQ)
#define NVIC_IRQ7_EXTI1_DISABLE()			(NVIC_ICER0 |= 1<<EXTI1_IRQ)
#define NVIC_IRQ8_EXTI2_DISABLE()			(NVIC_ICER0 |= 1<<EXTI2_IRQ)
#define NVIC_IRQ9_EXTI3_DISABLE()			(NVIC_ICER0 |= 1<<EXTI3_IRQ)
#define NVIC_IRQ10_EXTI4_DISABLE()			(NVIC_ICER0 |= 1<<EXTI4_IRQ)
#define NVIC_IRQ23_EXTI5_9_DISABLE()		(NVIC_ICER0 |= 1<<EXTI5_IRQ)
#define NVIC_IRQ40_EXTI10_15_DISABLE()		(NVIC_ICER1 |= 1<<8)	//40-32

//USART
#define NVIC_IRQ37_USART1_ENABLE()			(NVIC_ISER1 |= 1<<(USART1_IRQ-32))
#define NVIC_IRQ38_USART2_ENABLE()			(NVIC_ISER1 |= 1<<(USART2_IRQ-32))
#define NVIC_IRQ39_USART3_ENABLE()			(NVIC_ISER1 |= 1<<(USART3_IRQ-32))

#define NVIC_IRQ37_USART1_DISABLE()			(NVIC_ICER1 |= 1<<(USART1_IRQ-32))
#define NVIC_IRQ38_USART2_DISABLE()			(NVIC_ICER1 |= 1<<(USART2_IRQ-32))
#define NVIC_IRQ39_USART3_DISABLE()			(NVIC_ICER1 |= 1<<(USART3_IRQ-32))

//SPI
#define NVIC_IRQ35_SPI1_ENABLE()				(NVIC_ISER1 |= 1<<(SPI1_IRQ-32))
#define NVIC_IRQ36_SPI2_ENABLE()				(NVIC_ISER1 |= 1<<(SPI2_IRQ-32))

#define NVIC_IRQ35_SPI1_DISABLE()				(NVIC_ICER1 |= 1<<(SPI1_IRQ-32))
#define NVIC_IRQ36_SPI2_DISABLE()				(NVIC_ICER1 |= 1<<(SPI2_IRQ-32))


/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */


#endif

