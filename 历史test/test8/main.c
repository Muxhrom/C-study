#include <REGX52.H>

//不开门啊
void hc138(unsigned char n){
	P2 = (P2 & 0x1F) | 0x00;//擦擦前三位
	switch(n)
	{
		case 4: P2 = (P2 & 0x1F) | 0x80;break;
		case 5: P2 = (P2 & 0x1F) | 0xA0;break;
		case 6: P2 = (P2 & 0x1F) | 0xC0;break;
		case 7: P2 = (P2 & 0x1F) | 0xE0;break;
	
	}
	

}

void Delay(int xms)	//@12.000MHz
{
	unsigned char data i, j;
while(xms--){
	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}}

void LedRunning()
{
	unsigned char i;
	for (i=0; i<3; i++)
	{
		hc138(4);
		P0 = 0x00;
		hc138(0);
		Delay(100);
		
		hc138(4);
		P0 = 0xff;
		hc138(0);
		Delay(100);
	}

	for(i = 1; i <= 8; i++)
	{
		hc138(4);
		P0 = 0xff << i;
		hc138(0);
		Delay(100);
	}
	
	for(i = 1; i <= 8; i++)
	{
		hc138(4);
		P0 = ~(0xff << i)	;
		hc138(0);
		Delay(100);
	}


}

void main(){
	
	hc138(0);//初始化
	
	while (1)
	{
		LedRunning();
	
	
	}


}