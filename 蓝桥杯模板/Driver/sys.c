#include "sys.h"

void Sys_Init ()
{
	P0 = 0xff; Y4; Y0;
	P0 = 0xaf; Y5; Y0;
	P0 = 0x00; Y6; Y0;
	P0 = 0xff; Y7; Y0;
}

//	@12.000MHz, 12T
//	@Timer0 -> System,	1ms
void Timer0_Init (void)
{
	AUXR &= 0x7F;
	TMOD &= 0xF0;
	
	TL0 = 0x18;
	TH0 = 0xFC;
	
	TF0 = 0;
	TR0 = 1;
	
	ET0 = EA = 1;
}

//	@12.000MHz, 12T
//	@Timer0 -> NE555,	count
//	@Timer1 -> System,	1ms
void Timer01_Init (void)
{
	AUXR &= 0x3F;
	TMOD = 0x04;
	
	TL0 = 0xFF;
	TH0 = 0xFF;
	
	TL1 = 0x18;
	TH1 = 0xFC;
	
	TF0 = TF1 = 0;
	TR0 = TR1 = 1;
	
	ET0 = ET1 = EA = 1;
}

//	@12.000MHz, 12T
//	@Timer2 -> PWM,	100us
void Timer2_Init(void)
{
	AUXR &= 0xFB;
	
	T2L = 0x9C;
	T2H = 0xFF;
	
	AUXR |= 0x10;		//TR2
	
	IE2 |= (0x01 << 2);	//ET2
	
	EA = 1;
}
