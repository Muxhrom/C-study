#include <REGX52.H>
#include <key.h>
#include <smg.h>

//变量定义
unsigned int smg_flag, key_flag, led_flag;  //按键减速,500 10 500
unsigned char key_val, key_old, key_down;  //按键判断
unsigned char smg_pos = 0; //选smg位置，动态扫描
unsigned char smg_buf[8] = {0,1,2,3,4,5,6,7}; //smg的整体数值


//按键处理
void Key_Proc()
{
	if(key_flag) return;
	key_flag = 1;
	
	key_val = Key_Read();
	key_down = key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
	
	}
}


//数据处理
void SMG_Proc()
{
	if(smg_flag) return;
	smg_flag = 1;
}

//led及其他数据处理
void Led_Proc()
{
	if(led_flag) return;
	led_flag = 1;
}	

//定时器初始化
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD = 0x01;			//设置定时器模式
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

//定时器服务函数
void Timer0_Server() interrupt 1
{
	TL0 = 0x18;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值

	if(++smg_flag >= 500)
		smg_flag = 0;
	if(++led_flag >= 500)
		led_flag = 0;
	if(++key_flag >= 10)
		key_flag = 0;
	
	if(++smg_pos == 8)
		smg_pos = 0;
	SMG_Display(smg_pos, smg_buf[smg_pos]);
}

//主函数
void main()
{
	Timer0_Init();
	while(1)
	{
		SMG_Proc();
		Led_Proc();
		Key_Proc();
	}
}