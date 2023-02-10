/*
 * lcd.c
 *
 * Created: 4/22/2021 3:01:11 PM
 *  Author: Ahmed Aboraya
 */ 

#include "lcd.h"


#define LCD_DATA_PORT(LCD) 		LCD->s_LCDDataPins.GPIOX
#define LCD_CONTROL_PORT(LCD)	LCD->s_LCDCtrlPins.GPIOX

void LCD_clear_screen(s_LCD_Config_t* LCD){
	LCD_WRITE_COMMAND(LCD, LCD_CLEAR_SCREEN);
	LCD->Ch_Counter=0;
}

void LCD_return_home(s_LCD_Config_t* LCD){
	LCD_WRITE_COMMAND(LCD, LCD_RETURN_HOME);
	LCD->Ch_Counter=0;
}

void LCD_lcd_kick(s_LCD_Config_t* LCD){
	MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD),LCD->s_LCDCtrlPins.enpin,GPIO_PIN_SET);
	WAIT_ms(5);
	MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD),LCD->s_LCDCtrlPins.enpin,GPIO_PIN_RESET);
}

void LCD_GOTO_XY(s_LCD_Config_t*  LCD,unsigned char line, unsigned char position){
	uint32_t address;
	if (position < LINE_DIGITS && position >= 0)
	{
		switch(line)
		{
			case 0:
				address = position;
				break;
			case 1:
				address = LCD_BEGIN_AT_ROW1+position;
				break;
			case 2:
				address = LCD_BEGIN_AT_ROW2+position;
				break;
			case 3:
				address = LCD_BEGIN_AT_ROW3+position;
				break;
		}
		LCD->Ch_Counter =line*LINE_DIGITS+position ;
		LCD_WRITE_COMMAND(LCD, LCD_SET_ROW+address);
	}
}
void LCD_GPIO_INIT(s_LCD_Config_t* LCD){

	/*MODE&CNF :make GPIOA (EN_SWITCH,RW_SWITCH,RS_SWITCH) pins
	 	 as floating input(reset state)
	 */
	GPIO_PinConfig_t LCD_pinconfig ={LCD->s_LCDCtrlPins.enpin, GPIO_Mode_OUT_PP, GPIO_Speed_10MHZ};
	MCAL_GPIO_init(LCD_CONTROL_PORT(LCD),&LCD_pinconfig);

	LCD_pinconfig.GPIO_PINNumber = LCD->s_LCDCtrlPins.rspin;
	MCAL_GPIO_init (LCD_CONTROL_PORT(LCD),&LCD_pinconfig);

	LCD->Ch_Counter = 0;
	/************************************************************/

	//MODE&CNF: init GPIOA PIN(0-7) as as push-pull outputs with 10MHZ speed
	if(LCD->e_OperMode < EIGHTBIT_1LINE_7DOT)	// 4 bits
	{
		//*(LCD->s_LCDDataPins.p_DataDireReg) |= (0x0F << LCD->s_LCDDataPins.DataPinStart);
		for(uint8_t i =0;i<4;i++){
			LCD_pinconfig.GPIO_PINNumber = LCD->s_LCDDataPins.DataPinStart << i;
			MCAL_GPIO_init(LCD_DATA_PORT(LCD),&LCD_pinconfig);
		}
	}
	else
	{
		for(uint8_t i =0;i<8;i++){
			LCD_pinconfig.GPIO_PINNumber = LCD->s_LCDDataPins.DataPinStart << i;
			MCAL_GPIO_init(LCD_DATA_PORT(LCD),&LCD_pinconfig);
		}
	}

}

