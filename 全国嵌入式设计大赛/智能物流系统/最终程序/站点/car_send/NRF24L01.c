#include "NRF24L01.h"
#include "systemInit.h"
#include "ssi.h"

#define PART_LM3S1138
#include <pin_map.h>
#include <stdio.h> 
//  定义KEY1 pd1
#define  KEY_PERIPHD             SYSCTL_PERIPH_GPIOD
#define  KEY_PORTD               GPIO_PORTD_BASE
#define  KEY_PIND                GPIO_PIN_1
//  定义KEY2 pg5
#define  KEY_PERIPHG             SYSCTL_PERIPH_GPIOG
#define  KEY_PORTG               GPIO_PORTG_BASE
#define  KEY_PING                GPIO_PIN_5
//发送地址
uchar TX_ADDRESS[TX_ADR_WIDTH] = {0x34,0x43,0x10,0x10,0x01};

uchar rx_buf[TX_PLOAD_WIDTH];//接收缓冲区
uchar tx_buf[TX_PLOAD_WIDTH];//发送缓冲区
uchar flag;
uchar sta;
int key1=0;
int key2=0;


void KeyInit(void)
{
      SysCtlPeriEnable(KEY_PERIPHD);                           //  使能KEY所在的GPIOD端口
    GPIOPinTypeIn(KEY_PORTD, KEY_PIND);                       //  设置KEY1所在管脚为输入
    GPIOIntTypeSet(KEY_PORTD, KEY_PIND, GPIO_LOW_LEVEL);      //  设置KEY1管脚的中断类型

    GPIOPinIntEnable(KEY_PORTD, KEY_PIND);                    //  使能KEY1所在管脚的中断
    IntEnable(INT_GPIOD);                                   //  使能GPIOD端口中断
    
    SysCtlPeriEnable(KEY_PERIPHG);                           //  使能KEY所在的GPIO端口
    GPIOPinTypeIn(KEY_PORTG, KEY_PING);                       //  设置KEY2所在管脚为输入
    GPIOIntTypeSet(KEY_PORTG, KEY_PING, GPIO_LOW_LEVEL);      //  设置KEY2管脚的中断类型

    GPIOPinIntEnable(KEY_PORTG, KEY_PING);                    //  使能KEY所在管脚的中断
    IntEnable(INT_GPIOG);                                   //  使能GPIOD端口中断
    IntMasterEnable();                                      //  使能处理器中断
}

//  GPIOD的中断服务函数
void GPIO_Port_D_ISR(void)
{
    
    unsigned char ucVal;
    unsigned long ulStatus;

    ulStatus = GPIOPinIntStatus(KEY_PORTD, true);            //  读取中断状态
    GPIOPinIntClear(KEY_PORTD, ulStatus);                    //  清除中断状态，重要

    if (ulStatus & KEY_PIND)                                 //  如果KEY的中断状态有效
    {
     key1=1;
    
   //  TX_Mode('a');

    }
}
//  GPIOG的中断服务函数
void GPIO_Port_G_ISR(void)
{
    unsigned char ucVal;
    unsigned long ulStatus;

    ulStatus = GPIOPinIntStatus(KEY_PORTG, true);            //  读取中断状态
    GPIOPinIntClear(KEY_PORTG, ulStatus);                    //  清除中断状态，重要

    if (ulStatus & KEY_PING)                                 //  如果KEY的中断状态有效
    {
     key2=1;
    
     //TX_Mode('b');
    }
    else
    {
    }
}
void Action(void)
{

  if(key1)  
  {
    TX_Mode('a');  //forward
    key1=0;
  }

  if(key2)
  {
    TX_Mode('b');//stop
    key2=0;
  }
//if(key1&&key2)
  //{
  // TX_Mode('c'); //backward
// }
 // else
 // {
 //   if(key1==0)
  // {
  //   TX_Mode('b');//stop
 //  }
  //}

 // if(key2==0)  
 // {TX_Mode('c'); //backward
   // TX_Mode('d');  //turnleft
  //}
  
}




NRF_IO CE,CSN,IRQ;

void NRF_IO_MemberSet(NRF_IO *pThis,
                      unsigned long ulPeriph,
                      unsigned long ulPort,
                      unsigned char ucPin)
{
  pThis->ulPeriph = ulPeriph;
  pThis->ulPort   = ulPort;
  pThis->ucPin    = ucPin;
}

