#include "LCD_KEY.h"
#include  "systemInit.h"

//  ��ʱN��΢�� 
void __delayNuS (int32 iTime)
{
    iTime = SysCtlClockGet() * iTime / 2000000;             //  ����ϵͳʱ������ȷ����ʱ
    while (--iTime != 0);
}

//  ��SPI ����д��1 ���ֽڵ����ݡ�
void __zlg7289SPIWrite (int8 cDat)
{
    int8 cT = 8;
    GPIOPinTypeOut( LCD_KEY_PORT , LCD_KEY_DIO);            //  ����DIO�˿�Ϊ���ģʽ
    
    do
    {                                                       //  ѭ��дһ���ֽڵ�����
        if((cDat & 0x80) == 0x80)
        {
            GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_DIO, 0xff);
        } 
        else 
        {
            GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_DIO, 0x00);
        }

        cDat <<= 1;
        GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CLK, 0xff);
        __delayNuS(5);
        GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CLK, 0x00);
        __delayNuS(5);

    } while (--cT != 0);
}
 
//  ��SPI ���߶�ȡ1 ���ֽڵ�����
int8 __zlg7289SPIRead (void)
{
    int8 cDat = 0;
    int8 cT   = 8;
    GPIOPinTypeIn( LCD_KEY_PORT, LCD_KEY_DIO);              //  ����DIO�˿�Ϊ���ģʽ

    do
    {                                                       //  ѭ����һ���ֽڵ�����
        GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CLK, 0xff);
        __delayNuS(5);
        cDat <<= 1;

        if (GPIOPinRead( LCD_KEY_PORT , LCD_KEY_DIO)) 
        {
            cDat++;
        }

        GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CLK, 0x00);
        __delayNuS(5);

    } while (--cT != 0);

    return (cDat);
}

//  ִ��ZLG7289 ��ָ�
void zlg7289Cmd (int8  cCmd)
{
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0x00);
    __delayNuS(25);
    __zlg7289SPIWrite(cCmd);
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0xff);
    __delayNuS(5);
}

//  ִ��ZLG7289 ������ָ�
void zlg7289CmdDat (uint8  cCmd, int8  cDat)
{
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0x00);
    __delayNuS(25);
    __zlg7289SPIWrite(cCmd);
    __delayNuS(15);
    __zlg7289SPIWrite(cDat);
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0xff);
    __delayNuS(5);
}

//  �������ݡ�
//  ucMod=0�� ���������Ұ���ʽ0 ����
//  ucMod=1�� ���������Ұ���ʽ1 ����
//  ucMod=2�� �������ݵ�������
//  cX��      ����ܱ�ţ������꣩��ȡֵ0��7
//  cDp=0��   С���㲻��
//  cDp=1��   С������
//  cDat��    Ҫ��ʾ������ 
void zlg7289Download (uint8  ucMod, int8  cX, int8  cDp, int8  cDat)
{
    uint8 ucModDat[3] = {0x80,0xC8,0x90};
    uint8 ucD1;
    uint8 ucD2;

    if (ucMod > 2) 
    {
        ucMod = 2;
    }

    ucD1  = ucModDat[ucMod];
    cX   &= 0x07;
    ucD1 |= cX;
    ucD2  = cDat & 0x7F;

    if (cDp  == 1) 
    {
        ucD2 |= 0x80;
    }

    zlg7289CmdDat(ucD1, ucD2);
}

//  ִ��ZLG7289 �������
//  ���ض����İ���ֵ��0��63���������0xFF ���ʾû�м�����
int8 zlg7289Key (void)
{
    int8 cKey;
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0x00);
    __delayNuS(25);
    __zlg7289SPIWrite(0x15);
    __delayNuS(15);
    cKey = __zlg7289SPIRead();
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS, 0xff);
    __delayNuS(5);

    return (cKey);
}

//  ZLG7289 ��ʼ��
void zlg7289Init (void)
{
    SysCtlPeripheralEnable( LCD_KEY_PERIPH );               //  ʹ��GPIO B������

    GPIOPinTypeIn( LCD_KEY_PORT , LCD_KEY_KEY);             //  ����KEY�˿�Ϊ����
    GPIOIntTypeSet( LCD_KEY_PORT , LCD_KEY_KEY, GPIO_FALLING_EDGE);
                                                            //  ���������½��ش����ж�
    GPIOPinIntEnable( LCD_KEY_PORT , LCD_KEY_KEY);          //  ʹ�����������ж�
    IntEnable(INT_GPIOE);   
    
                                    //  ʹ��GPIO PE���ж�

    GPIOPinTypeOut( LCD_KEY_PORT , LCD_KEY_CS |LCD_KEY_CLK |LCD_KEY_DIO);     
                                                            //  ����I/O��Ϊ���ģʽ
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_DIO, 0xff);
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CLK, 0x00);
    GPIOPinWrite( LCD_KEY_PORT , LCD_KEY_CS , 0xff);

    zlg7289Reset();                                         //  ��λZLG7289
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
