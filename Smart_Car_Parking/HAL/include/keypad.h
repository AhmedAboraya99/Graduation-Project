/*
 * keypad.h
 *
 * Created: 4/22/2021 6:32:00 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6_GPIO_Driver.h"

#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN3
#define R3 GPIO_PIN4
#define C0 GPIO_PIN5
#define C1 GPIO_PIN6
#define C2 GPIO_PIN7


#define KEYPAD_PORT GPIOB


void Keypad_init();
char Keypad_getkey();
char Keypad_getNum(char Num_len);

#endif /* KEYPAD_H_ */
