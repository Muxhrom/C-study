#include <REGX52.H>

sbit L1 = P0^0;
sbit S7 = P3^0;

//hc138
void hc138()
{
	P2 = (P2 & 0x1f) | 0x80;
}

//定时器相关
unsigned char count;
void Timer0_Init()		//100微秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x50;				//设置定时初始值
	TH0 = 0xFB;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	ET0 = 1;
	EA = 1;
}

unsigned char pwm_duty = 60;
void Time_Service() interrupt 1
{
	TL0 = 0x50;				//设置定时初始值
	TH0 = 0xFB;				//设置定时初始值
	
	count++;
	if(count == pwm_duty)
	{
		L1 = 1; 	
	}
	else if(count == 100)
	{
		L1 = 0;
		count = 0;
	}
}


//按键相关
void Delay_Key(unsigned int t)
{
	while(t--);
}

unsigned stat = 0;
void Scan_Key()
{
	if(S7 == 0)
	{
		Delay_Key(100);
		if(S7 == 0)
		{
			switch(stat)
			{
				case 0:
					L1 = 0;
					TR0 = 1;
					pwm_duty = 10;
					stat = 1;
				break;
				case 1:
					pwm_duty = 50;
					stat = 2;
				break;
				case 2:
					pwm_duty = 90;
					stat = 3;
				break;
				case 3:
					TR0 = 0;
					L1 = 1;
					stat = 0;
				break;
			}
			while(S7 == 0);
		}
	}
}





void main()
{
	hc138();
	Timer0_Init();
	while(1)
	{
		Scan_Key();
	
	}
}