void LCD_INIT(s_LCD_Config_t*  LCD ){

	LCD_GPIO_INIT(LCD);

	LCD_return_home(LCD);				/* send for initialization of LCD  */
	LCD_WRITE_COMMAND(LCD ,FUNCTION_SET + LCD->e_OperMode);
	LCD_WRITE_COMMAND(LCD ,LCD_DISP_CONTROL + LCD->e_DispCtrl);
	LCD_WRITE_COMMAND(LCD,LCD_ENTRY_MODE+LCD->e_EntryMode);
	LCD_clear_screen(LCD);
	LCD_return_home(LCD);				/* send for initialization of LCD  */
	LCD_WRITE_COMMAND(LCD,LCD_SET_ROW);
}

void LCD_check_lcd_isbusy(s_LCD_Config_t*  LCD){


	WAIT_ms(5);
	
}


void LCD_WRITE_COMMAND(s_LCD_Config_t* LCD,unsigned char command){
	LCD_check_lcd_isbusy(LCD);

	if(LCD->e_OperMode < EIGHTBIT_1LINE_7DOT)	// 4 bits
		{

			MCAL_GPIO_WriteGroup(LCD_DATA_PORT(LCD), (((command  & 0xF0)>> DATA_shift) * LCD->s_LCDDataPins.DataPinStart), (0x0F * LCD->s_LCDDataPins.DataPinStart));
			MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD), LCD->s_LCDCtrlPins.rspin, GPIO_PIN_RESET);
			LCD_lcd_kick (LCD);
			MCAL_GPIO_WriteGroup(LCD_DATA_PORT(LCD),((command & 0x0F) * LCD->s_LCDDataPins.DataPinStart), (0x0F*LCD->s_LCDDataPins.DataPinStart) );
			WAIT_ms(1);
		}else{				//8bit mode
			MCAL_GPIO_WritePort(LCD_DATA_PORT(LCD) ,command);
			MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD) ,LCD->s_LCDCtrlPins.rspin,GPIO_PIN_RESET);
		}

	LCD_lcd_kick(LCD);
}
void LCD_WRITE_CHAR(s_LCD_Config_t* LCD, unsigned char character){
	LCD_check_lcd_isbusy(LCD);
	if(LCD->e_OperMode < EIGHTBIT_1LINE_7DOT)	// 4 bits
	{
		MCAL_GPIO_WriteGroup(LCD_DATA_PORT(LCD), (((character  & 0xF0)>> DATA_shift) * LCD->s_LCDDataPins.DataPinStart), (0x0F * LCD->s_LCDDataPins.DataPinStart));
		MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD), LCD->s_LCDCtrlPins.rspin, GPIO_PIN_SET);
		LCD_lcd_kick (LCD);
		MCAL_GPIO_WriteGroup(LCD_DATA_PORT(LCD),((character & 0x0F) * LCD->s_LCDDataPins.DataPinStart), (0x0F*LCD->s_LCDDataPins.DataPinStart) );
		WAIT_ms(1);
	}else{ 		//8-bit
		MCAL_GPIO_WritePort(LCD_DATA_PORT(LCD), character);
		MCAL_GPIO_WritePIN(LCD_CONTROL_PORT(LCD), LCD->s_LCDCtrlPins.rspin, GPIO_PIN_SET);

	}
	LCD_lcd_kick(LCD);


	LCD->Ch_Counter ++;
		if(LCD->Ch_Counter==LINE_DIGITS)
			LCD_GOTO_XY(LCD,1,0);
		else if (LCD->Ch_Counter==2*LINE_DIGITS)
			LCD_GOTO_XY(LCD,2,0);
		else if (LCD->Ch_Counter==3*LINE_DIGITS)
			LCD_GOTO_XY(LCD,3,0);
}


void LCD_WRITE_STRING(s_LCD_Config_t* LCD, char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(LCD,*string++);

	}
}
void LCD_WRITE_NUM(s_LCD_Config_t* LCD, uint32_t number){
	
	int p, k=0;
	int num[20];
	
	while(number)
	{
		num[k]=(number%10)+'0';
		number /= 10;
		k++;
	}
	k--;
	for (p=k;p>=0;p--)
	{
		LCD_WRITE_CHAR(LCD, num[p]);
	}
	
		
}
