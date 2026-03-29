#include "led.h"

static unsigned char temp_Y5 = 0x00;
static unsigned char temp_Y5_old = 0xff;

void Led_Disp (unsigned char addr, enable)
{
	static unsigned char temp_Y4 = 0x00;
	static unsigned char temp_Y4_old = 0xff;
	
	if (enable)
		temp_Y4 |= (0x01 << addr);
	else
		temp_Y4 &= ~ (0x01 << addr);
	
	if (temp_Y4 != temp_Y4_old) {
		P0 = ~temp_Y4;
		Y4; Y0;
		temp_Y4_old = temp_Y4;
	}
}

void Buzz (unsigned char enable)
{
	if (enable)
		temp_Y5 |= 0x40;
	else
		temp_Y5 &= ~ 0x40;
	
	if (temp_Y5 != temp_Y5_old) {
		P0 = temp_Y5;
		Y5; Y0;
		temp_Y5_old = temp_Y5;
	}
}

void Relay (unsigned char enable)
{
	if (enable)
		temp_Y5 |= 0x10;
	else
		temp_Y5 &= ~ 0x10;
	
	if (temp_Y5 != temp_Y5_old) {
		P0 = temp_Y5;
		Y5; Y0;
		temp_Y5_old = temp_Y5;
	}
}

void Motor (unsigned char enable)
{
	if (enable)
		temp_Y5 |= 0x20;
	else
		temp_Y5 &= ~ 0x20;
	
	if (temp_Y5 != temp_Y5_old) {
		P0 = temp_Y5;
		Y5; Y0;
		temp_Y5_old = temp_Y5;
	}
}