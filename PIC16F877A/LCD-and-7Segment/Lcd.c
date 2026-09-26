
#include<pic.h>						//Define PIC Registers
#include<stdio.h>					//Define I/O Functions

__CONFIG(0x3f72);					//Select HS oscillator, Enable (PWRTE,BOREN), 
									//Disable (CPD,CP,WDTEN,In-circuit Debugger)

#define RS RE0						//LCD Register Select
#define RW RE1						//LCD Read/Write Pin
#define EN RE2						//LCD Enable Pin
#define DATA 		PORTD			//LCD Data Port
#define DATADIR		TRISD			//LCD Data Port Direction Register
#define CNTRLDIR 	TRISE			//RS,RW,EN Direction Register

void lcdinit(void);					//LCD initialization Function
void lcdclr(void);					//LCD Clear Function			
void lcdcomd(unsigned char);		//LCD Command Declaring Fucntion
void lcddata(unsigned char);		//LCD Data Display Fucntion
void DelayMs(unsigned int);


void main()
{
		int i;
		unsigned char First[]={" PIC DEV. BOARD "};
		unsigned char Secnd[]={"LCD DEMO PROGRAM"};
		DelayMs(500);
		lcdinit();			
		DelayMs(500);

		while(1)
		{
			lcdclr();
			lcdcomd(0x80);
			for(i=0;i<16;i++)			//Display the Message
			{
				lcddata(First[i]);
				DelayMs(50);
			}

			lcdcomd(0xc0);
			for(i=0;i<16;i++)			//Display the Message
			{
				lcddata(Secnd[i]);
				DelayMs(50);
			}
			DelayMs(500);
		}
}


void lcdinit(void)
{	
	int i;
	unsigned char command[]={0x38,0x0c,0x06,0x01};					//LCD Command set for 8 bit Interface, 2 Lines, 5x7 Dots
	ADCON1 = 0x07;													//Make PORTE Pin as Digital
	CNTRLDIR = 0x00;												//Make LCD control port (PORTE) as output Port
	DATADIR  = 0x00;	
    DelayMs(50);											//Make LCD Data Port (PORTD) as output port
	for(i=0;i<4;i++)
	{
		lcdcomd(command[i]);										//Send the Initialisation Commands
		DelayMs(5);
	}
	DelayMs(500);
}

void lcdclr(void)													//Send LCD clear command
{
	lcdcomd(0x01);				
	DelayMs(2);
}                   
		
void lcdcomd(unsigned char cmd)
{	
	RS=0;	RW=0;													//Select Command Register, R/W--write enabled
	EN=1;															//Enable LCD to accept commands
	DATA=cmd;										
	EN=0;		
	DelayMs(5);														//Give a Pulse via Enable pin 
}

void lcddata(unsigned char byte) 
{				
	RS=1;	RW=0;													//Select Data register, R/W--write enabled
	EN=1;
	DATA=byte;										//Give a Pulse via Enable pin 
	EN=0;
	DelayMs(5);	
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