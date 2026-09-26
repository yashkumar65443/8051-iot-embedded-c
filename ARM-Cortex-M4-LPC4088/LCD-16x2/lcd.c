#include "LPC407x_8x_177x_8x.h"
#define RS_PORT 0
#define RS_PIN 4
#define RS_VAL (1<<RS_PIN)
#define EN_PORT 0
#define EN_PIN 5
#define EN_VAL (1<<EN_PIN)
#define DATA LPC_GPIO4->PIN

unsigned char Lcd_Line1[]={"CORTEX DEV BOARD"};
unsigned char Lcd_Line2[]={"LCD DEMO PROGRAM"};
unsigned char i=0;
void delay_ms(long ms);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);

void delay_ms(long ms)// delay for 1 ms @cclk 120 mhz
{
	long i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<26659;j++);
}

void lcd_init(void)
	{
		delay_ms(100);
		lcd_command(0x33);
		lcd_command(0x32);
		lcd_command(0x28);
		lcd_command(0x0C);
		lcd_command(0x06);
		lcd_command(0x01);
		delay_ms(200);

	}
void lcd_command(unsigned char cmd)
{
	LPC_GPIO0->CLR |=RS_VAL;//CLEAR THE RSPIN
	DATA=cmd<<24; //msb 4 bits
	LPC_GPIO0->PIN |=EN_VAL;
	LPC_GPIO0->CLR |=EN_VAL;
	DATA=cmd<<28; //Lsb 4 bits
	LPC_GPIO0->PIN |=EN_VAL;
	LPC_GPIO0->CLR |=EN_VAL;
	delay_ms(5);
}

void lcd_data(unsigned char data)
{
	LPC_GPIO0->PIN |=RS_VAL;//CLEAR THE RSPIN
	DATA=data<<24; //msb 4 bits
	LPC_GPIO0->PIN |=EN_VAL;
	LPC_GPIO0->CLR |=EN_VAL;
	DATA=data<<28; //Lsb 4 bits
	LPC_GPIO0->PIN |=EN_VAL;
	LPC_GPIO0->CLR |=EN_VAL;
	delay_ms(5);
}

int main(void)
{
	LPC_SC->PCONP1 |=(1<<15);//POWE R CONTROL
	
	LPC_IOCON->P0_4=0;
	LPC_IOCON->P0_5=0;
	LPC_IOCON->P4_28=0;
	LPC_IOCON->P4_29=0;
	LPC_IOCON->P4_30=0;
	LPC_IOCON->P4_31=0;
	
	LPC_GPIO0->DIR|=0X30;
	LPC_GPIO4->DIR =(0XF<<28);
	lcd_init();
	while(1)
	{
		lcd_command(0x80);
		for(i=0;Lcd_Line1[i]!='\0';i++)
		{
			lcd_data(Lcd_Line1[i]);
			delay_ms(50);
		}
		
		lcd_command(0xc0);
		for(i=0;Lcd_Line2[i]!='\0';i++)
		{
			lcd_data(Lcd_Line2[i]);
			delay_ms(50);
		}
					delay_ms(1000);
		lcd_command(0x01);

	}


	
	
}
