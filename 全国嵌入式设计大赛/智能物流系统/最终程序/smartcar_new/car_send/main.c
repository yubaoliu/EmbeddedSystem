/*
   ���Ͷ˳���
*/
#include  "systemInit.h"
#include  "NRF24L01.h"
#include  <stdio.h>
#include  "uartGetPut.h"
//  ��������������ڣ�

int main(void)
{
  jtagWait();                                             //  ��ֹJTAGʧЧ����Ҫ��
  clockInit();                                            //  ʱ�ӳ�ʼ��������6MHz
  uartInit();
  init_io();
  KeyInit();
  LedOff();//��ʼ״̬��LED����
 // TX_Mode();//ѡ��ģʽΪ����ģʽ
  //SysCtlDelay(200);//��ʱ10us
  for (;;)
  {
    //  TX_Mode('a');
  Action();
  }
}

