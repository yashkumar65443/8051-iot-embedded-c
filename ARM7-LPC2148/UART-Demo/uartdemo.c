#include<lpc214x.h>
#include<stdint.h>

void UART0_init(void);
void UART0_Txchar(char ch);
unsigned char UART0_Rxchar(void);
void UART0_SendString(char* str);

void delay_ms(uint16_t j)
{
	uint16_t x,i;
	for (i=0;i<j;i++)
	{
		for(x=0;x<6000;x++);//1 millisecond 60 mhz
	}
}

void UART0_init(void)
{
	PINSEL0=0x00000005;
	U0LCR  =0x00000083; 
  U0DLL=	0x000000C3;
	U0LCR  =0x00000003; 

}

void UART0_Txchar(char ch)
{
	U0THR=ch;
	while(!(U0LSR&0x20));
}
unsigned char UART0_Rxchar(void)
{
		while(!(U0LSR&0x01));
	return U0RBR;

	
}

void UART0_SendString(char* str)
{
	uint8_t i=0;
	while(str[i]!='\0')
	{
		UART0_Txchar(str[i]);
		i++;
	}
	
}



int main(void)
{
	char receive;
	VPBDIV=0x02;
	UART0_init();
	while(1)
		
	{
		//receive=UART0_Rxchar();
		//UART0_Txchar(receive);
		UART0_SendString("HELLO WORLD\r\n");
	}
	
	
}