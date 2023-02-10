/*
 * Bit_Math.h
 *
 * Created: 7/27/2022 6:03:17 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_
#include <math.h>
#define Set_Bit(Reg, Bit)		(Reg |= (1<<Bit))
#define Reset_Bit(Reg,Bit)		(Reg &=~ (1<<Bit))
#define Toggle_Bit(Reg,Bit)		(Reg ^= (1<<Bit))
#define Get_Bit(Reg,Bit)		((Reg >> Bit) & 1)

#define Set_Pin(Reg, Pin)		(Reg |= Pin)
#define Reset_Pin(Reg, Pin)		(Reg &=~ Pin)
#define Toggle_Pin(Reg, Pin)	(Reg ^= Pin)

#define Set_Config(Reg, Config)			Set_Pin(Reg, Config)
#define Reset_Config(Reg, Config)		(Reg &= Config)
#define Set_Port(Port)					(Port = 0xFF)
#define Reset_Port(Port)				(Port = 0x00)
#define Write_Port(Port, value)			(Port = value)

#define Set_Bitfield(Bitfield)			(Bitfield = 1)
#define Reset_Bitfield(Bitfield)		(Bitfield = 0)




#endif /* BIT_MATH_H_ */
