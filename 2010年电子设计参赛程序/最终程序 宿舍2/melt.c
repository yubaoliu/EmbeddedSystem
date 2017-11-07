#include "melt.h"
#include  "lcd12864.h"
#include  "NRF24L01.h"

//金属端口初始化
void meltInit(void)
{
     SysCtlPeriEnable(MELT_PERIPH);
     GPIOPinTypeIn(MELT_PORT,MELT_PIN);
}

//金属检测

void readMeltState(void)
{
	unsigned char meltValue;
	meltValue = GPIOPinRead(MELT_PORT,MELT_PIN);
	if(meltValue==0x00)
        {
          lcdWriteStr(4,5,"贵重物品");
          sendData(5);
        }
}
