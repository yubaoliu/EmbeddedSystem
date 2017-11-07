#ifndef  __COUNT_H__
#define  __COUNT_H__
#include  "systemInit.h"
//测试人数端口初始化
#define  BZ                     SYSCTL_PERIPH_GPIOF
#define  BZ_PORT                GPIO_PORTF_BASE
#define  BZ_PIN_1               GPIO_PIN_1
#define  BZ_PIN_2               GPIO_PIN_5
extern void BZ_Init(void);
extern void GPIO_Port_F_ISR(void);

#endif