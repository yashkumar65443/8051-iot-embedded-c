#include <pic.h>				//Define PIC Registers

__CONFIG(0x3f72);				//Select HS oscillator, Enable (PWRTE,BOREN), Turn OFF (CPD,CP,WDTEN,In-circuit Debugger).

void DelayMs(unsigned int);

void main()
{
	ADCON1 =  7;				//Select all the PORTA & PORTE as Digital I/O pins
	TRISA  =  0x00;				//PORTA Configured as O/P
	TRISB  =  0x00;				//PORTB Configured as O/P
	TRISC  =  0x00;				//PORTC Configured as O/P
	TRISD  =  0x00;				//PORTD Configured as O/P
	TRISE  =  0x00;				//PORTE Configured as O/P

	while(1)
	{
			PORTA = 0x3f;		//Enable all the LED's connected to PORTA
			PORTB = 0xff;		//Enable all the LED's connected to PORTB
			PORTC = 0xff;		//Enable all the LED's connected to PORTC
			PORTD = 0xff;		//Enable all the LED's connected to PORTD
			PORTE =	0x07;		//Enable all the LED's connected to PORTE
			DelayMs(500);		//Half second Delay
		
			PORTA = 0;			//Turn OFF all the LED's connected to PORTA
			PORTB = 0;			//Turn OFF all the LED's connected to PORTB
			PORTC = 0;			//Turn OFF all the LED's connected to PORTC
			PORTD = 0;			//Turn OFF all the LED's connected to PORTD
			PORTE=	0;			//Turn OFF all the LED's connected to PORTE
			DelayMs(500);		//Half second Delay	
	}
}

void DelayMs(unsigned int Ms)
{
	int delay_cnst;
	while(Ms>0)
	{
		Ms--;
		for(delay_cnst = 0;delay_cnst <220;delay_cnst++);
	}
}