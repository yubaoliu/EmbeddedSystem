#ifndef __TICK_H__
#define __TICK_H__
#include  "systemInit.h"

char *getTime(void);
extern void SysTick_ISR(void);
extern void sysTick_Init(void);
extern void setTime(char* date,char* hh,char* mm,char* ss);
#endif