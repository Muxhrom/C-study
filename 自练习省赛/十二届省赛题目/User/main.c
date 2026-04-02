#include <REGX52.H>
#include <key.h>
#include <smg.h>
#include <onewire.h>

//变量定义
unsigned int smg_flag, key_flag, led_flag;  //按键减速,1000 10 500
unsigned char key_val, key_old, key_down;  //按键判断
unsigned char smg_pos = 0; //选smg位置，动态扫描
unsigned char smg_buf[8] = {16,16,16,16,16,16,16,16}; //smg的整体数值
unsigned char smg_mode; //0温度 1设置 2dac输出
float tem; //实时温度
unsigned char smg_point[8] = {0,0,0,0,0,0,0,0};
unsigned char temp_ctrl, temp_disp; //一个控制值，一个显示值
unsigned char smg_display_mode; // 切换显示模式

//延时函数
void Delay(unsigned int time_delay)	//@12.000MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	while (time_delay--)
	{
		do
		{
			while (--j);
		} while (--i);
	}
}


//按键处理
void Key_Proc()
{
	if(key_flag) return;
	key_flag = 1;
	
	key_val = Key_Read(0);
	key_down = key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 4:
			if(++smg_display_mode == 3) smg_display_mode = 0;
			if(smg_display_mode == 1) temp_disp = temp_ctrl;
			if(smg_display_mode == 2) temp_ctrl = temp_disp;
			break;
	}
}


//数据处理
void SMG_Proc()
{
	if(smg_flag) return;
	smg_flag = 1;
	
	//数据获取
	tem = Read_Tem();
	
	
	//数据显示
	switch(smg_mode)
	{
		case 0://温度显示
			smg_buf[0] = 13;
			smg_buf[4] = (unsigned char)tem / 10 % 10;
			smg_buf[5] = (unsigned char)tem % 10;
			smg_buf[6] = (unsigned int)(tem * 100) / 10%10;
			smg_buf[7] = (unsigned int)(tem * 100) %10;
			smg_point[5] = 1;
		break;
		
		case 1://参数设置
			smg_buf[0] = 14; //本来应该是P，但是段码表我没改所以暂时用D代替
			smg_buf[4] = 16;
			smg_buf[5] = 16;
			smg_buf[6] = temp_disp / 10 % 10;
			smg_buf[7] = temp_disp % 10;

	}
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

	if(++smg_flag >= 1000)
		smg_flag = 0;
	if(++led_flag >= 500)
		led_flag = 0;
	if(++key_flag >= 10)
		key_flag = 0;
	
	if(++smg_pos == 8)
		smg_pos = 0;
	SMG_Display(smg_pos, smg_buf[smg_pos],smg_point[smg_pos]);
}

//主函数
void main()
{
	Read_Tem();
	Delay(750);
	Timer0_Init();
	while(1)
	{
		SMG_Proc();
		Led_Proc();
		Key_Proc();
	}
}