void NRF_IO_Enable(NRF_IO *pThis)
{
  SysCtlPeriEnable(pThis->ulPeriph);
}

void NRF_IO_In(NRF_IO *pThis)
{
  GPIOPinTypeIn(pThis->ulPort,pThis->ucPin);
}

void NRF_IO_Out(NRF_IO *pThis)
{
  GPIOPinTypeOut(pThis->ulPort,pThis->ucPin);
}

unsigned char NRF_IO_Return(NRF_IO *pThis)
{
  if(GPIOPinRead(pThis->ulPort,pThis->ucPin) &(pThis->ucPin))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void NRF_IO_Set(NRF_IO *pThis)
{
  GPIOPinWrite(pThis->ulPort,pThis->ucPin,0xff);
}

void NRF_IO_Clr(NRF_IO *pThis)
{
  GPIOPinWrite(pThis->ulPort,pThis->ucPin,0x00);
}

void NRF_IO_Init(void)
{
  
  NRF_IO_MemberSet(&CE,
                   SYSCTL_PERIPH_GPIOA,
                   GPIO_PORTA_BASE,
                   GPIO_PIN_0);
  NRF_IO_MemberSet(&CSN,
                   SYSCTL_PERIPH_GPIOA,
                   GPIO_PORTA_BASE,
                   GPIO_PIN_6);
  NRF_IO_MemberSet(&IRQ,
                   SYSCTL_PERIPH_GPIOA,
                   GPIO_PORTA_BASE,
                   GPIO_PIN_1);
  
  NRF_IO_Enable(&CE);
  NRF_IO_Enable(&CSN);
  NRF_IO_Enable(&IRQ);
  NRF_IO_Out(&CE);
  NRF_IO_Out(&CSN);
  NRF_IO_In(&IRQ);
  
  GPIOIntTypeSet(IRQ.ulPort,
                 IRQ.ucPin,
                 GPIO_LOW_LEVEL);
  GPIOPinIntEnable(IRQ.ulPort,
                   IRQ.ucPin);
  IntEnable(INT_GPIOA);
  IntMasterEnable();
}

void ssiInit(void)
{
  unsigned long ulBitRate = TheSysClock / 8;
  SysCtlPeriEnable(SYSCTL_PERIPH_SSI0);
  
  SysCtlPeriEnable(SSI0CLK_PERIPH);
  SysCtlPeriEnable(SSI0FSS_PERIPH);
  SysCtlPeriEnable(SSI0RX_PERIPH);
  SysCtlPeriEnable(SSI0TX_PERIPH);
  
  GPIOPinTypeSSI(SSI0CLK_PORT,SSI0CLK_PIN);
  GPIOPinTypeSSI(SSI0FSS_PORT,SSI0FSS_PIN);
  GPIOPinTypeSSI( SSI0RX_PORT, SSI0RX_PIN);
  GPIOPinTypeSSI( SSI0TX_PORT, SSI0TX_PIN);
  
  SSIConfig(SSI0_BASE,
            SSI_FRF_MOTO_MODE_0,
            SSI_MODE_MASTER,
            ulBitRate,
            8);
  SSIEnable(SSI0_BASE);
}

void SPI_SendData(unsigned char *data, unsigned char num)
{
  for(unsigned char i=0;i<num;i++)
  {
    SSIDataPut(SSI0_BASE,data[i]);
  }
}

void SPI_GetData( unsigned char *data, unsigned char num)
{
  unsigned char i;
  unsigned long temp;
  for(i = 0; i<num;i++)
  {
    SSIDataGet(SSI0_BASE,&temp);
    *data = (unsigned char )temp;
    data++;
  }
}

//下面部分为原main中函数的实现部分
void init_io(void)
{
  ssiInit();
  LedInit();
  NRF_IO_Init();
  NRF_IO_Clr(&CE);
  NRF_IO_Set(&CSN);
}

uchar SPI_RW(uchar byte)
{
  uchar bit_ctr;
  unsigned long temp;
  SSIDataPut(SSI0_BASE,byte);
  SSIDataGet(SSI0_BASE,&temp);
  bit_ctr = (unsigned char)temp;
  return (bit_ctr);
}

uchar SPI_RW_Reg(BYTE reg,BYTE value)
{
  uchar status;
  
  NRF_IO_Clr(&CSN);
  status = SPI_RW(reg);
  SPI_RW(value);
  NRF_IO_Set(&CSN);
  
  return (status);
}

BYTE SPI_Read(BYTE reg)
{
  BYTE reg_val;
  NRF_IO_Clr(&CSN);
  SPI_RW(reg);
  reg_val = SPI_RW(0);
  NRF_IO_Set(&CSN);
  
  return reg_val;
}

uchar SPI_Read_Buf(BYTE reg,BYTE *pBuf, BYTE bytes)
{
  uchar status,byte_ctr;
  NRF_IO_Clr(&CSN);
  status = SPI_RW(reg);
  
  for(byte_ctr = 0;byte_ctr<bytes;byte_ctr++)
  {
    pBuf[byte_ctr]=SPI_RW(0);
  }
  
  NRF_IO_Set(&CSN);
  return status;
}

uchar SPI_Write_Buf(BYTE reg,BYTE *pBuf,BYTE bytes)
{
  uchar status,byte_ctr;
  NRF_IO_Clr(&CSN);
  status = SPI_RW(reg);
  
  for(byte_ctr=0;byte_ctr<bytes;byte_ctr++)
  {
    SPI_RW(*pBuf++);
  }
  NRF_IO_Set(&CSN);
  return status;
}

void RX_Mode(void)
{
  NRF_IO_Clr(&CE);
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
  SPI_RW_Reg(WRITE_REG + EN_AA    ,0x01);
  SPI_RW_Reg(WRITE_REG + EN_RXADDR,0x01);
  SPI_RW_Reg(WRITE_REG + RF_CH    ,40);
  SPI_RW_Reg(WRITE_REG + RX_PW_P0 ,TX_PLOAD_WIDTH);
  SPI_RW_Reg(WRITE_REG + RF_SETUP ,0x07);
  SPI_RW_Reg(WRITE_REG + CONFIG   ,0x0f);
  NRF_IO_Set(&CE);
  
}


void TX_Mode(char x)
{
  int i;
  for(i = 0;i< 10 ;i++)
  {
    tx_buf[i] = x;
  }
  tx_buf[i] = '\0';
  
  NRF_IO_Clr(&CE);
  SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0,TX_ADDRESS, TX_ADR_WIDTH);
  SPI_Write_Buf(WR_TX_PLOAD, tx_buf,TX_PLOAD_WIDTH);
  
  SPI_RW_Reg(WRITE_REG + EN_AA      , 0x01);
  SPI_RW_Reg(WRITE_REG + EN_RXADDR  , 0x01);
  SPI_RW_Reg(WRITE_REG + SETUP_RETR , 0x1a);
  SPI_RW_Reg(WRITE_REG + RF_CH      , 40  );
  SPI_RW_Reg(WRITE_REG + RF_SETUP   , 0x07);
  SPI_RW_Reg(WRITE_REG + CONFIG     , 0x0e);
  NRF_IO_Set(&CE);
}
//中断服务函数,进行数据发送成功与否的判断
void GPIO_Port_A_ISR(void)
{
  unsigned long ulStatus;
  ulStatus = GPIOPinIntStatus(IRQ.ulPort,true);
  
  if(ulStatus & IRQ.ucPin)
  {
    sta = SPI_Read(STATUS);
    //如果发送成功
    if(TX_DR)
    {
      LedOn();//发送端的灯亮
    }
    //如果自动重发次数超过编程的最大值
    if(MAX_RT)
    {
      LedOn();//发送端的灯亮
      SPI_RW_Reg(FLUSH_TX,0);//清空发送缓冲区的内容
    }
    SPI_RW_Reg(WRITE_REG + STATUS, sta);//将原来的状态清除
  }
}


//其它部分函数的实现部分
void LedInit(void)
{
  SysCtlPeriEnable(SYSCTL_PERIPH_GPIOG);
  GPIOPinTypeOut(GPIO_PORTG_BASE,GPIO_PIN_2);
  GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,0xff);
}

void LedOn(void)
{
  GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,0x00);
}

void LedOff(void)
{
  GPIOPinWrite(GPIO_PORTG_BASE,GPIO_PIN_2,0xff);
}  