#ifndef _TEMP_H_
#define _TEMP_H_

#include "systemInit.h"

#define  TEMP_PERIPH            SYSCTL_PERIPH_GPIOF
#define  TEMP_PORT              GPIO_PORTF_BASE
#define  TEMP_PIN               GPIO_PIN_0
#define  TEMP_PINI              GPIO_PIN_2
#define  GPIN          GPIOPinTypeGPIOInput 
#define  GPOUT         GPIOPinTypeGPIOOutput 
#define  GPW          GPIOPinWrite
#define  GPR          GPIOPinRead

#define  uint unsigned int
#define  uchar unsigned char

//一般先声明变量，然后声明函数

extern uint  tltemp,flagOfTemp;
extern uchar tempBuffer[6];
extern uint  integer;
extern uint  decimal;

extern uchar Init_18B20(void);

extern void temp_portInit(void);

extern uchar RdByte(void);

extern void WrByte(uchar dat);

extern  void readTemp(void);

extern  void tempToStr(void);

#endif