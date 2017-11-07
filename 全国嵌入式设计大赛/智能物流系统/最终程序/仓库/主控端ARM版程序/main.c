/* ���Ĵ���ʵ��*/
#include  "systemInit.h"
#include  "NRF24L01.h"
#include  <stdio.h>
#include  <uart.h>
#include  "uartGetPut.h"
#include "lcd12864.h"
//  ��������������ڣ�

int main(void)
{

  jtagWait();                                             //  ��ֹJTAGʧЧ����Ҫ��
  clockInit();                                            //  ʱ�ӳ�ʼ��������6MHz
  uartInit();
  init_io();

  lcdInit();
  LedOn();
  RX_Mode();//ѡ��ģʽΪ����ģʽ
  SysCtlDelay(200);//��ʱ10us
  lcdWriteStr(1,1,"NRF24L01");
  SysCtlDelay(2600);//��ʱ130us
  LedOff();//��ʼ״̬������LED����
  
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
        size = uartGets(s, sizeof(s));                      //  ��UART���������ַ���
        if(size > 0)
        {
          sendCodeData(s);//(s);
        //  SysCtlDelay(200*(TheSysClock/3000));

          size = 0;
          RX_Mode();//ѡ��ģʽΪ����ģʽ
        //  SysCtlDelay(200);//��ʱ10us
          SysCtlDelay(200*(TheSysClock/3000));
        }
       }
  }
}


