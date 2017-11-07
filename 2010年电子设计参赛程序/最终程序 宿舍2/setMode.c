#include "setMode.h"
#include "lcd12864.h"
#include "NRF24L01.h"

char modebody=0;
char modeforg=0;
extern tBoolean hasPrintOnce;

void  setBodyMode(char key)
{
   if(key=='1')//1.Ԥ��ģʽ
   {
     modebody=1;
     lcdWriteStr(4,1,"Ԥ��ģʽ�ѿ���");
     SysCtlDelay(100*(TheSysClock/3000));
     sendData(0);
   }
   if(key=='2')//�⾯ģʽ
   {
     modebody=0;
     lcdWriteStr(4,1,"�⾯ģʽ�ѿ���");
     SysCtlDelay(100*(TheSysClock/3000));
     sendData(0);

   }
   hasPrintOnce = false;
   
}

void  setForgMode(char key)
{

   //key=readkeyboard();
   if(key=='1')
   {
     modeforg=1;
     lcdWriteStr(4,1,"Ԥ��ģʽ�ѿ���");
     SysCtlDelay(1000*(TheSysClock/3000));
     sendData(0);
   }
   if(key=='2')
   {
     modeforg=0;
     lcdWriteStr(4,1,"�⾯ģʽ�ѿ���");
     SysCtlDelay(1000*(TheSysClock/3000));
     sendData(0);
   }
   hasPrintOnce = false;
   
}
