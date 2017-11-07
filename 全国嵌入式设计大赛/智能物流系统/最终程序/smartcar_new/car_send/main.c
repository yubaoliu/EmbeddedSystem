/*
   发送端程序
*/
#include  "systemInit.h"
#include  "NRF24L01.h"
#include  <stdio.h>
#include  "uartGetPut.h"
//  主函数（程序入口）

int main(void)
{
  jtagWait();                                             //  防止JTAG失效，重要！
  clockInit();                                            //  时钟初始化：晶振，6MHz
  uartInit();
  init_io();
  KeyInit();
  LedOff();//初始状态让LED灯灭
 // TX_Mode();//选择模式为发送模式
  //SysCtlDelay(200);//延时10us
  for (;;)
  {
    //  TX_Mode('a');
  Action();
  }
}

