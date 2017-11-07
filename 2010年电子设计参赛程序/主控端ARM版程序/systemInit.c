#include  "systemInit.h"


//  ����ȫ�ֵ�ϵͳʱ�ӱ���
unsigned long TheSysClock = 12000000UL;


//  ����KEY
#define  KEY_PERIPH             SYSCTL_PERIPH_GPIOG
#define  KEY_PORT               GPIO_PORTG_BASE
#define  KEY_PIN                GPIO_PIN_5


//  ��ֹJTAGʧЧ
void jtagWait(void)
{
    SysCtlPeriEnable(KEY_PERIPH);                           //  ʹ��KEY���ڵ�GPIO�˿�
    GPIOPinTypeIn(KEY_PORT, KEY_PIN);                       //  ����KEY���ڹܽ�Ϊ����

    if (GPIOPinRead(KEY_PORT, KEY_PIN) == 0x00)             //  ����λʱ����KEY�������
    {
        for (;;);                                           //  ��ѭ�����Եȴ�JTAG����
    }

    SysCtlPeriDisable(KEY_PERIPH);                          //  ��ֹKEY���ڵ�GPIO�˿�
}


//  ϵͳʱ�ӳ�ʼ��
void clockInit(void)
{
    SysCtlLDOSet(SYSCTL_LDO_2_50V);                         //  ����LDO�����ѹ

    SysCtlClockSet(SYSCTL_USE_OSC |                         //  ϵͳʱ������
                   SYSCTL_OSC_MAIN |                        //  ����������
                   SYSCTL_XTAL_6MHZ |                       //  ���6MHz����
                   SYSCTL_SYSDIV_1);                        //  ����Ƶ

/*
    SysCtlLDOSet(SYSCTL_LDO_2_75V);                         //  ����PLLǰ�뽫LDO��Ϊ2.75V

    SysCtlClockSet(SYSCTL_USE_PLL |                         //  ϵͳʱ�����ã�����PLL
                   SYSCTL_OSC_MAIN |                        //  ������
                   SYSCTL_XTAL_6MHZ |                       //  ���6MHz����
                   SYSCTL_SYSDIV_10);                       //  ��Ƶ���Ϊ20MHz
*/

    TheSysClock = SysCtlClockGet();                         //  ��ȡ��ǰ��ϵͳʱ��Ƶ��
}

