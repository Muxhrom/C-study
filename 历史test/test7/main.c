#include <STC15F2K60S2.H>
#include "hardware.h"

// 极简变量命名
unsigned char seg_buf[8] = {8, 17, 17, 17, 17, 17, 17, 17}; // 让第一个管子开局就显示 8
unsigned char seg_pos = 0;

unsigned char key_val, key_down, key_up, key_old;

// tick 代表滴答滴答的计时器，比 slow_down 好记太多了
unsigned int key_tick = 0; 
unsigned int seg_tick = 0; 

// 定时器初始化 (ISP生成粘贴过来)
void timer0_init(void) 
{
    AUXR |= 0x80; 
    TMOD &= 0xF0; 
    TL0 = 0x20;   
    TH0 = 0xD1;   
    TF0 = 0;      
    TR0 = 1;      
    ET0 = 1; EA = 1; 
}

// 定时器中断
void timer0_isr() interrupt 1
{
    key_tick++;
    seg_tick++;
    
    seg_disp(seg_pos, seg_buf[seg_pos]);
    if(++seg_pos >= 8) seg_pos = 0;
}

// 按键业务处理
void key_proc()
{
    if(key_tick < 10) return; // 10ms 消抖
    key_tick = 0;             

    // 状态机三步曲
    key_val = key_read(); 
    key_down = key_val & (key_val ^ key_old); // 提取按下瞬间的动作
    key_up = ~key_val & (key_val ^ key_old);  // 提取松开瞬间的动作
    key_old = key_val;

    // 根据“真实键码”执行动作
    switch(key_down)
    {
        case 4:  // S7 按下 (键码是4)
            seg_buf[0] = 1; 
            break;
            
        case 8:  // S11 按下 (键码是8，P31行与P44列交叉)
            seg_buf[0] = 2; 
            break;
            
        case 16: // S19 按下 (键码是16，P33行与P44列交叉)
            seg_buf[0] = 17; // 全灭
            break;
    }
}

// 数码管业务处理
void seg_proc()
{
    if(seg_tick < 500) return; 
    seg_tick = 0;              
}

// 主函数
void main()
{
    sys_init(); 
    timer0_init(); 
    
    while(1)
    {
        key_proc(); 
        seg_proc(); 
    }
}