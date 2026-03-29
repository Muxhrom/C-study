#ifndef _DS1302_H
#define _DS1302_H
#include <REGX52.H>

void Set_Time(unsigned char* ucTime);
void Read_Time(unsigned char* ucTime);



sbit SCK=P1^7; sbit SDA=P2^3; sbit RST=P1^3;

void Write_Ds1302_Byte(unsigned char addr, unsigned char dat);
unsigned char Read_Ds1302_Byte(unsigned char addr);

#endif