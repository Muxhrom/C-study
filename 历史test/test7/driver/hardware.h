#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <STC15F2K60S2.H>

void hc138(unsigned char n);
void sys_init(void);
void seg_disp(unsigned char w, unsigned char d);
unsigned char key_read(void);

#endif