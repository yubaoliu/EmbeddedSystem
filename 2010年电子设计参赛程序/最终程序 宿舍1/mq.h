#ifndef __MQ_H__
#define __MQ_H__
#include  "systemInit.h"
#include  "uartGetPut.h"
#include  <adc.h>
#include  <stdio.h>
#include  "buzzer.h"


#define  ADCSequEnable          ADCSequenceEnable
#define  ADCSequDisable         ADCSequenceDisable
#define  ADCSequConfig          ADCSequenceConfigure
#define  ADCSequStepConfig      ADCSequenceStepConfigure
#define  ADCSequDataGet         ADCSequenceDataGet

extern void adcInit(void);
extern unsigned long adcSample(void);
extern void mq_Alarm(void);
void ADC_Sequence_0_ISR(void);


#endif