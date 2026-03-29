#include "hardware.h"

// 蓝桥杯专属段码与位码
unsigned char code seg_dula[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0xff};
unsigned char code seg_wela[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

// 极其好记的开门函数
void hc138(unsigned char n)
{
    P2 = (P2 & 0x1F) | 0x00; 
    switch(n)
    {
        case 4: P2 = (P2 & 0x1F) | 0x80; break; 
        case 5: P2 = (P2 & 0x1F) | 0xA0; break; 
        case 6: P2 = (P2 & 0x1F) | 0xC0; break; 
        case 7: P2 = (P2 & 0x1F) | 0xE0; break; 
    }
}

// 关灯关蜂鸣器
void sys_init(void)
{
    hc138(5); P0 = 0x00; hc138(0); 
    hc138(4); P0 = 0xFF; hc138(0); 
}

// 数码管显示
void seg_disp(unsigned char w, unsigned char d)
{
    P0 = 0xFF;         hc138(7); hc138(0); 
    P0 = seg_wela[w];  hc138(6); hc138(0); 
    P0 = seg_dula[d];  hc138(7); hc138(0); 
}

// 矩阵按键读取
unsigned char key_read(void)
{
    unsigned char temp = 0;
    P30=0; P31=1; P32=1; P33=1;
    if(P34==0) temp=1; if(P35==0) temp=2; if(P42==0) temp=3; if(P44==0) temp=4;
    P30=1; P31=0; P32=1; P33=1;
    if(P34==0) temp=5; if(P35==0) temp=6; if(P42==0) temp=7; if(P44==0) temp=8;
    P30=1; P31=1; P32=0; P33=1;
    if(P34==0) temp=9; if(P35==0) temp=10; if(P42==0) temp=11; if(P44==0) temp=12;
    P30=1; P31=1; P32=1; P33=0;
    if(P34==0) temp=13; if(P35==0) temp=14; if(P42==0) temp=15; if(P44==0) temp=16;
    return temp;
}