#include <REGX52.H>

unsigned char urdat;
sfr AUXR = 0x8e;

//串口中断初始化
void Init_Uart()
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x8F;			//设置定时初始值
	TH1 = 0xFD;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	
	ES = 1;
	EA = 1;
}

//中断服务函数
void Service_Uart() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		urdat = SBUF;
	
	}
}


void main()
{
	while(1)
	{
	
	}
}