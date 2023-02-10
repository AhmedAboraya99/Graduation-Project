#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/*===============Learn in depth================*/
/*===Second term project Smart Car Barking=====*/
/*Eng : Ahmed Aboraya */



#include "Lcd.h"
#include "STM32F103x6_UART_Driver.h"
#include "Servo_Motor.h"
#include "Timer.h"
#include "keypad.h"


/*=================Global Variables===============*/
uint16_t RFID_CARD_Enter ;
uint16_t RFID_CARD_EXIT ;
#define ID_Length  (uint8_t)2

uint8_t pass[3] ={0};

Std_Bool_t EntryID_Flag = FALSE;
Std_Bool_t ExitID_Flag = FALSE;

Std_Bool_t EntryCar_Flag = FALSE;
Std_Bool_t ExitCar_Flag = FALSE;

#define  PIR1_PinVal   GPIOA->IDR.Pins.Pin7
#define  PIR2_PinVal   GPIOA->IDR.Pins.Pin1
unsigned char Available_Slots= 3;
uint8_t Search_Done = 0;

/*=================Global Functions===============*/

void WAIT_ms(uint32_t t){
	uint32_t i,j;
	for(i=0;i<t;i++){
		for(j=0;j<255;j++);
	}
}
/*=================Functions Prototype===============*/
void RFID_CARD_Enter_CallBack(void);
void RFID_CARD_EXIT_CallBack(void);

void LCD_Welcome(void);
void LCD_Display_Empty_Slots(void);
void LEDs_Init(void);
void LEDs_Control(LED_Define_t LED);
void PIRs_Init(void);
void Store_IDs_From_Admin(void);
int a2i(char* txt);

/*=================Set Configurations ===============*/
s_LCD_Config_t LCD={

		{GPIOB, GPIO_PIN11, GPIO_PIN10},	//Control Pins
		{GPIOB,GPIO_PIN12},				//Data Pins
		NOSHIFT_INCREMENT,				//entry mode
		ONDISP_BLINKCURSOR,				//display control
		FOURBIT_2LINE_7DOT				//operation mode
		,0
};

s_LCD_Config_t LCD2={
		{GPIOA, GPIO_PIN5, GPIO_PIN6},	//Control Pins
		{GPIOA,GPIO_PIN12},				//Data Pins
		NOSHIFT_INCREMENT,				//entry mode
		ONDISP_BLINKCURSOR,				//display control
		FOURBIT_2LINE_7DOT				//operation mode
		,0
};

USART_Config_t USART1_Config = { USART_MODE_TX_RX,
								USART_BaudRate_115200,
								USART_Payload_Length_8B,
								USART_NONE_Parity,
								USART_1_StopBit,
								USART_HWFlowCTRL_NONE,
								USART_IRQ_Enable_RXNE,
								RFID_CARD_Enter_CallBack};

USART_Config_t USART2_Config = { USART_MODE_TX_RX,
								USART_BaudRate_115200,
								USART_Payload_Length_8B,
								USART_NONE_Parity,
								USART_1_StopBit,
								USART_HWFlowCTRL_NONE,
								USART_IRQ_Enable_RXNE,
								RFID_CARD_EXIT_CallBack};



void Clock_Init(void){
	RCC_GPIOA_CLOCK_EN();
	RCC_GPIOB_CLOCK_EN();
	RCC_AFIO_CLOCK_EN();
}

int main(void)
{
	Clock_Init();
	Keypad_init();
	Timer2_init();
	Servo1_Entry_Gate_Init();
	Servo2_Exit_Gate_Init();


	//==========================Connected Hardware INIT=============================
	LCD_INIT(&LCD);
	LCD_INIT(&LCD2);
	LEDs_Init();
	PIRs_Init();

	/*==========Enter IDs To Store In Array Pass==========*/
	 Store_IDs_From_Admin();

	/*Dash Bord LCD*/
	LCD_Welcome();
	Timer_dms(200);
	LCD_Display_Empty_Slots();

	//==========================UART1 INIT=============================
	/* PA9  TX
	 * PA10 RX
	 * PA11 CTC
	 * PA12 RTS
	 */
	MCAL_USART_init(USART1 , &USART1_Config);


	//==========================UART2 INIT=============================
	/* PA2  ->TX
	 * PA3 ->RX
	 * PA0 ->CTS
	 * PA1 ->RTS
	 */
	MCAL_USART_init(USART2, &USART2_Config);

	while(1)
	{
		//Reset Flags

		//Entry/Exit Operation
		if( Available_Slots>0 )
		{
			LCD_GOTO_XY(&LCD2, (LCD2.Ch_Counter/16)+1, 0);
			LCD_WRITE_STRING(&LCD2,"Plz Enter ur ID");
			while(EntryID_Flag == FALSE && ExitID_Flag == FALSE);

		}
		/*======Parking is full so not allow enter cars=======*/
		else if (Available_Slots == 0)
		{
			LCD_GOTO_XY(&LCD2, (LCD2.Ch_Counter/16)+1, 0);
			LCD_WRITE_STRING(&LCD2,"NO Available Slots");
			LCD_GOTO_XY(&LCD2, (LCD2.Ch_Counter/16)+1, 0);
			LCD_WRITE_STRING(&LCD2,"Come Back Later");
			continue;
		}

		//Search about ID in array of Pass
		for(int i=0;i<3;i++)
		{
			if (EntryID_Flag == TRUE){

				if(RFID_CARD_Enter == pass[i]){
					LEDs_Control(GREEN_LED);
					LCD_WRITE_STRING(&LCD2,"Successful Entry");
					Available_Slots--;
					EntryCar_Flag = TRUE;
					RFID_CARD_Enter = 0;
					EntryID_Flag = FALSE;

					break;
				}
			}
			else if (ExitID_Flag == TRUE){
				if(RFID_CARD_EXIT == pass[i]){
					LEDs_Control(GREEN_LED);
					LCD_WRITE_STRING(&LCD2,"Successful Exit");
					Available_Slots++;
					ExitCar_Flag = TRUE;

					ExitID_Flag = FALSE;
					RFID_CARD_EXIT = 0;
					break;
					}
			}
			Search_Done = 1;
		}
		/*==================Wrong Id====================*/
		if ((RFID_CARD_EXIT>0 || RFID_CARD_Enter>0) && Search_Done == 1){
			LEDs_Control(RED_LED);
			LCD_WRITE_STRING(&LCD2,"Wrong ID! Please Enter a valid one");
			Search_Done = 0;
			RFID_CARD_EXIT = 0;
			RFID_CARD_Enter = 0;
		}
		/*=====================Enter gate=====================*/
		if(EntryCar_Flag == TRUE){
			Servo1_Entry_Gate(UP);
			while(PIR1_PinVal);
			WAIT_ms(10000);
			Servo1_Entry_Gate(DOWN);
			EntryCar_Flag = FALSE;
		}
		/*===================Exit gate====================*/
		if(ExitCar_Flag == TRUE){
			Servo2_Exit_Gate(UP);
			while(PIR2_PinVal);
			WAIT_ms(10000);
			Servo2_Exit_Gate(DOWN);
			ExitCar_Flag = FALSE;
		}



	}

	return 0;
}


