#include <REGX52.H>
#include <key.h>

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

unsigned char Key_Read()
{
	unsigned char temp = 0;
	if(S7 == 0)
		temp = 1;
	if(S6 == 0)
		temp = 2;
	if(S5 == 0)
		temp = 3;
	if(S4 == 0)
		temp = 4;
	return temp;
	
}