#include <REGX52.H>

//不开门啊
void hc138(unsigned char n){
    P2 = (P2 & 0x1F) | 0x00; //擦擦前三位
    switch(n)
    {
        case 4: P2 = (P2 & 0x1F) | 0x80;break;
        case 5: P2 = (P2 & 0x1F) | 0xA0;break;
        case 6: P2 = (P2 & 0x1F) | 0xC0;break;
        case 7: P2 = (P2 & 0x1F) | 0xE0;break;
    }   
}

//延时函数
void Delay(int xms)    //@12.000MHz
{
    unsigned char data i, j;
    while(xms--){
        i = 12;
        j = 169;
        do
        {
            while (--j);
        } while (--i);
    }
}

//封装函数
void Out(unsigned char channel, unsigned char dat)
{
    hc138(channel); 
    P0 = dat;
    hc138(0);
}

void LedRunning()
{
    unsigned char i;
    
    //闪烁
    for (i=0; i<3; i++)
    {
        Out(4, 0x00);
        Delay(100);
        
        Out(4, 0xff);
        Delay(100);
    }

    //变长
    for(i = 1; i <= 8; i++)
    {
        Out(4, 0xff << i); 
        Delay(100);
    }
    
    Out(5, 0x10); //继电器
    Delay(10000);
    
    Out(5, 0x40); //蜂鸣器
    Delay(10000);
    
    Out(5, 0x00); //全关
    Delay(100);
    
    //变短
    for(i = 1; i <= 8; i++)
    {
        Out(4, ~(0xff << i)); 
        Delay(100);
    }
}

void main(){
    
    //初始化
    Out(5, 0x00); 
    Out(4, 0xFF); 
    
    while (1)
    {
        LedRunning();
    }
}