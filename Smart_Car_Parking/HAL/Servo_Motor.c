/*
 * Sorce_Motor.c
 *
 *  Created on: Nov 12, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */

#include "Servo_Motor.h"


//Direction of motion
#define UP   1
#define DOWN 2


//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_PinConfig_t PinConfg;
	PinConfg.GPIO_PINNumber=GPIO_PIN8;
	PinConfg.GPIO_Mode = GPIO_Mode_OUT_PP;
	PinConfg.GPIO_Speed =GPIO_Speed_10MHZ;
	MCAL_GPIO_init(GPIOB, &PinConfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN8, 1);
		Timer_dus(500);
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN8, 0);
	}
	if(Direction==DOWN)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN8, 1);
		Timer_dus(1488);
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_PinConfig_t PinConfg;
	PinConfg.GPIO_PINNumber=GPIO_PIN9;
	PinConfg.GPIO_Mode = GPIO_Mode_OUT_PP;
	PinConfg.GPIO_Speed =GPIO_Speed_10MHZ;
	MCAL_GPIO_init(GPIOB, &PinConfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN9, 1);
		Timer_dus(500);
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN9, 0);
	}

	if(Direction == DOWN)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN9, 1);
		Timer_dus(1488);
		MCAL_GPIO_WritePIN(GPIOB, GPIO_PIN9, 0);
	}

}
