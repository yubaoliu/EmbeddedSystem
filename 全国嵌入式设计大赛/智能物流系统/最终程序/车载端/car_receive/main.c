#include  "systemInit.h"
#include  "NRF24L01.h"
#define  PART_LM3S1138 
#include  <pin_map.h> 
#include "car.h"
#include "lcd12864.h"
#include <stdio.h>
#include <timer.h>

#include  <systick.h> 
//测速传感器
#define V_PERIPH    SYSCTL_PERIPH_GPIOD
#define V_PORT      GPIO_PORTD_BASE
#define V_PIN       GPIO_PIN_2   

//红外壁障pf4 pf7

#define RED_PERIPH    SYSCTL_PERIPH_GPIOG
#define RED_PORT      GPIO_PORTG_BASE
#define RED_PIN_R      GPIO_PIN_2
#define RED_PIN_L       GPIO_PIN_0

void redInit(void) //红外壁障模块初始化
{
   SysCtlPeriEnable(RED_PERIPH);
  GPIOPinTypeIn(RED_PORT,RED_PIN_R);
  GPIOPinTypeIn(RED_PORT,RED_PIN_L);
}

unsigned long int i=0,flag2=0; //flag
unsigned long int time=0;
void sysTick_Init(void)   //1 second
{
   SysTickPeriodSet(6000000UL);
  SysTickIntEnable();
  IntMasterEnable();
  SysTickEnable();
}
void sg90_Timer_Init(void)
{
  SysCtlPeriEnable(SYSCTL_PERIPH_TIMER1);
  SysCtlPeriEnable(CCP3_PERIPH);
  GPIOPinTypeTimer(CCP3_PORT,CCP3_PIN);
  TimerConfigure(TIMER1_BASE,TIMER_CFG_16_BIT_PAIR|TIMER_CFG_B_PWM);
  TimerControlLevel(TIMER1_BASE,TIMER_B,true);
  TimerLoadSet(TIMER1_BASE,TIMER_B,120000);
  TimerMatchSet(TIMER1_BASE,TIMER_B,9000);
  TimerEnable(TIMER1_BASE,TIMER_B);
}
//  main function
int main(void)
{
   extern NRF_IO CE,CSN;
   extern uchar rx_buf[20];
   char flag=0;//控制红外

    jtagWait();                                             //  防止JTAG失效，重要！
    clockInit();                                            //  时钟初始化：晶振，6MHz
    init_io();;  //nrf24L01
    SysCtlDelay(200);//延时10us
    RX_Mode();//选择模式为接收模式
     redInit();//红外壁障模块初始化
     
    Car_Init();
    lcdInit();
    
    sysTick_Init();
    sg90_Timer_Init();
    
    
   //测速
    
    SysCtlPeriEnable(V_PERIPH);
    GPIOPinTypeIn(V_PORT,V_PIN);
    GPIOIntTypeSet(V_PORT,V_PIN,GPIO_FALLING_EDGE);     //测速
    GPIOPinIntEnable(V_PORT,V_PIN);  
    //Forward();
   lcdWriteStr(0,2,"智能物流系统");
/* 9000-------0'
6000--------R45'
3000--------R90
12000------L45'
15000-----L90--sg90*/
    IntEnable(INT_GPIOD);
    IntMasterEnable();

   
    for (;;)
    {
  
                
        switch(rx_buf[0])
        {
            case 'a':
             {
                Forward(); 
                TimerMatchSet(TIMER1_BASE,TIMER_B,3000);  //right 
                TimerEnable(TIMER1_BASE,TIMER_B);
                flag=1;
  
                  break;
             }  
           case 'b':
             {
                Stop();
                flag=0;
                TimerMatchSet(TIMER1_BASE,TIMER_B,15000); //left
                 TimerEnable(TIMER1_BASE,TIMER_B);     
               break;
             }
 
            default:
              break;
          }
        if(flag==1)
        {
          if((GPIOPinRead(RED_PORT, RED_PIN_R) == 0x00)&&(GPIOPinRead(RED_PORT, RED_PIN_R) == 0x00))
          {
              Stop();
              TimerMatchSet(TIMER1_BASE,TIMER_B,15000); //left
               TimerEnable(TIMER1_BASE,TIMER_B);  
     
          }
          else
          {
            Forward(); 
           // TimerMatchSet(TIMER1_BASE,TIMER_B,3000);  //right 
            // TimerEnable(TIMER1_BASE,TIMER_B); 
          }
        }
   
      /* 
       for(i=0;i<5;i++)
       {
        SysCtlDelay(5000*(TheSysClock/3000));
        TimerMatchSet(TIMER1_BASE,TIMER_B,15000);   //L90
        TurnLeft();
        SysCtlDelay(5000*(TheSysClock/3000));
       
        TimerMatchSet(TIMER1_BASE,TIMER_B,3000);    //R90
        TurnRight();
        SysCtlDelay(5000*(TheSysClock/3000));   
        Forward();
        SysCtlDelay(2000*(TheSysClock/3000));
       }*/
     //  Forward();
       SysCtlDelay(2000*(TheSysClock/3000));
    }
    
}
void GPIO_Port_D_ISR(void)
{
  
  char ucVal[20];
  unsigned long ulStatus,circle;
  float s;
  ulStatus=GPIOPinIntStatus(V_PORT,true);
  GPIOPinIntClear(V_PORT,ulStatus);
  
  if(ulStatus&V_PIN)
  {
    i++;
    flag2++;
  }
  
  circle=i/4;   
  s=circle/1000.0;
  sprintf(ucVal,"路程：%.2f m",s);  //s 为路程
  lcdWriteStr(3,1,ucVal);

  
  }
void SysTick_ISR(void)
{
  unsigned int minute,hour,second,temp;   //   硬件会自动清除SysTick中断状态 
  float v;
   char chour[10],cminute[10],csecond[10],s[30],ucVal[20];
  time++;
  temp=time;
  hour=(temp/3600)%24;
  if(hour>=10) sprintf(chour,"%ld",hour);
  else sprintf(chour,"0%ld",hour);
  temp%=3600;
  minute=temp/60;
  if(minute>=10) sprintf(cminute,"%ld",minute);
  else sprintf(cminute,"0%d",minute);
  temp%=60;
  second=temp;
  if(second>=10) sprintf(csecond,"%ld",second);
  else sprintf(csecond,"0%ld",second);
  sprintf(s,"时间:%s:%s:%s",chour,cminute,csecond);
  lcdWriteStr(2,1,s);
  v=flag2/4/1000.0;
  sprintf(ucVal,"速度：%.3f m/s",v);  //v 为速度
  lcdWriteStr(4,1,ucVal);
  
  flag2=0;
  
  
}


