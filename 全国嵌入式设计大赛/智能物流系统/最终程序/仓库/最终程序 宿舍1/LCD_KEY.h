//  ����ͷ�ļ�
#ifndef  __LCD_KEY_H__
#define  __LCD_KEY_H__

#include "hw_memmap.h"
#include "hw_types.h"
#include "sysctl.h"
#include "gpio.h"
#include  <hw_sysctl.h>
#include  <hw_gpio.h>

//  Date types(Compiler specific)  �������ͣ��ͱ�������أ�
typedef unsigned char  uint8;                               //  Unsigned  8 bit quantity
                                                            //  �޷���8λ���ͱ���
typedef signed   char  int8;                                //  Signed    8 bit quantity
                                                            //  �з���8λ���ͱ���
typedef unsigned short uint16;                              //  Unsigned 16 bit quantity
                                                            //  �޷���16λ���ͱ���
typedef signed   short int16;                               //  Signed   16 bit quantity
                                                            //  �з���16λ���ͱ���
typedef unsigned int   uint32;                              //  Unsigned 32 bit quantity
                                                            //  �޷���32λ���ͱ���
typedef signed   int   int32;                               //  Signed   32 bit quantity
                                                            //  �з���32λ���ͱ���
typedef float           fp32;                               //  Single precision floating point
                                                            //  �����ȸ�������32λ����
typedef double          fp64;                               //  Double precision floating point
                                                            //  ˫���ȸ�������64λ���ȣ�
//  ��������ź�
#define  LCD_KEY_PERIPH             SYSCTL_PERIPH_GPIOE
#define  LCD_KEY_PORT               GPIO_PORTE_BASE
#define  LCD_KEY_CS                 GPIO_PIN_0
#define  LCD_KEY_CLK                GPIO_PIN_1
#define  LCD_KEY_DIO                GPIO_PIN_2
#define  LCD_KEY_KEY                GPIO_PIN_3

extern void __delayNuS(int32 iTime);                        //  �ӳٺ���

//  ���ϳ��ı�ʶ������ɽ϶̵���ʽ
#define  SysCtlPeriEnable       SysCtlPeripheralEnable
#define  SysCtlPeriDisable      SysCtlPeripheralDisable
#define  GPIOPinTypeIn          GPIOPinTypeGPIOInput
#define  GPIOPinTypeOut         GPIOPinTypeGPIOOutput
#define  GPIOPinTypeOD          GPIOPinTypeGPIOOutputOD


//  ZLG7289���Թ��ⲿʹ�õĺ�������
extern void zlg7289Cmd(int8  cCmd);                         //  ִ��ZLG7289 ��ָ��
extern void zlg7289CmdDat(uint8  cCmd, int8  cDat);         //  ִ��ZLG7289 ������ָ��
extern void zlg7289Download(uint8 ucMod, int8 cX, int8 cDp, int8 cDat);
                                                            //  ��������
extern int8 zlg7289Key(void);                               //  ������ֵ
extern void zlg7289Init(void);                              //  ZLG7289 ��ʼ��

//  ZLG7289�û�ָ�
#define zlg7289Reset()      zlg7289Cmd(0xA4)                //  ��λ(���)ָ��
#define zlg7289Test()       zlg7289Cmd(0xBF)                //  ����ָ��
#define zlg7289SHL()        zlg7289Cmd(0xA0)                //  ����ָ��
#define zlg7289SHR()        zlg7289Cmd(0xA1)                //  ����ָ��
#define zlg7289ROL()        zlg7289Cmd(0xA2)                //  ѭ������ָ��
#define zlg7289ROR()        zlg7289Cmd(0xA3)                //  ѭ������ָ��

#define zlg7289Flash(cX)    zlg7289CmdDat(0x88, (cX))       //  ��˸����
                                                            //  cX��8��λ��Ӧ����ܵ�8��λ
                                                            //  0:��˸  1:����˸

#define zlg7289Hide(cX)     zlg7289CmdDat(0x98, (cX))       //  ��������
                                                            //  cX��8��λ��Ӧ����ܵ�8��λ
                                                            //  0:����  1:��ʾ

#define zlg7289SegOn(cSeg)  zlg7289CmdDat(0xE0, (cSeg))     //  �ε���ָ��
                                                            //  8������ܱ�����64������LED
                                                            //  cSeg: 0 �� 63

#define zlg7289SegOff(cSeg) zlg7289CmdDat(0xC0, (cSeg))     //  �ιر�ָ��
                                                            //  8������ܱ�����64������LED
                                                            //  cSeg: 0 �� 63

#endif
