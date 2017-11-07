/*
*/
#ifndef _NRF24L01_H__
#define _NRF24L01_H__

//定义测试用管脚
#define KEY_PERIPH   SYSCLT_PERIPH_GPIOG
#define KEY_PORT     GPIO_PORTG_BASE
#define KEY_PIN      GPIO_PIN_5
/*
   数据类型定义
*/
typedef unsigned char BYTE;
#define uchar unsigned char
#define TX_ADR_WIDTH   5
#define TX_PLOAD_WIDTH 20


#define RX_DR  (sta&0x40)
#define TX_DR  (sta&0x20)
#define MAX_RT (sta&0x10)

//****************************************************************//
/*
   NRF24L01的控制字节
*/
// SPI(nRF24L01) commands
#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register

//***************************************************//
/*
   NRF24L01的寄存器地址
*/
// SPI(nRF24L01) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

//***************************************************************//
/*
    对NRF24L01的基本操作部分
*/
//***************************************************************//
//                   FUNCTION's PROTOTYPES  //
/****************************************************************/
 void SPI_Init(BYTE Mode);     // Init HW or SW SPI
 BYTE SPI_RW(BYTE byte);                                // Single SPI read/write
 BYTE SPI_Read(BYTE reg);                               // Read one byte from nRF24L01
 BYTE SPI_RW_Reg(BYTE reg, BYTE byte);                  // Write one byte to register 'reg'
 BYTE SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);  // Writes multiply bytes to one register
 BYTE SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);   // Read multiply bytes from one register
//*****************************************************************/


 
 typedef struct
 {
   unsigned long ulPeriph;
   unsigned long ulPort;
   unsigned char ucPin;
 }NRF_IO;
 
 void NRF_IO_MemberSet(NRF_IO *pThis, 
                              unsigned long ulPeriph,
                              unsigned long ulPort,
                              unsigned char ucPin);
 void NRF_IO_Enable(NRF_IO *pThis);
 void NRF_IO_In(NRF_IO *pThis);
 void NRF_IO_Out(NRF_IO *pThis);
 unsigned char NRF_IO_Return(NRF_IO *pThis);
 void NRF_IO_Set(NRF_IO *pThis);
 void NRF_IO_Clr(NRF_IO *pThis);
 void NRF_IO_Init(void);

 //与SSI相关的操作
 void ssiInit(void);
 void SPI_SendData(unsigned char *data, unsigned char Num);
 void SPI_GetData(unsigned char *data, unsigned char Num);

//在主函数中实现的部分
  void  init_io(void);
  void  delay100(void);
  void  delay_ms(unsigned int x);
  uchar SPI_RW(uchar byte);
  uchar SPI_RW_Reg(BYTE reg,BYTE value);
  BYTE  SPI_Read(BYTE reg);
  uchar SPI_Read_Buf(BYTE  reg,BYTE *pBuf,BYTE bytes);
  uchar SPI_Write_Buf(BYTE reg,BYTE *pBuf,BYTE bytes);
  void  RX_Mode(void);
  void  TX_Mode(char x);
  void  Check_ACK(void);
  void  CheckButtons(void);
  void  GPIO_PortA_ISR(void);
  void  GPIO_PortG_ISR(void);
  void  GPIO_PortD_ISR(void);
  
  
  //其它的函数部分
  void LedInit(void);
  void LedOn(void);
  void LedOff(void);
 void Action(void);
  void KeyInit(void);
 
#endif//_NRF24L01_H__