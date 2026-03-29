#include "Uart.h"

//	@12.000MHz, 12T
//	@Timer2 -> 9600bps
void Uart_Init (void)
{
	SCON = 0x50;
	AUXR |= 0x01;
	AUXR &= 0xFB;
	
	T2L = 0xE6;
	T2H = 0xFF;
	
	AUXR |= 0x10;
	
	ES = 1;
}

void Uart_Send_Byte (unsigned char ch)
{
	SBUF = ch;
	while (TI == 0) ;
	TI = 0;
}

void Uart_Send_String (unsigned char* str)
{
	while (* str != '\0') {
		Uart_Send_Byte (* str ++);
	}
}