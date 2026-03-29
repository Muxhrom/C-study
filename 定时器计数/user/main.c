#include <seg.h>
#include <key.h>
#include <ds1302.h>
#include <REGX52.H>


//变量定义
unsigned char key_val, key_old, key_down; //按键判断消抖
unsigned char seg_wait, key_wait, led_wait; //数码管和按键稍微延迟，按键10ms，seg500ms
unsigned char seg_pos = 0; //数码管扫描
unsigned char seg_buf[6] = {1,1,1,1,1,1};//数码管内容

//按键进程
void Key_Proc()
{
	if(key_wait) return;
	key_wait = 1;
	
	key_val = Key_Read();
	key_down = key_val & (key_old ^ key_val);
	key_old = key_val;
	
	switch(key_down)
	{
	
	}
}

//数码管显示进程
void Seg_Proc()
{
	if(seg_wait) return;
	seg_wait = 1;
}

//其他显示
void Led_Proc()
{
	if(led_wait) return;
	led_wait = 1;
}

//定时器初始化
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD = 0x11;			//设置模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;
	EA = 1;
}

void Timer0_Service() interrupt 1
{
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	
	if(++key_wait == 10) key_wait = 0;
	if(++seg_wait == 500) seg_wait = 0;
	if(++led_wait == 500) led_wait = 0;
	
	if(++seg_pos == 6) seg_pos = 0;
	Seg_Bit(seg_pos,seg_buf[seg_pos]);
		
}



//主函数
void main()
{
	out(4, 0xff); // 通道4：LED全灭
  out(5, 0x00); // 通道5：蜂鸣器、继电器全关
	Timer0_Init();
	while(1)
	{
		Key_Proc();
		Led_Proc();
		Seg_Proc();
	}
}