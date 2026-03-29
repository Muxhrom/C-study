#include <REGX52.H>
#include <intrins.h>

// 段码
unsigned char code SMG_duanma[18] = {
  0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
  0x80, 0x90, 0x88, 0x80, 0xc6, 0xc0, 0x86, 0x8e,
  0xbf, 0x7f
};

// 定义
unsigned char yu;

// 延时函数
void Delay(unsigned int xms) //@12.000MHz
{
  unsigned char data i, j;
  while (xms--) {
    i = 12;
    j = 169;
    do {
      while (--j);
    } while (--i);
  }
}

// hc138
void hc138(unsigned char n)
{
  P2 = (P2 & 0x1F) | 0x00;
  switch (n) {
    case 4: P2 = (P2 & 0x1F) | 0x80; break;
    case 5: P2 = (P2 & 0x1F) | 0xA0; break;
    case 6: P2 = (P2 & 0x1F) | 0xC0; break;
    case 7: P2 = (P2 & 0x1F) | 0xE0; break;
  }
}

void out(unsigned char channel, unsigned char dat)
{
  P0 = dat;
  hc138(channel);
  hc138(0);
}

// 修复后的显示单元：自带消影！
void smg_bit(unsigned char value, unsigned char pos)
{
  out(6, 0x01 << pos);       // 1. 开聚光灯
  out(7, SMG_duanma[value]); // 2. 画形状
  Delay(2);                  // 3. 亮 2ms 让眼睛看清
  out(7, 0xFF);              // 4. 极其重要：消影全灭！
}

// 纯粹的显示任务（不含任何长延时，总耗时约 16ms）
void smg_display(unsigned char m)
{
  smg_bit(2, 0);
  smg_bit(0, 1);
  smg_bit(2, 2);
  smg_bit(6, 3);

  smg_bit(16, 4); // '-'
  smg_bit(16, 5); // '-'

  smg_bit(m / 10, 6); // 月份十位
  smg_bit(m % 10, 7); // 月份个位
}

// 全局变量
unsigned char yu = 1;   // 月份从 1 开始
unsigned int count = 0; // 计时器

void main()
{
  while (1) {
    // 1. 永不停歇地刷新屏幕（每次耗时约 16ms）
    smg_display(yu);

    // 2. 利用循环次数来“软延时”
    count++;
    if (count >= 30) { // 扫描 30 次，大约经过了 30 * 16ms ≈ 500ms（半秒钟）
      count = 0;       // 计数器清零
      yu++;            // 月份加一
      if (yu > 12) {
        yu = 1;
      }
    }
  }
}