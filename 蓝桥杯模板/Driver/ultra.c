#include "ultra.h"

sbit Tx = P1^0;
sbit Rx = P1^1;

void Delay12us ()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 38;		//[*] 33 -> 38
	while (--i);
}

void Ultra_Init ()
{
	unsigned char i;
	
//	EA = 0;
	
	for (i = 0; i < 8; i ++) {
		Tx = 1;
		Delay12us ();
		Tx = 0;
		Delay12us ();
	}
	
//	EA = 1;
}

unsigned char Ultra_Read ()
{
	unsigned int time;
	
	CMOD = 0x00;
	CL = CH = 0;
	
	Ultra_Init ();
	
	CR = 1;
	while (Rx == 1 && CF == 0) ;
	CR = 0;
	
	if (CF) {
		CF = 0;
		return 0;
	} else {
		time = (CH << 8) | CL;
		return (time * 0.017);
	}
}