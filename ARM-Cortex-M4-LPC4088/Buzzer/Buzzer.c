#include "LPC407x_8X_177X_8x.h"

void delay_ms(long ms);
	
int main(void)
{	
	//1. Set the PCGPIO bit
	LPC_SC->PCONP |= (1<<15);
	LPC_IOCON->P0_26 = 0;
	LPC_GPIO0->DIR= 0x4000000;	
		
	while(1)
		{
			//4. Send a High
			LPC_GPIO0->PIN= 0x4000000;
			//5.Pause the system for few milliseconds
			delay_ms(500);
			//6.Send a low
			LPC_GPIO0->PIN= 0x0000000;
			//7.Pause the system for few milliseconds
			delay_ms(500);
		}
}


void delay_ms(long ms) 					// delay 1 ms per count @ CCLK 120 MHz
{
		long i,j;
		for (i = 0; i < ms; i++ )
		for (j = 0; j < 26659; j++ );
}
