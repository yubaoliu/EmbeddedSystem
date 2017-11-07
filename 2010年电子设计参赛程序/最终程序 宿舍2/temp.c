#include "temp.h"

uint  tltemp,flagOfTemp;
uchar tempBuffer[6];
uint  integer;
uint  decimal;

//初始化DS18B20
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


/* 读取数据的一个字节 */
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

 

// 写数据的一个字节，满足写1和写0的时隙要求 

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
//度温度准备
 void readTemp(void)
 {
   uchar low=0;
   uchar high=0;
   uchar sign;
   
   
   Init_18B20();
   WrByte(0xcc);//跳过rom
   WrByte(0x44);//启动温度转换
   SysCtlDelay(200* (TheSysClock / 3000000)); 
   Init_18B20();
   WrByte(0xcc);
   WrByte(0xbe);//读温度
   SysCtlDelay(200 * (TheSysClock / 3000000));
   
   low=RdByte();
   high=RdByte();
   sign=high & 0xf8;
   
  if(sign == 0X00)
  {
    integer = high << 4;
    integer += (low & 0XF0) >> 4;
    decimal = low & 0X0F;
    
    tempBuffer[0] = integer / 100 + '0';    //默认温度不会超过199度,将温度值转换成字符形式
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
    tempBuffer[0] = '-';      //默认温度不会超过零下100度
    integer = high << 4;
    integer += (low & 0XF0) >> 4;
    integer = ~integer + 1;  //只是对整数位进行取反加1
    decimal = ~low & 0X0F;   //小数位只需取反不需加1
  }
 }
void tempToStr(void)
{
//  float deci;
  tempBuffer[1] = integer % 100 / 10 + '0';  //温度十位
  tempBuffer[2] = integer % 10 + '0';        //温度个位
  tempBuffer[3] = '.';
//  deci = (decimal * 0.0625) ;    //这是小数部分的整数表示
//  tempBuffer[4] = deci * 10 % 10 + '0';   //这样得到的只是小数部分的数值，而没小数点
  tempBuffer[4] = decimal * 625 / 1000 % 10 + '0';
  tempBuffer[5] = '\0';
}
