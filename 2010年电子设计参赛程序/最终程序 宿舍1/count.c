#include "count.h"
#include <stdio.h>
#include "lcd12864.h"
#include "tick.h"
#include "buzzer.h"
#include "NRF24L01.h"


int flagPerson;   //1--in 0--out 
int count=0;
int precount = 0;
int flag1 = 0;
int flag2 = 0;
//extern char modebody;
char str[10];
void BZ_Init(void)
{

    SysCtlPeriEnable(BZ);                           
    GPIOPinTypeIn(BZ_PORT,BZ_PIN_1);
    GPIOPinTypeIn(BZ_PORT,BZ_PIN_2);
    GPIOIntTypeSet(BZ_PORT, BZ_PIN_1,GPIO_FALLING_EDGE );     
    GPIOIntTypeSet(BZ_PORT, BZ_PIN_2,GPIO_FALLING_EDGE ); 
    GPIOPinIntEnable(BZ_PORT, BZ_PIN_1);    
    GPIOPinIntEnable(BZ_PORT, BZ_PIN_2);                   
    IntEnable(INT_GPIOF);                                   
    IntMasterEnable();  
  }
//  GPIOF���жϷ�����
void GPIO_Port_F_ISR(void)
{
    unsigned long ulStatus;
    ulStatus = GPIOPinIntStatus(BZ_PORT, true);            //  ��ȡ�ж�״̬
    GPIOPinIntClear(BZ_PORT, ulStatus);                    //  ����ж�״̬����Ҫ

    if (ulStatus & BZ_PIN_1)                          //  ���BZ1���ж�״̬��Ч
    {
          if(flag2 == 1)
          {
            count--;
            if(count <0)
              count = 0;
            lcdWriteStr(4,1,"1���뿪");
            sendData(2);
            flag2 = 0;
           if(count==0)
           {
             lcdWriteStr(3,5,"������!");
             SysCtlDelay(100*(TheSysClock/3000));
             buzzerInit();
             buzzerSound(1500);                                      //  ����������1500Hz����
             SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ400ms
             buzzerSound(2000);                                      //  ����������2000Hz����
             SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ5000ms
             buzzerQuiet();
           }
           else
           {
            sprintf(str,"����:%2d",count);
            lcdWriteStr(3,5,str);
            SysCtlDelay(100*(TheSysClock/3000));
            SysCtlDelay(100*(TheSysClock/3000));
           }

          }
          else
          {
            flag1 = 1;
          }
    }
    if(ulStatus&BZ_PIN_2)
    {
          if(flag1 == 1)
          {
            count++;
            sendData(1);
            flag1 = 0; 
            flagPerson=1;
            sprintf(str,"����:%2d",count);
            lcdWriteStr(3,5,str);
            SysCtlDelay(100*(TheSysClock/3000));
            lcdWriteStr(4,1,"1�˽���");
            SysCtlDelay(100*(TheSysClock/3000));
          }
          else
          {
            flag2 = 1;
          } 
   } 

}