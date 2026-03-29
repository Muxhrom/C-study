#include <REGX52.H>
#include <intrins.h>

// 段码
unsigned char code SMG_duanma[18] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x80, 0xc6, 0xc0, 0x86, 0x8e,
  0xbf, 0x7f
};

// 定义变量
unsigned char yu;

//独立按键定义
sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

//灯灯
sbit L1 = P0^0;
sbit L2 = P0^1;
sbit L3 = P0^2;
sbit L4 = P0^3;
sbit L5 = P0^4;
sbit L6 = P0^5;

// 延时函数
void Delay(unsigned int xms) //@12.000MHz
{
  unsigned char data i, j;
  while (xms--) {
    i = 12;
    j = 169;
    do {
      while (--j);
    } while (--i);
  }
}

// hc138
void hc138(unsigned char n)
{
  P2 = (P2 & 0x1F) | 0x00;
  switch (n) {
    case 4: P2 = (P2 & 0x1F) | 0x80; break;
    case 5: P2 = (P2 & 0x1F) | 0xA0; break;
    case 6: P2 = (P2 & 0x1F) | 0xC0; break;
    case 7: P2 = (P2 & 0x1F) | 0xE0; break;
  }
}

//封装输出
void out(unsigned char channel, unsigned char dat)
{
  P0 = dat;
  hc138(channel);
  hc138(0);
}



void main()
{
  while (1) {
    if (S7 == 0){
			Delay(100);
			if (S7 == 0)
			{
				out(4,0xFE);
				while(S7 == 1);
				out(4,0xFF);
			}
		}

    }
  }