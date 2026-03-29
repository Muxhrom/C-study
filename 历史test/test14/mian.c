#include <REGX52.H>

sbit L1 = P0^0;
sbit L8 = P0^7;

void hc138(unsigned char n)
{
	P2 = (P2 & 0x1f) | (n << 5);
}

//初始化中断
void InitTime()
{
	TMOD = 01;
	TH0 = (65535 - 50000) / 256;
	TL1 = (65535 - 50000) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

//中断业务函数
unsigned int count = 0;
unsigned int count1 = 0;
void sertime() interrupt 1
{
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	count ++;
	count1 ++;
	if (count == 10)
	{
		L1 = ~L1;
		count = 0;
	}
	if (count1 == 50)
	{
		L8 = ~L8;
		count1 = 0;
	}
	


}



void main()
{
	hc138(4);
	InitTime();
	while(1)
	{
		
	
	}

}