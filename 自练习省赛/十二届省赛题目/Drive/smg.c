#include <REGX52.H>
#include <smg.h>

unsigned char code _Wei[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};      //????
unsigned char code _Duan[] = {
    // 0~9 ???
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 
    // A~F ???
    0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 
    // ?? 16??? (Black)
    0xFF, 
    // ?? 17??? (-)
    0xBF  
};

void hc138(unsigned char n)
{
	P2 = (P2 & 0x1f) | (n << 5);
}
void out(unsigned char channel, unsigned char dat)
{
	P0 = dat;
	hc138(channel);
	hc138(0);
}

void SMG_Display(unsigned char wei, unsigned char duan, unsigned char point)
{
	unsigned char seg_code;
	out(7,0xff);
	out(6,_Wei[wei]);
	seg_code = _Duan[duan];
	
	if(point == 1)
		seg_code &= 0x7F;
	out(7,seg_code);
}