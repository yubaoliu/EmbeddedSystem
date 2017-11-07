#ifndef  __UART_GET_PUT_H__
#define  __UART_GET_PUT_H__


//  UART��ʼ��
extern void uartInit(void);

//  ͨ��UART����һ���ַ�
extern void uartPutc(const char c);

//  ͨ��UART�����ַ���
extern void uartPuts(const char *s);

//  ͨ��UART����һ���ַ�
extern char uartGetc(void);

//  ͨ��UART�����ַ��������ԣ��˸�<Backspace>�޸ģ��س�<Enter>����
extern int uartGets(char *s, int size);


#endif  //  __UART_GET_PUT_H__

