/******************************************************************************
;    Filename:	    usart.c                                           
;                                                                    
;    Author:        M.Sukumar                                          
;    Company:       PANTECH SOLUTIONS                                  
;    Notes:  	    This program will send the string "Hello World" to PC      
;                                                                                                               
;******************************************************************************/

#include<pic.h>
#include<stdio.h>

__CONFIG(0x3f72);

#define FOSC 		10000										//10Mhz==>10000Khz
#define BAUD_RATE	9.6											//9600 Baudrate
#define BAUD_VAL	(char)(FOSC/ (16 * BAUD_RATE )) - 1;		//Calculation For 9600 Baudrate @10Mhz

unsigned char ReceiveChar;

void DelayMs(unsigned int);

void main(void)
{
	DelayMs(50);
	TRISC=0xc0;			//RC7,RC6 set to usart mode(INPUT)
	TXSTA=0x24; 		//Transmit Enable
	SPBRG=BAUD_VAL;		//9600 baud at 10Mhz
	RCSTA=0x90;			//Usart Enable, Continus receive enable
	TXIF=1;		
	DelayMs(100);	
	printf("\033[2J");	//Clear Hypherterminal
	printf("Type A Key:\n\r");	//Clear Hypherterminal
	while(1)
    {
        if(RCIF)
	   	{
            ReceiveChar=RCREG;
            printf("Hello you pressed [%c] and the hex value is %d\n\r",ReceiveChar,ReceiveChar);
	    }
	}
}

void putch(unsigned char byte) 						//This routine is necessary to use printf statement
{													//printf will automatically call putch() to send characters												/* output one byte */
	while(!TXIF);									/* set when register is empty */
	TXREG = byte;
}

void DelayMs(unsigned int Ms)							//Delay Routine
{
		int delay_cnst;
		while(Ms>0)
		{
			Ms--;
			for(delay_cnst = 0;delay_cnst <220;delay_cnst++);	//delay constant for 1Ms @10Mhz
		}
}