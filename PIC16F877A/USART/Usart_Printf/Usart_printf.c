
/**********************************************************************
;    Filename:	    usart.c                                             *
;    Date:          03/06/06                                          *
;    File Version:  1.0                                               *
;                                                                     *
;    Author:       M.Sukumar                                          *
;    Company:      PANTECH SOLUTIONS                                  *
;    Notes:  			 This program will send the characters received from      *
;    							 PC back to PC                                                    *
;                                                                     *
;                                                                     *
;**********************************************************************/
#include<pic.h>
#include<stdio.h>

__CONFIG(0x3f72);

unsigned char ReceiveChar;
void putch(unsigned char);

void main()
	{
	
	TRISC=0xc0;	
	TXSTA=0x24; 
	SPBRG=25;
	RCSTA=0x90;
	TXIF=1;

	while(1)
	{
         if(RCIF)
	    {
            ReceiveChar=RCREG;
            printf("Hello you pressed [%c] and the hex value is %d",ReceiveChar,ReceiveChar);
	    }
	}

void putch(unsigned char byte) 
{
				/* output one byte */
	while(!TXIF);		/* set when register is empty */
	TXREG = byte;
}
