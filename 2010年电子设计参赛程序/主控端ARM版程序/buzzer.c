#include  "buzzer.h"
#include  <hw_types.h>
#include  <hw_memmap.h>
#include  <sysctl.h>
#include  <gpio.h>
#include  <timer.h>


#define  PART_LM3S1138
#include  <pin_map.h>


#define  SysCtlPeriEnable       SysCtlPeripheralEnable
#define  GPIOPinTypeOut         GPIOPinTypeGPIOOutput


//  ����ȫ�ֵ�ϵͳʱ�ӱ���
extern unsigned long TheSysClock;


//  ��������ʼ��
void buzzerInit(void)
{
    SysCtlPeriEnable(SYSCTL_PERIPH_TIMER1);                 //  ʹ��TIMER1ģ��
    SysCtlPeriEnable(CCP3_PERIPH);                          //  ʹ��CCP3���ڵ�GPIO�˿�
    GPIOPinTypeTimer(CCP3_PORT, CCP3_PIN);                  //  ������عܽ�ΪTimer����

    TimerConfigure(TIMER1_BASE, TIMER_CFG_16_BIT_PAIR |     //  ����TimerBΪ16λPWM
                                TIMER_CFG_B_PWM);
}


//  ����������ָ��Ƶ�ʵ�����
//  usFreq�Ƿ���Ƶ�ʣ�ȡֵ (ϵͳʱ��/65536)+1 �� 20000����λ��Hz
void buzzerSound(unsigned short usFreq)
{
    unsigned long ulVal;

    if ((usFreq <= TheSysClock / 65536UL) || (usFreq > 20000))
    {
        buzzerQuiet();
    }
    else
    {
          //���ע�͵�û����
//        GPIOPinTypeTimer(CCP3_PORT, CCP3_PIN);              //  ������عܽ�ΪTimer����
        ulVal = TheSysClock / usFreq;
        TimerLoadSet(TIMER1_BASE, TIMER_B, ulVal);          //  ����TimerB��ֵ
        TimerMatchSet(TIMER1_BASE, TIMER_B, ulVal / 2);     //  ����TimerBƥ��ֵ
        TimerEnable(TIMER1_BASE, TIMER_B);                  //  ʹ��TimerB����
    }
}


//  ������ֹͣ����
void buzzerQuiet(void)
{
    TimerDisable(TIMER1_BASE, TIMER_B);                     //  ��ֹTimerB����
    GPIOPinTypeOut(CCP3_PORT, CCP3_PIN);                    //  ����CCP3�ܽ�ΪGPIO���
    GPIOPinWrite(CCP3_PORT, CCP3_PIN, 0x00);                //  ʹCCP3�ܽ�����͵�ƽ
}

