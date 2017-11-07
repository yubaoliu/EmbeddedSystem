#include  "systemInit.h"
#ifndef __HUMAN_H__
#define __HUMAN_H__
#include  "buzzer.h"
#define PER_PERIPH      SYSCTL_PERIPH_GPIOF
#define PER_PORT        GPIO_PORTF_BASE
#define PER_PIN         GPIO_PIN_3
#define ALARM_LED_PERIPH      SYSCTL_PERIPH_GPIOB
#define ALARM_LED_PORT        GPIO_PORTB_BASE
#define ALARM_LED_PIN         GPIO_PIN_5

//functions definition
extern char modebody;
extern char modeforg;
void humanInit(void);
void humanSound(void);

#endif