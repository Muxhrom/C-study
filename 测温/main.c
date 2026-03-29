//头文件声明
#include <REGX52.H>
#include <key.h>
#include <seg.h>
#include <ds1302.h>
#include <onewire.h>

//变量声明区
unsigned char key_slow; //按键减速变量 10ms
unsigned int seg_slow; //显示减速变量 500ms
unsigned char key_val, key_old, key_down, key_up;
unsigned char seg_pos = 0;//数码管扫描变量
unsigned char seg_buf[8] = {16, 16, 16, 16, 16, 16, 16, 16};//数码管测试
unsigned char seg_mode = 0; //显示模式 0显示 1设置
unsigned int time_1000ms;//1000ms计时
unsigned char time_count = 30; //系统计时变量
bit system_flag; //系统标志位，0暂停1开始
unsigned char set_dat[] = {15,30,60}; //三种档位
unsigned char set_index = 1;
unsigned char uctime[3] = {0x23, 0x59, 0x55}; //ds1302，默认时间23:59:55
float tem; //温度

//按键处理函数
void Key_Proc()
{
	if(key_slow) return;
	key_slow = 1; //按键减速
	
	key_val = Key_Read();
	key_down = key_val & (key_val ^ key_old);
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 1: //启动倒计时
			if(seg_mode == 0)
			{
				system_flag = 1;
			}
			break;
		case 2://复位
			if(seg_mode == 0)
				time_count = set_dat[set_index];
		break;
		case 3://切换模式
			if(seg_mode == 1)
				time_count = set_dat[set_index];
			seg_mode = !seg_mode;
			break;
		case 4:
			if(seg_mode == 1)
			{
				set_index = set_index + 1;
				if(set_index == 3)
					set_index = 0;
			}
		break;
	}
}


//信息处理函数
void Seg_Proc()
{
	if(seg_slow) return;
	seg_slow = 1; //按键减速
	
	//信息读取
	Read_Time(uctime);
	
	//数据处理
	seg_buf[0] = uctime[0] / 16;
	seg_buf[1] = uctime[0] % 16;
	seg_buf[2] = 17;
	seg_buf[3] = uctime[1] / 16;
	seg_buf[4] = uctime[1] % 16;
	seg_buf[5] = 17;
	seg_buf[6] = uctime[2] / 16;
	seg_buf[7] = uctime[2] % 16;
	
	tem = Read_Tem();
	
	seg_buf[0] = (unsigned char)tem / 10 % 10;
	seg_buf[1] = (unsigned char)tem % 10;
	seg_buf[2] = (unsigned int)(tem*10) % 10;
}

//其他信息显示
void Led_Proc()
{

}

//定时器0初始化
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;
	TH0 = 0xFC; 
	TL0 = 0x18;
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	ET0 = 1;
	EA = 1;
}


//定时器0中断服务函数
void Timer0_Service() interrupt 1
{
	TH0 = 0xFC; 
	TL0 = 0x18;
		
	if(++key_slow == 10) key_slow = 0;
	if(++seg_slow == 500) seg_slow = 0;
	if(++seg_pos == 8) seg_pos = 0;
	Seg_Bit(seg_pos,seg_buf[seg_pos]);
	if(system_flag == 1)
		{
			if(++time_1000ms == 1000)
			{
				time_1000ms =0;
				time_count--;
			}
		}
}




//主函数
void main()
{
	Timer0_Init();
	Set_Time(uctime);
	while(1)
	{
		Key_Proc();
		Seg_Proc();
		Led_Proc();
		
	}
}