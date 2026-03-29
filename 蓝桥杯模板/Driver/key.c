#include "key.h"

unsigned char Key_Scan ()
{
	unsigned char temp = 0;
	
	R3 = R4 = 0;
	C1 = C2 = 1;
	if (C1 == 0) temp = 4;
	if (C2 == 0) temp = 8;
	
	C1 = C2 = 0;
	R3 = R4 = 1;
	if (R4 == 0) temp += 0;
	if (R3 == 0) temp += 1;
	
	return temp;
}