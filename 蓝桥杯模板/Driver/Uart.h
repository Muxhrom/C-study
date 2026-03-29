#ifndef __UART_H
#define __UART_H

#include "main.h"

void Uart_Init (void);
void Uart_Send_Byte (unsigned char ch);
void Uart_Send_String (unsigned char* str);

#endif