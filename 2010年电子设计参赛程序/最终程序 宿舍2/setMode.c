#include "setMode.h"
#include "lcd12864.h"
#include "NRF24L01.h"

char modebody=0;
char modeforg=0;
extern tBoolean hasPrintOnce;

void  setBodyMode(char key)
{
   if(key=='1')//1.预警模式
   {
     modebody=1;
     lcdWriteStr(4,1,"预警模式已开启");
     SysCtlDelay(100*(TheSysClock/3000));
     sendData(0);
   }
   if(key=='2')//解警模式
   {
     modebody=0;
     lcdWriteStr(4,1,"解警模式已开启");
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
     lcdWriteStr(4,1,"预警模式已开启");
     SysCtlDelay(1000*(TheSysClock/3000));
     sendData(0);
   }
   if(key=='2')
   {
     modeforg=0;
     lcdWriteStr(4,1,"解警模式已开启");
     SysCtlDelay(1000*(TheSysClock/3000));
     sendData(0);
   }
   hasPrintOnce = false;
   
}
