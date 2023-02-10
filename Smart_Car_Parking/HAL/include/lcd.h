/*
 * lcd.h
 *
 * Created: 4/22/2021 3:01:25 PM
 *  Author: Ahmed Aboraya
 */ 


#ifndef LCD_H_
#define LCD_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6_GPIO_Driver.h"


#define DATA_shift 4 // in 8 bit mode 0 and in 4 bit mode 4
#define LINE_DIGITS 16		//max digits per Line



#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_RETURN_HOME								(0x02)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_MODE								(0x04)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)

#define LCD_DISP_CONTROL   							(0x08)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)

#define FUNCTION_SET								(0x20)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)

#define LCD_BEGIN_AT_ROW1							(0x40)
#define LCD_BEGIN_AT_ROW2							(0x10)
#define LCD_BEGIN_AT_ROW3							(0x50)
#define LCD_SET_ROW									(0x80)



typedef enum{
	CURSOR_LEFT  = 0x00,
	CURSOR_RIGHT = 0x04,
	DISP_LEFT	 = 0x08,
	DISP_RIGHT	 = 0x0c
	}e_ShiftDir_t;
typedef enum{
	NOSHIFT_DECREMENT=0,
	SHIFT_DECREMENT=1,
	NOSHIFT_INCREMENT=2,
	SHIFT_INCREMENT=3
	}e_EntryMode_t;
typedef enum{
	OFFDISP_OFFCURSOR	=	0x00,
	ONDISP_OFFCURSOR	=	0x04,
	ONDISP_ONCURSOR		=	0x06,
	ONDISP_BLINKCURSOR	=	0x07
	}e_DispCtrl_t;
typedef enum{
	FOURBIT_1LINE_7DOT	=	0x00,
	FOURBIT_1LINE_10DOT	=	0x04,
	FOURBIT_2LINE_7DOT	=	0x08,
	FOURBIT_2LINE_10DOT	=	0x0C,
	EIGHTBIT_1LINE_7DOT	=	0x10,
	EIGHTBIT_1LINE_10DOT=	0x14,
	EIGHTBIT_2LINE_7DOT	=	0x18,
	EIGHTBIT_2LINE_10DOT=	0x1C
	}e_OperMode_t;
	// in this version i separated the struct of the control pins from the struct of data pins in case if the the control pins were in another port
typedef struct {
	GPIO_TypeDef 	*GPIOX;
	uint16_t 		DataPinStart;				//the pin number of the lowest data pin
	}s_LCDDataPins_t;
typedef struct {
	GPIO_TypeDef 	*GPIOX;
	uint16_t 		rspin;						// register select pin
	uint16_t 		enpin;						// enable pin
	}s_LCDCtrlPins_t;
typedef struct{
	s_LCDCtrlPins_t s_LCDCtrlPins;
	s_LCDDataPins_t	s_LCDDataPins ;
	e_EntryMode_t	e_EntryMode;
	e_DispCtrl_t	e_DispCtrl;
	e_OperMode_t	e_OperMode;
	uint8_t 		Ch_Counter;
	}s_LCD_Config_t;
typedef enum {
	COMMAND,
	DATA
}e_LCDCharType_t;

void LCD_INIT(s_LCD_Config_t  *  LCD );
void LCD_WRITE_COMMAND(s_LCD_Config_t* LCD ,unsigned char command);
void LCD_WRITE_CHAR(s_LCD_Config_t* LCD ,unsigned char character);
void LCD_WRITE_STRING(s_LCD_Config_t* LCD ,char* string);
void LCD_WRITE_NUM(s_LCD_Config_t* LCD ,uint32_t number);
void LCD_WRITE_DATA(s_LCD_Config_t* LCD ,unsigned int data);
void LCD_check_lcd_isbusy(s_LCD_Config_t* LCD );
void LCD_lcd_kick(s_LCD_Config_t* LCD );
void LCD_clear_screen(s_LCD_Config_t*  LCD);
void LCD_GOTO_XY(s_LCD_Config_t*  LCD ,unsigned char line, unsigned char position);
void LCD_GPIO_INIT(s_LCD_Config_t*  LCD);


#endif /* LCD_H_ */
