#include <REGX52.H>

unsigned char code SMG_duanma[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
     0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
     0xbf,0x7f};


void hc138(unsigned char n)
{
	P2 = (P2 & 0x1f) | (n << 5);
}

void out(unsigned char dat, unsigned char channel)
{
	P0 = dat;
	hc138(channel);
	hc138(0);
}

void InitStstem()
{
	out(0x00,5);
	out(0xff,4);
	
}

void SMG_display(unsigned char channel, unsigned char dat)
{
	out(0x00,6);
	out(dat,7);
}

void main()
{
	while(1)
	{
	}
}