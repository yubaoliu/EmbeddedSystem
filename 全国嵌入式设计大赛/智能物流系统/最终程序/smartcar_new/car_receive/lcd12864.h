#include  "systemInit.h"
//define LCD 12864 ports 
#define  LCD_PERIPH            SYSCTL_PERIPH_GPIOB
#define  LCD_PORT               GPIO_PORTB_BASE

#define  LCD_DIO                GPIO_PIN_1
#define  LCD_CLK                GPIO_PIN_2
#define  LCD_PSB                GPIO_PIN_3
#define  LCD_RST                GPIO_PIN_4
#define  E_PERIPH            SYSCTL_PERIPH_GPIOE
#define  E_PORT               GPIO_PORTE_BASE
#define  LCD_CS                 GPIO_PIN_0
//functions declaration of lcd12864.c
void lcdInit(void);
void clearAll(void);
void lcdComdWrite(unsigned int command);
void lcdDataWrite(unsigned int data);
void lcdByteWrite(unsigned int bytename);
void lcdSetPos(char X,char Y);
void lcdWriteStr(char X,char Y,char *String);
void lcdPictureOn(void);
void lcdPictureOff(void);
void lcdGdramAddress(unsigned int  VerticalAddr,unsigned int  HorizontalAddr);
void lcdPowerOnPictureInitDisplay(void);
///////////////////////

void display1(void);
void display2(void);
void display3(void);

