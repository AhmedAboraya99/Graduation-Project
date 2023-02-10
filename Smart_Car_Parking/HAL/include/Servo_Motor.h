/*
 * Servo_Motor.h
 *
 *  Created on: Nov 12, 2021
 *      Author:  Mostafa Mahmoud Elshiekh
 */



#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

#include "Timer.h"

#define UP   1
#define DOWN 2


void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);

void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);




#endif /* _SERVO_MOTOR_H_ */
