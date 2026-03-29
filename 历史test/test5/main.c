#include <STC15F2K60S2.H>
#include <intrins.h> // 包含 _crol_ 移位函数的头文件

// 延时函数：毫秒级延时 (@12.000MHz)
// 注意：这里改成了 unsigned int，最大可以支持 65535 毫秒
void Delay(unsigned int xms)    
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

// 核心门控函数：控制 138译码器 打通指定的 573锁存器 通道
void Select_HC573(unsigned char channel)
{
  // P2 端口的高三位（P2.7, P2.6, P2.5）控制 138 译码器
  P2 = (P2 & 0x1F) | 0x00; // 先把高三位清零，防止干扰
  
  switch(channel)
  {
    case 4: P2 = (P2 & 0x1F) | 0x80; break; // 选择 Y4C，打通 LED 控制通道
    case 5: P2 = (P2 & 0x1F) | 0xA0; break; // 选择 Y5C，打通 蜂鸣器/继电器 控制通道
  }
}

// 主函数
void main()
{
  // 1. 定义一个变量，装载初始的 LED 状态 (0xFE 也就是二进制 1111 1110，最低位灯亮)
  unsigned char led_data = 0xFE; 

  // 2. 蓝桥杯上电必备操作：关闭蜂鸣器，防止发出刺耳噪音
  Select_HC573(5); // 打通蜂鸣器通道
  P0 = 0x00;       // 写入低电平关闭蜂鸣器
  Select_HC573(0); // 锁死通道

  // 3. 主循环
  while (1)
  {
    // 第 1 步：输出电平点亮 LED
    Select_HC573(4);  // 打通 LED 控制通道
    P0 = led_data;    // 把当前的 led_data 状态丢给 P0 口
    Select_HC573(0);  // 锁死通道，LED 状态保持不变

    // 第 2 步：延时停留，让肉眼能看清灯亮着
    Delay(500);       // 停留 500 毫秒 (0.5秒)

    // 第 3 步：移位操作，准备点亮下一个灯
    // _crol_ 是循环左移函数，把 1111 1110 变成 1111 1101，再变成 1111 1011...
    led_data = _crol_(led_data, 1); 
  }
}