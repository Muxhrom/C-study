//头文件声明
#include <STC15F2K60S2.H>
#include "Key.h"
#include "Seg.h"



//变量声明
unsigned char Key_Slow_Down;//按键减速10ms
unsigned int Seg_Slow_Down;//数码管减速变量
unsigned char Key_Val,Key_Down,Key_Old;
unsigned char Seg_Buf[6] = {1,2,3,4,5,6};//数码管显示数据存放数组

// 按键处理



//mian
void main(){
	if (Key_Slow_Down) return;
	Key_Slow_Down = 1;//按键减速
	
	Key_Val = Key_Read();
	Key_Down = Key_Val&(Key_Val^Key_Old);
	Key_Old = Key_Val;
	
	switch(Key_Down)
	{
	
	}
}

//信息处理函数
void Seg_Proc()
{
	if (Seg_Slow_Down) return;
	Key_Slow_Down = 1;//数码管减速

}

//其他显示函数
void Led_Proc()
{

}

//定时器0初始化函数
void Timer0_Init(void)		//100微秒@11.0592MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xAE;				//设置定时初始值
	TH0 = 0xFB;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//自己加的两行，不知道意义
	EA = 1;
}

//定时器0中断服务函数
void Timer0Server() interrupt 1 
{
	TL0 = 0xAE;				//设置定时初始值
	TH0 = 0xFB;				//设置定时初始值
	if(++Key_Slow_Down == 10) Key_Slow_Down = 0;
	if(++Seg_Slow_Down == 500) Seg_Slow_Down = 0;
	if(++Seg_Pos==6) Seg_Pos = 0;
	Seg_Disp(Seg_Pos,Seg_Buf[Seg_Pos]);
}

//main
void main(){
	Timer0Init();
	while(1)
	{
		Ket_Proc();
		Seg_Proc();
		Led_Proc();
	}

}