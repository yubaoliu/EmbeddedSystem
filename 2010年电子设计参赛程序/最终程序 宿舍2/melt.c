#include "melt.h"
#include  "lcd12864.h"
#include  "NRF24L01.h"

//�����˿ڳ�ʼ��
void meltInit(void)
{
     SysCtlPeriEnable(MELT_PERIPH);
     GPIOPinTypeIn(MELT_PORT,MELT_PIN);
}

//�������

void readMeltState(void)
{
	unsigned char meltValue;
	meltValue = GPIOPinRead(MELT_PORT,MELT_PIN);
	if(meltValue==0x00)
        {
          lcdWriteStr(4,5,"������Ʒ");
          sendData(5);
        }
}
