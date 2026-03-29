#include <REGX52.H>

//初始化定义
sbit S4 = P3^3;
sbit S5 = P3^2;

unsigned char time_m = 0;
unsigned char time_s = 0;
unsigned char time_005ms = 0;


//延时函数
void Delay(unsigned int time)	//@12.000MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	while(time--)
	{
		do
		{
			while (--j);
		} while (--i);
	}
}


//段码表
unsigned char code SMG_duanma[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
     0x80,0x90,0x88,0x80,0xc6,0xc0,0x86,0x8e,
     0xbf,0x7f};
		
//out封装
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

//单数码管显示
void SMG_bit(unsigned char value, unsigned char pos)
{
	out(7, 0xff);
	out(6,0x01 << pos);
	out(7,value);
}

//数码管延时专用
void SMG_delay(unsigned int t)
{
	while(t--);
}

//数码管复杂显示模组
void SMG_show()
{
	SMG_bit(SMG_duanma[time_005ms % 10], 7);
	SMG_delay(500);
	SMG_bit(SMG_duanma[time_005ms / 10], 6);
	SMG_delay(500);
	SMG_bit(SMG_duanma[17], 5);
	SMG_delay(500);
	SMG_bit(SMG_duanma[time_s % 10], 4);
	SMG_delay(500);
	SMG_bit(SMG_duanma[time_s / 10], 3);
	SMG_delay(500);
	SMG_bit(SMG_duanma[17], 2);
	SMG_delay(500);
	SMG_bit(SMG_duanma[time_m % 10], 1);
	SMG_delay(500);
	SMG_bit(SMG_duanma[time_m / 10], 0);
	SMG_delay(500);
}


//定时器中断
void InitTime()
{
	TMOD = 0x01;
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;

	ET0 = 1;
	EA = 1;
	TR0 = 1;
}
	
//定时器服务
void ServiceTime() interrupt 1
{
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	time_005ms++;
	if(time_005ms == 20)
	{
		time_s++;
		time_005ms = 0;
	}
	if(time_s == 60)
	{
		time_m++;
		time_s = 0;
	}
	if(time_m == 99)
	{
		time_m = 0;
	}
}

//按键扫描延时
void Key_delay(unsigned int t)
{
	while(t--);
}


//按键扫描
void Key()
{
	if(S4 == 0) //暂停，启动
	{
		Key_delay(100);
		if(S4 == 0)
		{
			TR0 = ~TR0;
			while(S4 == 0)
			{
				SMG_show();
			}
		}
	}

	if(S5 == 0) //秒表清零
	{
		Key_delay(100);
		if(S5 == 0)
		{
			time_m = 0;
			time_s = 0;
			time_005ms = 0;
			while(S5 == 0)
			{
				SMG_show();
			}
		}
	}
}


void main()
{
	InitTime();
	while(1)
	{
	SMG_show();
		Key();
	}
}