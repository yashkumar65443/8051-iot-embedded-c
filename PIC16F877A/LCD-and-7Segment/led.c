/*************************************************************************
;    Filename:	   7segment.c                                            
;    Frequency:	   10Mhz		                                     							      
;    Author:       M.Sukumar                                              
;    Company:      PANTECH SOLUTIONS                                      
;    Notes:		   Program to Demonstrate 4x7Segment Multiplexed Display                                                                  * 
;                  PORTB and Seven Segment Section Should be connected     
;				   Via BUS                                                 
;**************************************************************************/

#include<pic.h>												//Define PIC Registers

__CONFIG(0x3f72);											//Select HS oscillator, Enable (PWRTE,BOREN),
															//Disable (CPD,CP,WDTEN,In-circuit Debugger)

#define CNTRL_PORT PORTA
#define DATA_PORT  PORTD

void hex2dec(unsigned char);
void send_seg(unsigned char,unsigned char,unsigned char,unsigned char);
void DelayMs(unsigned int);

unsigned char x;
unsigned char thou=0,hun=0,ten=0,single=0;
unsigned char CA[10]	=	{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char CC[10]	=	{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char CA_CNTRL[4] 	= 	{0x07,0x0b,0x0d,0x0e};
unsigned char CC_CNTRL[4] 	= 	{0x08,0x04,0x02,0x01};
unsigned char n=1;

void main()
{
	unsigned char number;
	RBPU =0;
	TRISD=0x00;												//PORTB configured as O/P
	ADCON1=0x07;											//Configure PORTA & PORTE as Digital port
	TRISA=0x00;												//PORTA Configured as O/P

	while(1)
	{
		if(x == 200)   
		{
			x=0;
			single++;										//Increment the value upto 9 in unit place
			if(single>9)
			{
				single=0;
				ten++;										//Increment the value upto 9 in Tenth place					
				if(ten>9)
				{
					ten=0;
					hun++;									//Increment the value upto 9 in Hundredth place
					if(hun>9)
					{
						hun=0;
						thou++;								//Increment the value upto 9 in Thousandth place
						if(thou>9)
							thou=0;
					}
				}
			}
		}
		x++;
		send_seg(thou,hun,ten,single);		
	}
}

void send_seg(unsigned char thou,unsigned char hun,unsigned char ten,unsigned char single)
{
	if(n==1)
	{
		CNTRL_PORT=CA_CNTRL[0];											//Eanble Unit place 7-Segment
		DATA_PORT=CA[single];											//Display Unit Place Number
		n=2;
		DelayMs(3);
	}
	else if(n==2)
		 {
			CNTRL_PORT=CA_CNTRL[1];										//Eanble Tenth place 7-Segment
			DATA_PORT=CA[ten];											//Display Tenth Place Number
			n=3;
			DelayMs(3);
		 }
		 else if(n==3)
			  {
		 		CNTRL_PORT=CA_CNTRL[2];									//Eanble Hundredth place 7-Segment
				DATA_PORT=CA[hun];										//Display Hundredth Place Number
				n=4;
				DelayMs(3);
			  }
			 else if(n==4)
			 	  {
					CNTRL_PORT=CA_CNTRL[3];								//Eanble Thousandth place 7-Segment
					DATA_PORT=CA[thou];									//Display Thousandth Place Number
					n=1;
					DelayMs(3);
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