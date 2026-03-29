// 头文件
#include <REGX52.H>
#include <intrins.h>

//延时部分
void Delay(unsigned char xms)	//@12.000MHz
{
	unsigned char data i, j;
	while(xms--)
	{
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
	}
}
//声明变量
unsigned char ucLed=0xfe;

// main
void main(){
	while (1)
	{
		ucLed = _crol_(ucLed,1);
		P1 = ucLed;
		Delay(100);
	}
}