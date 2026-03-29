#include <STC15F2K60S2.H>
#include <intrins.h>

// 声明变量
unsigned char ucLed = 0xfe;
unsigned char Key_Val, Key_Down, Key_Up, Key_Old;
bit System_Flag;
unsigned int Time = 100;

// 延时函数：毫秒级延时 (@12.000MHz)
void Delay(unsigned char xms)    
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

// 按键读取函数：获取当前物理引脚状态
// 按键读取函数：获取当前物理引脚状态
unsigned char Key_Read()
{
  unsigned char temp = 0;
  
  P30 = 0; P31 = 1; P32 = 1; P33 = 1;
  if (P34 == 0) temp = 1;
  if (P35 == 0) temp = 2;
  if (P42 == 0) temp = 3;
  if (P44 == 0) temp = 4;
  
  P30 = 1; P31 = 0; P32 = 1; P33 = 1;
  if (P34 == 0) temp = 5;
  if (P35 == 0) temp = 6;
  if (P42 == 0) temp = 7;
  if (P44 == 0) temp = 8;
  
  P30 = 1; P31 = 1; P32 = 0; P33 = 1;
  if (P34 == 0) temp = 9;
  if (P35 == 0) temp = 10;
  if (P42 == 0) temp = 11;
  if (P44 == 0) temp = 12;
  
  P30 = 1; P31 = 1; P32 = 1; P33 = 0;
  if (P34 == 0) temp = 13;
  if (P35 == 0) temp = 14;
  if (P42 == 0) temp = 15;
  if (P44 == 0) temp = 16;
  
  return temp;
}

// 主函数
void main()
{
  while (1)
  {
    // 1. 软件消抖核心：强制单片机每 10ms 扫描一次按键，避开高频机械抖动
    Delay(10); 
    
    // 2. 状态机运算逻辑
    Key_Val = Key_Read();                     // 采样当前状态
    Key_Down = Key_Val & (Key_Val ^ Key_Old); // 提取下降沿（刚按下瞬间）
    Key_Up = ~Key_Val & (Key_Val ^ Key_Old);  // 提取上升沿（刚松开瞬间）
    Key_Old = Key_Val;                        // 更新历史状态，为下一次扫描做准备
    
    // 3. 业务执行
		if(System_Flag == 1)
			{
		ucLed = _crol_(ucLed,1);
		P1 = ucLed;
		Delay(Time);
			}

		switch (Key_Down)
		{
			case 1:               
				System_Flag = 1;    
				break;              

			case 2:               
				System_Flag = 0;    
				break;
			
			case 3:
				Time += 100;
				break;
			
			case 4:
				Time -= 100;
				break;
		}
		
  }
}