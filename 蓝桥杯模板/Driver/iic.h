#ifndef __IIC_H
#define __IIC_H

#include "main.h"

#define DELAY_TIME 5

sbit scl = P2^0;
sbit sda = P2^1;

static void I2C_Delay (unsigned char n);
void I2CStart (void);
void I2CStop (void);
void I2CSendByte (unsigned char byt);
unsigned char I2CReceiveByte (void);
unsigned char I2CWaitAck (void);
void I2CSendAck (unsigned char ackbit);

void DA_Write (unsigned char dat);
unsigned char AD_Read (unsigned char addr);
void EEP_Write (unsigned char* str, unsigned char addr, num);
void EEP_Read (unsigned char* str, unsigned char addr, num);

#endif