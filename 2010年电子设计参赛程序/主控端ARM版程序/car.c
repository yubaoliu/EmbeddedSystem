#include  "systemInit.h"
#include "car.h"
#include <timer.h>

#define  PART_LM3S1138
#include  <pin_map.h>

#define IN_PERIPH    SYSCTL_PERIPH_GPIOF
#define IN_PORT      GPIO_PORTF_BASE
#define IN_1         GPIO_PIN_0
#define IN_2         GPIO_PIN_1
#define IN_3         GPIO_PIN_2
#define IN_4         GPIO_PIN_3
void IN_Init(void)
{
  /*
  现在A，B的输入采用PWM的方式来进行，可能输入的电压不是5V，而是3.3V。
  */
    SysCtlPeriEnable(SYSCTL_PERIPH_TIMER0);                 //  ??Timer0
    SysCtlPeriEnable(CCP0_PERIPH);                          //  ??CCP2???GPIO??
    GPIOPinTypeTimer(CCP0_PORT, CCP0_PIN);                  //  ??CCP2???PWM??
    SysCtlPeriEnable(CCP1_PERIPH);                          //  ??CCP1???GPIO??
    GPIOPinTypeTimer(CCP1_PORT, CCP1_PIN);                  //  ??CCP1???PWM??

    TimerConfigure(TIMER0_BASE, TIMER_CFG_16_BIT_PAIR |     //  ??Timer??16?PWM
                                TIMER_CFG_A_PWM |
                                TIMER_CFG_B_PWM);

    TimerControlLevel(TIMER0_BASE, TIMER_BOTH, true);      //  ??PWM????
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, 100);           //  ??TimerBoth??
    TimerMatchSet(TIMER0_BASE, TIMER_A, 98);             //  ??TimerA?PWM???
    TimerMatchSet(TIMER0_BASE, TIMER_B, 93);             //  ??TimerB?PWM???
    TimerEnable(TIMER0_BASE, TIMER_BOTH);                  //  ??Timer??,PWM????

    SysCtlPeriEnable(IN_PERIPH);
    GPIOPinTypeOut(IN_PORT,IN_1|IN_2|IN_3|IN_4);
    GPIOPinWrite(IN_PORT,IN_1|IN_2|IN_3|IN_4,0x00);

}

void L_Forward(void)
{
  GPIOPinWrite(IN_PORT,IN_1,0xff);
  GPIOPinWrite(IN_PORT,IN_2,0x00);
}
void R_Forward(void)
{
  GPIOPinWrite(IN_PORT,IN_3,0x00);
  GPIOPinWrite(IN_PORT,IN_4,0xff);
}
void L_Stop(void)
{
  GPIOPinWrite(IN_PORT,IN_1,0x00);
  GPIOPinWrite(IN_PORT,IN_2,0x00);
}
void R_Stop(void)
{
  GPIOPinWrite(IN_PORT,IN_3,0x00);
  GPIOPinWrite(IN_PORT,IN_4,0x00);
}
void L_Backward(void)
{
  GPIOPinWrite(IN_PORT,IN_1,0x00);
  GPIOPinWrite(IN_PORT,IN_2,0xff);
}
void R_Backward(void)
{
  GPIOPinWrite(IN_PORT,IN_3,0xff);
  GPIOPinWrite(IN_PORT,IN_4,0x00);
}
void Forward(void)
{
  L_Forward();
  R_Forward();
}
void Stop(void)
{
  L_Stop();
  R_Stop();
}
void Backward(void)
{
  L_Backward();
  R_Backward();
}
void TurnRight(void)
{
      R_Stop();
      SysCtlDelay(3000 * (TheSysClock / 3000));   
      R_Forward();
      
}
void TurnLeft(void)
{
  L_Stop();
  SysCtlDelay(3000 * (TheSysClock / 3000));   
  L_Forward();
}