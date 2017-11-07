#include  "uartGetPut.h"
#include  <hw_types.h>
#include  <hw_memmap.h>
#include  <sysctl.h>
#include  <gpio.h>
#include  <uart.h>
#include  <ctype.h>


#define  SysCtlPeriEnable       SysCtlPeripheralEnable


//  UART��ʼ��
void uartInit(void)
{
    SysCtlPeriEnable(SYSCTL_PERIPH_UART2);                  //  ʹ��UARTģ��
    SysCtlPeriEnable(SYSCTL_PERIPH_GPIOG);                  //  ʹ��RX/TX���ڵ�GPIO�˿�

    GPIOPinTypeUART(GPIO_PORTG_BASE,                        //  ����RX/TX���ڹܽ�Ϊ
                    GPIO_PIN_0 | GPIO_PIN_1);               //  UART�շ�����

    UARTConfigSet(UART2_BASE,                               //  ����UART�˿�
                  9600,                                     //  �����ʣ�9600
                  UART_CONFIG_WLEN_8 |                      //  ����λ��8
                  UART_CONFIG_STOP_ONE |                    //  ֹͣλ��1
                  UART_CONFIG_PAR_NONE);                    //  У��λ����

    UARTEnable(UART2_BASE);                                 //  ʹ��UART�˿�
}


//  ͨ��UART����һ���ַ�
void uartPutc(const char c)
{
    UARTCharPut(UART2_BASE, c);
}


//  ͨ��UART�����ַ���
void uartPuts(const char *s)
{
    while (*s != '\0') uartPutc(*(s++));
}


//  ͨ��UART����һ���ַ�
char uartGetc(void)
{
    return(UARTCharGet(UART2_BASE));
}


//  ���ܣ�ͨ��UART�����ַ��������ԣ��˸�<Backspace>�޸ģ��س�<Enter>����
//  ������*s����������ݵĻ�������ֻ���տɴ�ӡ�ַ���ASCII��32��127��
//        size�ǻ�����*s���ܳ��ȣ�Ҫ��size >= 2������ĩβ'\0'��������sizeof()����ȡ��
//  ���أ����յ�����Ч�ַ���Ŀ
int uartGets(char *s, int size)
{
    char c;
    int n = 0;

    *s = '\0';
    if (size < 2) return(0);
    size--;

    for (;;)
    {
        c = uartGetc();                                     //  ����1���ַ�
        uartPutc(c);                                        //  ����������ַ�

        if (c == '\b')                                      //  ���˸�<Backspace>�޸�
        {
            if (n > 0)
            {
                *(--s) = '\0';
                n--;
                uartPuts(" \b");                            //  ��ʾ�ո���˸�<Backspace>
            }
        }

        if (c == '\r')                                      //  ���س�<Enter>����
        {
            uartPuts("\r\n");                               //  ��ʾ�س�����<CR><LF>
            break;
        }

        if (n < size)                                       //  ���С�ڳ�������
        {
            if (isprint(c))                                 //  ������յ����ǿɴ�ӡ�ַ�
            {
                *(s++) = c;                                 //  ������յ����ַ���������
                *s = '\0';
                n++;
            }
        }
    }

    return(n);                                              //  ���ؽ��յ�����Ч�ַ���Ŀ
}

