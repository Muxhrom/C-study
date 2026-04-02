#include <REGX52.H>
#include <key.h>

sbit R7 = P3^0;
sbit R6 = P3^1;
sbit R5 = P3^2;
sbit R4 = P3^3;

unsigned char Key_Read(unsigned char key_mode)
{
	unsigned char temp = 0;

	if(key_mode == 0) //独立按键
	{
		if(R7 == 0) temp = 7;
		if(R6 == 0) temp = 6;
		if(R5 == 0) temp = 5;
		if(R4 == 0) temp = 4;
	}

	if(key_mode == 1)//矩阵按键
	{
		P3 = 0xEF;
		if(R7 == 0) temp = 7;
		if(R6 == 0) temp = 6;
		if(R5 == 0) temp = 5;
		if(R4 == 0) temp = 4;

		P3 = 0xDF;
		if(R7 == 0) temp = 11;
		if(R6 == 0) temp = 10;
		if(R5 == 0) temp = 9;
		if(R4 == 0) temp = 8;

		P3 = 0xBF;
		if(R7 == 0) temp = 15;
		if(R6 == 0) temp = 14;
		if(R5 == 0) temp = 13;
		if(R4 == 0) temp = 12;

		P3 = 0x7F;
		if(R7 == 0) temp = 19;
		if(R6 == 0) temp = 18;
		if(R5 == 0) temp = 17;
		if(R4 == 0) temp = 16;

		P3 = 0xFF;
	}
	return temp;
}