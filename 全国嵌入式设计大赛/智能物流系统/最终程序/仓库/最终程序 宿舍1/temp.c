#include "temp.h"

uint  tltemp,flagOfTemp;
uchar tempBuffer[6];
uint  integer;
uint  decimal;

//��ʼ��DS18B20
uchar Init_18B20(void)
{  uchar flagOfTemp;
  
   //GPOUT(TEMP_PORT,TEMP_PIN );

   GPW(TEMP_PORT,TEMP_PIN ,0xff);
   SysCtlDelay(6 * (TheSysClock / 3000000)); 
   GPW(TEMP_PORT,TEMP_PIN ,0x00);
   SysCtlDelay(600 * (TheSysClock / 3000000)); 
   GPW(TEMP_PORT,TEMP_PIN ,0xff);
   SysCtlDelay(30* (TheSysClock / 3000000)); 
   flagOfTemp=GPR(TEMP_PORT,TEMP_PINI);//read
   SysCtlDelay(200* (TheSysClock / 3000000));
   return flagOfTemp;
   
}

void temp_portInit(void)
{
   SysCtlPeriEnable(TEMP_PERIPH);
   GPIN(TEMP_PORT,TEMP_PINI);
   GPOUT(TEMP_PORT,TEMP_PIN);
   
   //GPW(TEMP_PORT,TEMP_PIN ,0x00);
 
}


/* ��ȡ���ݵ�һ���ֽ� */
uchar RdByte(void)
{
  uchar i=0;
  uchar dat=0x00;
  uchar d=0x00;
  for(i=0;i<8;i++)
  {
    GPW(TEMP_PORT,TEMP_PIN,0XFF);
    SysCtlDelay(1 * (TheSysClock / 3000000));
    GPW(TEMP_PORT,TEMP_PIN,0X00);
    SysCtlDelay(1 * (TheSysClock / 3000000));
    GPW(TEMP_PORT,TEMP_PIN,0XFF);
    SysCtlDelay(6 * (TheSysClock / 3000000));
    dat>>=1;
    d=GPR(TEMP_PORT,TEMP_PINI);
    if(d==0x04)
      dat|=0x80;
    else
      dat|=0x00;
     SysCtlDelay(3 * (TheSysClock / 3000000));
  }
  return dat;
}

 

// д���ݵ�һ���ֽڣ�����д1��д0��ʱ϶Ҫ�� 

void WrByte(uchar dat)
{
 uchar i;
 uchar d=0x00;
 for(i=0;i<8;i++)
 {
   GPW(TEMP_PORT , TEMP_PIN,0XFF);
   SysCtlDelay(1 * (TheSysClock / 3000000));
   GPW(TEMP_PORT , TEMP_PIN,0X00);
   SysCtlDelay(1 * (TheSysClock / 3000000));
   d=dat&0x01;
   GPW(TEMP_PORT , TEMP_PIN,d);
   SysCtlDelay(30* (TheSysClock / 3000000)); 
   GPW(TEMP_PORT , TEMP_PIN,0XFF);
   SysCtlDelay(3 * (TheSysClock / 3000000));
   dat>>=1;
 }
}
//���¶�׼��
 void readTemp(void)
 {
   uchar low=0;
   uchar high=0;
   uchar sign;
   
   
   Init_18B20();
   WrByte(0xcc);//����rom
   WrByte(0x44);//�����¶�ת��
   SysCtlDelay(200* (TheSysClock / 3000000)); 
   Init_18B20();
   WrByte(0xcc);
   WrByte(0xbe);//���¶�
   SysCtlDelay(200 * (TheSysClock / 3000000));
   
   low=RdByte();
   high=RdByte();
   sign=high & 0xf8;
   
  if(sign == 0X00)
  {
    integer = high << 4;
    integer += (low & 0XF0) >> 4;
    decimal = low & 0X0F;
    
    tempBuffer[0] = integer / 100 + '0';    //Ĭ���¶Ȳ��ᳬ��199��,���¶�ֵת�����ַ���ʽ
    if(tempBuffer[0] == '1') 
    {
      tempBuffer[0] = '1';
    }
    else
    {
      tempBuffer[0] = ' ';
    }    
  }
  else
  {
    tempBuffer[0] = '-';      //Ĭ���¶Ȳ��ᳬ������100��
    integer = high << 4;
    integer += (low & 0XF0) >> 4;
    integer = ~integer + 1;  //ֻ�Ƕ�����λ����ȡ����1
    decimal = ~low & 0X0F;   //С��λֻ��ȡ�������1
  }
 }
void tempToStr(void)
{
//  float deci;
  tempBuffer[1] = integer % 100 / 10 + '0';  //�¶�ʮλ
  tempBuffer[2] = integer % 10 + '0';        //�¶ȸ�λ
  tempBuffer[3] = '.';
//  deci = (decimal * 0.0625) ;    //����С�����ֵ�������ʾ
//  tempBuffer[4] = deci * 10 % 10 + '0';   //�����õ���ֻ��С�����ֵ���ֵ����ûС����
  tempBuffer[4] = decimal * 625 / 1000 % 10 + '0';
  tempBuffer[5] = '\0';
}
