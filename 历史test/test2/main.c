#include <REGX52.H>
#include <intrins.h>

// 声明变量
unsigned char ucLed = 0xfe;
unsigned char Key_Val, Key_Down, Key_Up, Key_Old;
bit System_Flag;

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
unsigned char Key_Read()
{
  unsigned char temp = 0;
  
  if (P3_4 == 0) temp = 1;
  if (P3_5 == 0) temp = 2;
  if (P3_6 == 0) temp = 3;
  if (P3_7 == 0) temp = 4;
  
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
    
    // 3. 业务执行逻辑：根据状态机的输出控制 P1 口的 LED
    if(Key_Down == 1)      // 按键 1：按下瞬间触发
    {
      P1_0 = 0;
    }
    
    if (Key_Up == 2)       // 按键 2：松开瞬间触发
    {
      P1_0 = 1;
    }
    
    if(Key_Old == 3)       // 按键 3：按住期间持续触发
    {
      P1_1 = 0;
    }
    else                   // 按键 3：没按时保持默认状态
    {
      P1_1 = 1;
    }
		
		if(System_Flag == 1)
			{
		ucLed = _crol_(ucLed,1);
		P1 = ucLed;
		Delay(100);
			}

		switch (Key_Down)
		{
			case 1:               // 当 Key_Down 等于 1 时
				System_Flag = 1;    // 开启流水灯标志
				break;              // 活干完了，跳出 switch

			case 2:               // 当 Key_Down 等于 2 时
				System_Flag = 0;    // 关闭流水灯标志
				break;              // 活干完了，跳出 switch
		}
		
  }
}