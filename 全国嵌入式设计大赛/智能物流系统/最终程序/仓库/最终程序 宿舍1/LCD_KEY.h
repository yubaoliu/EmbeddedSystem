//  包含头文件
#ifndef  __LCD_KEY_H__
#define  __LCD_KEY_H__

#include "hw_memmap.h"
#include "hw_types.h"
#include "sysctl.h"
#include "gpio.h"
#include  <hw_sysctl.h>
#include  <hw_gpio.h>

//  Date types(Compiler specific)  数据类型（和编译器相关）
typedef unsigned char  uint8;                               //  Unsigned  8 bit quantity
                                                            //  无符号8位整型变量
typedef signed   char  int8;                                //  Signed    8 bit quantity
                                                            //  有符号8位整型变量
typedef unsigned short uint16;                              //  Unsigned 16 bit quantity
                                                            //  无符号16位整型变量
typedef signed   short int16;                               //  Signed   16 bit quantity
                                                            //  有符号16位整型变量
typedef unsigned int   uint32;                              //  Unsigned 32 bit quantity
                                                            //  无符号32位整型变量
typedef signed   int   int32;                               //  Signed   32 bit quantity
                                                            //  有符号32位整型变量
typedef float           fp32;                               //  Single precision floating point
                                                            //  单精度浮点数（32位长度
typedef double          fp64;                               //  Double precision floating point
                                                            //  双精度浮点数（64位长度）
//  定义控制信号
#define  LCD_KEY_PERIPH             SYSCTL_PERIPH_GPIOE
#define  LCD_KEY_PORT               GPIO_PORTE_BASE
#define  LCD_KEY_CS                 GPIO_PIN_0
#define  LCD_KEY_CLK                GPIO_PIN_1
#define  LCD_KEY_DIO                GPIO_PIN_2
#define  LCD_KEY_KEY                GPIO_PIN_3

extern void __delayNuS(int32 iTime);                        //  延迟函数

//  将较长的标识符定义成较短的形式
#define  SysCtlPeriEnable       SysCtlPeripheralEnable
#define  SysCtlPeriDisable      SysCtlPeripheralDisable
#define  GPIOPinTypeIn          GPIOPinTypeGPIOInput
#define  GPIOPinTypeOut         GPIOPinTypeGPIOOutput
#define  GPIOPinTypeOD          GPIOPinTypeGPIOOutputOD


//  ZLG7289可以供外部使用的函数申明
extern void zlg7289Cmd(int8  cCmd);                         //  执行ZLG7289 纯指令
extern void zlg7289CmdDat(uint8  cCmd, int8  cDat);         //  执行ZLG7289 带数据指令
extern void zlg7289Download(uint8 ucMod, int8 cX, int8 cDp, int8 cDat);
                                                            //  下载数据
extern int8 zlg7289Key(void);                               //  读按键值
extern void zlg7289Init(void);                              //  ZLG7289 初始化

//  ZLG7289用户指令集
#define zlg7289Reset()      zlg7289Cmd(0xA4)                //  复位(清除)指令
#define zlg7289Test()       zlg7289Cmd(0xBF)                //  测试指令
#define zlg7289SHL()        zlg7289Cmd(0xA0)                //  左移指令
#define zlg7289SHR()        zlg7289Cmd(0xA1)                //  右移指令
#define zlg7289ROL()        zlg7289Cmd(0xA2)                //  循环左移指令
#define zlg7289ROR()        zlg7289Cmd(0xA3)                //  循环右移指令

#define zlg7289Flash(cX)    zlg7289CmdDat(0x88, (cX))       //  闪烁控制
                                                            //  cX的8个位对应数码管的8个位
                                                            //  0:闪烁  1:不闪烁

#define zlg7289Hide(cX)     zlg7289CmdDat(0x98, (cX))       //  消隐控制
                                                            //  cX的8个位对应数码管的8个位
                                                            //  0:消隐  1:显示

#define zlg7289SegOn(cSeg)  zlg7289CmdDat(0xE0, (cSeg))     //  段点亮指令
                                                            //  8个数码管被看成64个独立LED
                                                            //  cSeg: 0 ～ 63

#define zlg7289SegOff(cSeg) zlg7289CmdDat(0xC0, (cSeg))     //  段关闭指令
                                                            //  8个数码管被看成64个独立LED
                                                            //  cSeg: 0 ～ 63

#endif
