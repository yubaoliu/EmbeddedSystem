#ifndef __MELT_H__
#define __MELE_H__

#include "systemInit.h"

#define MELT_PERIPH         SYSCTL_PERIPH_GPIOB
#define MELT_PORT           GPIO_PORTB_BASE
#define MELT_PIN            GPIO_PIN_6

extern void meltInit(void);
extern void readMeltState(void);
#endif