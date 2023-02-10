/*
 * ualtra_sonic.c
 *
 * Created: 2/15/2022 4:18:43 PM
 *  Author: 20128
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "UART_Driver.h"
#include "avr/interrupt.h"

#define F_CPU  8000000UL


char data;
int main(void)
{
	MCAL_USART_init();
	
	sei();  //Global Interrupt
	DDRD|=(1<<7)|(1<<5)|(1<<4)|(1<<1);
	DDRC|=(1<<1);
	DDRC|=(1<<6); 
	
	DDRA|=(1<<6);
	DDRA|=(1<<7);

	DDRA|=(1<<1);
	DDRA|=(1<<2);
	
	DDRD &=~(1<<2);
	PORTD |=(1<<2);
	
	MCUCR=0;
	GICR=(1<<INT0);
	
	
	
	char counter,i,old=-1;
	int x,b,high,distance;
	
    while(1)
    {
		data=0;

		TCCR1A = 0;
		TCCR1B=0;
		TIFR = (1<<ICF1);  	
		PORTD|=(1<<7);
		_delay_us(50);
		PORTD&=(~(1<<7));
		
		TCCR1B = 0xc1;  	
		while ((TIFR&(1<<ICF1)) == 0);
		x = ICR1;
		TIFR = (1<<ICF1);  	
		TCCR1B = 0x81;  	
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		
		TIFR = (1<<ICF1);  	
		TCNT1=0;
		TCCR1B = 0;  		
		high=b-x;
		distance=((high*34600)/(F_CPU*2)) ;
		
		if (distance<=6)
		{
			PORTD |=(1<<4);
			data |=(1<<0);
			_delay_ms(200);
		}
		else
		{
			PORTD &=~(1<<4);
			data &=~(1<<0);
			_delay_ms(200);
		}
		
		
		

		
		PORTC|=(1<<1);
		_delay_us(50);
		PORTC&=(~(1<<1));

		TCCR0=0x01;
		
		high=0;	

		while ((PINC&(1<<0)) == 0);
		TCNT0=0;
		while ((PINC&(1<<0)) == 1)
		{
			if ((TIFR&(1<<TOV0)) == 1)
			{
				high+=256;
				TIFR|=(1<<0);
			}
		}
		high=(high+(TCNT0+152))-256;
		TCCR0=0;
		distance=((high*34600)/(F_CPU*2)) ;
		
		if (distance<=6)
		{
			PORTC |=(1<<6);
			data |=(1<<1);
			_delay_ms(200);
		}
		else
		{
			PORTC &=~(1<<6);
			data &=~(1<<1);
			_delay_ms(200);
		}
		
		
		

		
		PORTA|=(1<<6);
		_delay_us(50);
		PORTA&=(~(1<<6));

		TCCR0=0x01;
	
		high=0;
		

		while ((PINA&(1<<5)) == 0);
		TCNT0=0;
		while ((PINA&(1<<5)) == 32)
		{
			if ((TIFR&(1<<TOV0)) == 1)
			{
				high+=256;
				TIFR|=(1<<0);
			}
		}
		high=(high+(TCNT0+152))-256;
		TCCR0=0;
		distance=((high*34600)/(F_CPU*2)) ;
		
		if (distance<=6)
		{
			PORTA |=(1<<7);
			data |=(1<<2);
			_delay_ms(200);
		}
		else
		{
			PORTA &=~(1<<7);
			data &=~(1<<2);
			_delay_ms(200);
		}
		
		

		PORTA|=(1<<1);
		_delay_us(50);
		PORTA&=(~(1<<1));

		TCCR0=0x01;
	
		high=0;
		

		while ((PINA&(1<<0)) == 0);
		TCNT0=0;
		while ((PINA&(1<<0)) == 1)
		{
			if ((TIFR&(1<<TOV0)) == 1)
			{
				high+=256;
				TIFR|=(1<<0);
			}
		}
		high=(high+(TCNT0+152))-256;
		TCCR0=0;
		distance=((high*34600)/(F_CPU*2)) ;
		
		if (distance<=6)
		{
			PORTA |=(1<<2);
			data |=(1<<3);
			_delay_ms(200);
		}
		else
		{
			PORTA &=~(1<<2);
			data &=~(1<<3);
			_delay_ms(200);
		}
	
		if (old==-1 || old!=data)
		{
			old=data;
	    	MCAL_USART_send_char(data);
		    _delay_ms(1000);
		}
		


    }
	
}

ISR(INT0_vect)
{

	 // Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64
	 TCCR1A = (1<<WGM11)|(1<<COM1A1);
	 TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);

	if (data!=15)
	{
			 TCNT1 = 0;		// Set timer1 count zero
			 ICR1 = 2499;		// Set TOP count for timer1 in ICR1 register
			 
			 OCR1A = 65;	// Set servo shaft at -90° position
			 _delay_ms(1500);
			 
			 while((PIND&(1<<2))==0);
			 _delay_ms(4000);
			 _delay_ms(4000);
			 _delay_ms(4000);
			 OCR1A = 186;	// Set servo shaft at 0° position
			 _delay_ms(1500);
			 
			 TCCR1A =0;
			 TCCR1B =0;

	}
}