/*Call Back For UART*/
void RFID_CARD_Enter_CallBack(void)
{
	char *ID_String;
	MCAL_USART_ReceiveNum(USART1,ID_String,ID_Length );
	RFID_CARD_Enter = *ID_String;

	EntryID_Flag = TRUE;
}

void RFID_CARD_EXIT_CallBack(void)
{

	char *ID_String;
	MCAL_USART_ReceiveNum(USART2,ID_String,ID_Length );
	RFID_CARD_EXIT = *ID_String;

	ExitID_Flag = TRUE;
}



void LCD_Welcome(void)
{
	/*Dash Bord LCD*/

	LCD_WRITE_COMMAND(&LCD2, LCD_DISP_ON);
	LCD_WRITE_COMMAND(&LCD2, LCD_CLEAR_SCREEN);
	LCD_GOTO_XY(&LCD2, 0, 0);
	LCD_WRITE_STRING(&LCD2,"Welcome in");
	LCD_GOTO_XY(&LCD2, 1, 0 );
	LCD_WRITE_STRING(&LCD2,"Ahmed'S Parking");
}

void LCD_Display_Empty_Slots(void)
{
	LCD_WRITE_COMMAND(&LCD2, LCD_DISP_ON);
	LCD_WRITE_COMMAND(&LCD2, LCD_CLEAR_SCREEN);
	LCD_GOTO_XY(&LCD2, 0, 0);
	LCD_WRITE_STRING(&LCD2,"Empty Slots=");
	LCD_GOTO_XY(&LCD2, 0, 13);
	LCD_WRITE_NUM(&LCD2,Available_Slots);
}

void LEDs_Init(void)
{
	//RED LED A0
	GPIO_PinConfig_t LED_pincfg = { GPIO_PIN0 , GPIO_Mode_OUT_PP, GPIO_Speed_NONE};
	MCAL_GPIO_init(GPIOA, &LED_pincfg);
	//GREEN LED A11
	LED_pincfg.GPIO_PINNumber = GPIO_PIN11;
	MCAL_GPIO_init(GPIOA, &LED_pincfg);
}
void LEDs_Control(LED_Define_t LED)
{
	//RED LED A0
		if(LED == RED_LED){
			MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN0, GPIO_PIN_SET);
			Timer_dms(2000);
			MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN0, GPIO_PIN_RESET);
		}//GREEN LED A11
		else if(LED == GREEN_LED){
			MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN11, GPIO_PIN_SET);
			Timer_dms(2000);
			MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN11, GPIO_PIN_RESET);
	}
}
void PIRs_Init(void)
{
	//PIR1 A7
	GPIO_PinConfig_t PinConfg;
	PinConfg.GPIO_PINNumber=GPIO_PIN7;
	PinConfg.GPIO_Mode = GPIO_Mode_IN_PU;
	MCAL_GPIO_init(GPIOA, &PinConfg);

	//PIR2 A1
	PinConfg.GPIO_PINNumber=GPIO_PIN1;
	PinConfg.GPIO_Mode = GPIO_Mode_IN_PU;
	MCAL_GPIO_init(GPIOA, &PinConfg);

//	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN0, GPIO_PIN_SET); //make A0 ground
//	MCAL_GPIO_WritePIN(GPIOA, GPIO_PIN11, GPIO_PIN_SET); //make A11 ground

}

void Store_IDs_From_Admin(void)
{
	LCD_WRITE_COMMAND(&LCD, LCD_DISP_ON);
	LCD_WRITE_COMMAND(&LCD, LCD_CLEAR_SCREEN);
	LCD_WRITE_STRING(&LCD,"<Enter Auth IDs>");
	for(char i=0;i<Available_Slots;i++){
		LCD_GOTO_XY(&LCD, i+1, 0);
		LCD_WRITE_STRING(&LCD,"Auth ID");
		LCD_WRITE_NUM(&LCD,i+1);
		LCD_WRITE_STRING(&LCD,":");
		pass[i] = Keypad_getNum(ID_Length);
		LCD_WRITE_NUM(&LCD,pass[i]);
	}
}

int a2i(char* txt)
{
    int sum,digit,i = 0;
    sum = atoi(txt);
    do {
        sum /= 10;
        digit = (txt[i])-48;
        i++;
    } while (sum != 0);
    return digit;

}
