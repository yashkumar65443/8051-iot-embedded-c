#include<reg51.h>
#define sw P0
#define led  P2

void main()
{
	P0=0xff ; 
	P2=0x00;
	while(1)
	{
		led=sw;
	}
}


