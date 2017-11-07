#include "mq.h"
#include "human.h"
#include "buzzer.h"
#include  <timer.h>
#include "lcd12864.h"
#include "NRF24L01.h"


tBoolean ADC_EndFlag = false; //  ����ADCת�������ı�־
char FoundFire = 0;

//  ADC��ʼ��
void adcInit(void)
{
    SysCtlPeriEnable(SYSCTL_PERIPH_ADC);                    //  ʹ��ADCģ��
    SysCtlADCSpeedSet(SYSCTL_ADCSPEED_125KSPS);             //  ����ADC��������
    ADCSequDisable(ADC_BASE, 0);                            //  ����ǰ�Ƚ�ֹ��������

    //  �����������ã�ADC��ַ���������б�ţ������¼����������ȼ�
    ADCSequConfig(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    //  �����������ã�ADC��ַ���������б�ţ���ֵ��ͨ������
    ADCSequStepConfig(ADC_BASE, 0, 0, ADC_CTL_CH0 |
                                      ADC_CTL_END |
                                      ADC_CTL_IE);

    ADCIntEnable(ADC_BASE, 0);                  //  ʹ��ADC�ж�
    IntEnable(INT_ADC0);                        //  ʹ��ADC���������ж�
    IntMasterEnable();                              //  ʹ�ܴ������ж�

    ADCSequEnable(ADC_BASE, 0);               //  ʹ�ܲ�������
}


//  ADC����
unsigned long adcSample(void)
{
    unsigned long ulValue;

    ADCProcessorTrigger(ADC_BASE, 0);                       //  ������������������
    while (!ADC_EndFlag);                                   //  �ȴ���������
    ADC_EndFlag = false;                                    //  ���ADC����������־
    ADCSequDataGet(ADC_BASE, 0, &ulValue);                  //  ��ȡADCת�����
    return(ulValue);
}
  
void mq_Alarm(void)
{ 
   int  ulVal;
   ulVal = adcSample();             //  ADC����
   ulVal = (ulVal * 3000) / 1024;   //  ת���ɵ�ѹֵ
   if(ulVal>1900)
        {
        
          GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0xff);
          lcdWriteStr(4,5,"���ַ���");
          FoundFire = 1;
          sendData(3);
          buzzerInit();
          buzzerSound(1500);                                      //  ����������1500Hz����
          SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ400ms
          buzzerSound(2000);                                      //  ����������2000Hz����
          SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ800ms
          buzzerQuiet();
        }
        else
        {
          FoundFire = 0;
          buzzerQuiet();
          GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0x00);
        // lcdWriteStr(4,5,"�޻��� ");
        }
        SysCtlDelay(1000 * (TheSysClock / 3000));    
}
             
  


//  ADC��������0���ж�
void ADC_Sequence_0_ISR(void)
{
    unsigned long ulStatus;

    ulStatus = ADCIntStatus(ADC_BASE, 0, true);             //  ��ȡ�ж�״̬
    ADCIntClear(ADC_BASE, 0);                               //  ����ж�״̬����Ҫ

    if (ulStatus != 0)                                      //  ����ж�״̬��Ч
    {
        ADC_EndFlag = true;                                 //  ��λADC����������־
    }
}
