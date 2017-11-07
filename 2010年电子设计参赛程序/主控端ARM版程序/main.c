/* 读寄存器实验*/
#include  "systemInit.h"
#include  "NRF24L01.h"
#include  <stdio.h>
#include  <uart.h>
#include  "uartGetPut.h"
#include "lcd12864.h"
//  主函数（程序入口）

int main(void)
{

  jtagWait();                                             //  防止JTAG失效，重要！
  clockInit();                                            //  时钟初始化：晶振，6MHz
  uartInit();
  init_io();

  lcdInit();
  LedOn();
  RX_Mode();//选择模式为接收模式
  SysCtlDelay(200);//延时10us
  lcdWriteStr(1,1,"NRF24L01");
  SysCtlDelay(2600);//延时130us
  LedOff();//初始状态就是让LED灯灭
  
 // TX_Mode();
  char s[40];
  int size = 0;
  for (;;)
  {
     receiveData();
   //  sendCodeData("00100011112a");
   //  SysCtlDelay(200*(TheSysClock/3000));
   //  sendCodeData("11100011111a");
   //  SysCtlDelay(200*(TheSysClock/3000));
       if(UARTCharsAvail(UART2_BASE))
       {
        size = uartGets(s, sizeof(s));                      //  从UART接收命令字符串
        if(size > 0)
        {
          sendCodeData(s);//(s);
        //  SysCtlDelay(200*(TheSysClock/3000));

          size = 0;
          RX_Mode();//选择模式为接收模式
        //  SysCtlDelay(200);//延时10us
          SysCtlDelay(200*(TheSysClock/3000));
        }
       }
  }
}


