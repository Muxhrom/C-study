#ifndef __MAIN_H
#define __MAIN_H

#include <STC15F2K60S2.H>
#include <intrins.h>
#include <stdio.h>

#include "sys.h"
#include "key.h"
#include "seg.h"
#include "led.h"

#include "ds1302.h"
#include "onewire.h"
#include "iic.h"
#include "Uart.h"
#include "ultra.h"

#define Y4 P2 = (P2 & 0x1f) | 0x80
#define Y5 P2 = (P2 & 0x1f) | 0xa0
#define Y6 P2 = (P2 & 0x1f) | 0xc0
#define Y7 P2 = (P2 & 0x1f) | 0xe0
#define Y0 P2 = (P2 & 0x1f)

#endif