#include "human.h"
#include "lcd12864.h"
#include "NRF24L01.h"

extern char modebody;
unsigned char ucVal;

char FoundThief = 0;
void humanInit(void)
{
  //buzzerInit();                                           //  ��������ʼ��
  SysCtlPeriEnable(PER_PERIPH);
  GPIOPinTypeIn(PER_PORT,PER_PIN);
  
  SysCtlPeriEnable(ALARM_LED_PERIPH);
  GPIOPinTypeOut(ALARM_LED_PORT,ALARM_LED_PIN);
}
void humanSound(void)
{
      ucVal = GPIOPinRead(PER_PORT,PER_PIN);
       if((ucVal == 0x00))
       {
       //  clearAll();
         SysCtlDelay(200*(TheSysClock/3000));
        // lcdWriteStr(4,1,"�޴�����");
         GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0x00);
         buzzerQuiet();
         FoundThief = 0;
       }
      else
      {
        lcdWriteStr(4,1,"���ֵ���");
        SysCtlDelay(100*(TheSysClock/3000));
   //     lcdWriteStr(3,5,"���˴���");
   //     SysCtlDelay(100*(TheSysClock/3000));
        FoundThief = 1;
        sendData(4);
        GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0xff);
        buzzerInit();
        buzzerSound(1500);                                      //  ����������1500Hz����
        SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ400ms
        buzzerSound(2000);                                      //  ����������2000Hz����
        SysCtlDelay(1000 * (TheSysClock / 3000));                //  ��ʱԼ5000ms
      }
}
      