#include "main.h"

//=====================================================
unsigned char _Slow = 0;
bit Data_Flag, Key_Flag, Seg_Flag, Led_Flag;

unsigned char Key_Val, Key_Down, Key_Up, Key_Old;

idata unsigned char Seg_Buf[8] = {16,16,16,16, 16,16,16,16};
idata unsigned char Seg_Dot[8] = {0,0,0,0, 0,0,0,0};

idata unsigned char ucLed[8] = {0,0,0,0, 0,0,0,0};

unsigned char motor = 0;

//=====================================================
unsigned char Clock_Mode = 0;
unsigned char Clock[7] = {0x25, 0x04, 0x05, 0x08, 0x23, 0x59, 0x53};

float t;

unsigned int R_L, R_x;
unsigned char EEP_dat[2] = {30, 80};

unsigned int count_NE555 = 0, count_1s = 0, freq;

idata unsigned char Uart_Send_arr[20];
idata unsigned char Uart_Recv_arr[20];
idata unsigned char Uart_Recv_index = 0;
idata unsigned char Uart_Send_times = 0;

unsigned int Ultra_dat;

unsigned char count_PWM = 0, PWM_Set = 80;

//=====================================================


//=====================================================

void Data_Proc ()
{
	if (Data_Flag) return;
	Data_Flag = 1;
	//
	
}

void Key_Proc ()
{
	if (Key_Flag) return;
	Key_Flag = 1;
	//
	Key_Val = Key_Scan();
	Key_Down = Key_Val & (Key_Old ^ Key_Val);
	Key_Up = ~ Key_Val & (Key_Old ^ Key_Val);
	Key_Old = Key_Val;
	//
	
}

void Seg_Proc ()
{
	if (Seg_Flag) return;
	Seg_Flag = 1;
	//
	
}

void Led_Proc ()
{
	if (Led_Flag) return;
	Led_Flag = 1;
	//
	
}

//	@Counter0 Interrupt Serv for NE555.
/*
void Counter0_Serv () interrupt 1
{
	count_NE555 ++;
}
*/

//	@Timer0/Timer1 Interrupt Serv for Basic System.
//	@When Counter0 is used, Timer0 -> Timer1, interrupt 1 -> interrupt 3.
void Timer0_Serv () interrupt 1
{
	_Slow ++;
	if (_Slow % 10 == 0) Data_Flag = Key_Flag = 0;
	if (_Slow % 40 == 0) Seg_Flag = Led_Flag = 0;
	_Slow %= 200;
	//
	Seg_Disp (_Slow%8, Seg_Buf[_Slow%8], Seg_Dot[_Slow%8]);
	Led_Disp (_Slow%8, ucLed[_Slow%8]);
	//
	
}

//	@Timer2 Interrupt Serv for PWM (Led/Seg/Motor).
/*
void Timer2_Serv () interrupt 12
{
	count_PWM ++;
	if (count_PWM <= PWM_Set) {
		//enable
	} else {
		//disable
	}
	count_PWM %= 100;
}
*/

void main ()
{
	Sys_Init ();
	Timer0_Init ();
	//
	
	
    while (1) {
		Data_Proc ();
		Key_Proc ();
		Seg_Proc ();
		Led_Proc ();
		
    }
}