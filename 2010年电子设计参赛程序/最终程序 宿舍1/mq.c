#include "mq.h"
#include "human.h"
#include "buzzer.h"
#include  <timer.h>
#include "lcd12864.h"
#include "NRF24L01.h"


tBoolean ADC_EndFlag = false; //  定义ADC转换结束的标志
char FoundFire = 0;

//  ADC初始化
void adcInit(void)
{
    SysCtlPeriEnable(SYSCTL_PERIPH_ADC);                    //  使能ADC模块
    SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS);             //  设置ADC采样速率
    ADCSequDisable(ADC_BASE, 0);                            //  配置前先禁止采样序列

    //  采样序列配置：ADC基址，采样序列编号，触发事件，采样优先级
    ADCSequConfig(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    //  采样步进设置：ADC基址，采样序列编号，步值，通道设置
    ADCSequStepConfig(ADC_BASE, 0, 0, ADC_CTL_CH0 |
                                      ADC_CTL_END |
                                      ADC_CTL_IE);

    ADCIntEnable(ADC_BASE, 0);                  //  使能ADC中断
    IntEnable(INT_ADC0);                        //  使能ADC采样序列中断
    IntMasterEnable();                              //  使能处理器中断

    ADCSequEnable(ADC_BASE, 0);               //  使能采样序列
}


//  ADC采样
unsigned long adcSample(void)
{
    unsigned long ulValue;

    ADCProcessorTrigger(ADC_BASE, 0);                       //  处理器触发采样序列
    while (!ADC_EndFlag);                                   //  等待采样结束
    ADC_EndFlag = false;                                    //  清除ADC采样结束标志
    ADCSequDataGet(ADC_BASE, 0, &ulValue);                  //  读取ADC转换结果
    return(ulValue);
}
  
void mq_Alarm(void)
{ 
   int  ulVal;
   ulVal = adcSample();             //  ADC采样
   ulVal = (ulVal * 3000) / 1024;   //  转换成电压值
   if(ulVal>1900)
        {
        
          GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0xff);
          lcdWriteStr(4,5,"火灾发生");
          FoundFire = 1;
          sendData(3);
          buzzerInit();
          buzzerSound(1500);                                      //  蜂鸣器发出1500Hz声音
          SysCtlDelay(1000 * (TheSysClock / 3000));                //  延时约400ms
          buzzerSound(2000);                                      //  蜂鸣器发出2000Hz声音
          SysCtlDelay(1000 * (TheSysClock / 3000));                //  延时约800ms
          buzzerQuiet();
        }
        else
        {
          FoundFire = 0;
          buzzerQuiet();
          GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0x00);
        // lcdWriteStr(4,5,"无火灾 ");
        }
        SysCtlDelay(1000 * (TheSysClock / 3000));    
}
             
  


//  ADC采样序列0的中断
void ADC_Sequence_0_ISR(void)
{
    unsigned long ulStatus;

    ulStatus = ADCIntStatus(ADC_BASE, 0, true);             //  读取中断状态
    ADCIntClear(ADC_BASE, 0);                               //  清除中断状态，重要

    if (ulStatus != 0)                                      //  如果中断状态有效
    {
        ADC_EndFlag = true;                                 //  置位ADC采样结束标志
    }
}
