#include <REGX52.H>
#include <intrins.h>

//段码
unsigned char code SMG_duanma[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
     0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
     0xbf,0x7f};
		
//延时函数
void Delay(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;
	while(xms--)
		{
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}
}
		 
		 

//hc138函数
void hc138(unsigned char n)
{
	P2 = (P2 & 0x1F) | 0x00;
	switch (n)
	{
		case 4: P2 = (P2 & 0x1F) | 0x80; break;
		case 5: P2 = (P2 & 0x1F) | 0xA0; break;
		case 6: P2 = (P2 & 0x1F) | 0xC0; break;
		case 7: P2 = (P2 & 0x1F) | 0xE0; break;
	}
}

//封装
void Out(unsigned char channel, unsigned char dat)
{
	P0 = dat;
	hc138(channel);
	hc138(0);
}

//数码管显示单元
void ShowSMG_Bit(unsigned char pos, unsigned char dat)
{
	Out(6,0x01 << pos);
	
	Out(7,dat);
}

//数码管整体显示
void ShowSMG()
{
	unsigned char i,j;
	//分批显示
	for (i=0; i<8; i++)
	{
		for (j=0; j<10; j++)
		{
			ShowSMG_Bit(i,SMG_duanma[j]);
			Delay(100);
		}
	}	
	
	//统共显示
	for (i=0; i<16; i++)
	{
		Out(6,0xff);
		Out(7,SMG_duanma[i]);
		Delay(1000);
		
	}
	
	

}


void main(){
	while (1)
	{
		ShowSMG();
	}


}
