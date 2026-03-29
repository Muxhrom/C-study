#ifndef __LED_H
#define __LED_H

#include "main.h"

void Led_Disp (unsigned char addr, enable);
void Buzz (unsigned char enable);
void Relay (unsigned char enable);
void Motor (unsigned char enable);

#endif