#ifndef  __COUNT_H__
#define  __COUNT_H__
#include  "systemInit.h"
//���������˿ڳ�ʼ��
#define  BZ                     SYSCTL_PERIPH_GPIOF
#define  BZ_PORT                GPIO_PORTF_BASE
#define  BZ_PIN_1               GPIO_PIN_1
#define  BZ_PIN_2               GPIO_PIN_5
extern void BZ_Init(void);
extern void GPIO_Port_F_ISR(void);

#endif