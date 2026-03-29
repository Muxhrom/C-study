#include "ds1302.h"

void Write_Ds1302 (unsigned char temp)
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte (unsigned char address, unsigned char dat)
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte (unsigned char address)
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

//=====================================================

void Clock_Write (unsigned char *Clock)
{
	unsigned char i;
	
	Write_Ds1302_Byte (0x8e, 0x00);
	Write_Ds1302_Byte (0x80, 0x80); //[maybe]
	
	for (i = 0; i < 7; i ++) {
		Write_Ds1302_Byte (0x8c - 2 * i, * Clock ++);
	}
	
	Write_Ds1302_Byte (0x8e, 0x80);
}

void Clock_Read (unsigned char* Clock)
{
	unsigned char i;
	
	for (i = 0; i < 7; i ++) {
		* Clock ++ = Read_Ds1302_Byte (0x8d - 2 * i);
	}
}