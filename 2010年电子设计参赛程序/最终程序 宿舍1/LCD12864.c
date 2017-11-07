#include "lcd12864.h"

void lcdInit(void)
{
  SysCtlPeriEnable(LCD_PERIPH);  //enable GPIOB port 
  GPIOPinTypeOut(LCD_PORT,LCD_CS);   //Set the corresponding pin as an output
  GPIOPinTypeOut(LCD_PORT,LCD_CLK);
  GPIOPinTypeOut(LCD_PORT,LCD_DIO);
  GPIOPinTypeOut(LCD_PORT,LCD_RST);
  GPIOPinTypeOut(LCD_PORT,LCD_PSB);
  GPIOPinWrite(LCD_PORT,LCD_RST,0xff);// disable RST
  GPIOPinWrite(LCD_PORT,LCD_PSB,0x00);//serial mode
  lcdComdWrite(0x30);               //   Feature set, the basic instructions 
  lcdComdWrite(0x30);               //   the basic instruction,8-bit model,the basic instruction
  lcdComdWrite(0x0c);               //Show open, cursor off, anti-white off
  lcdComdWrite(0x01);               //clear show
  lcdComdWrite(0x06);               //go into the set point，the curser shift to the right，the picture does not move
  
}
//clear all 
void clearAll(void)
{
  lcdComdWrite(0x01);
  SysCtlDelay(200*(TheSysClock/3000));
}
//write command to the LCM
void lcdComdWrite(unsigned int command)
{
  GPIOPinWrite(LCD_PORT,LCD_CS,0xff);
  lcdByteWrite(0xf8);
  lcdByteWrite(command&0xf0);        //write high 4-bits 
  command<<=4;
  lcdByteWrite(command&0xf0);       //write low 4-bits
}
//write data to the lcm
void lcdDataWrite(unsigned int data)  //write one byte
{
  GPIOPinWrite(LCD_PORT,LCD_CS,0xff);
  lcdByteWrite(0xfa);
  lcdByteWrite(data&0xf0);
  data<<=4;
  lcdByteWrite(data&0xf0);
}
//write a byte to the lcm
void lcdByteWrite(unsigned int bytename)  //how to write one byte to the lcm
{
  unsigned int i,dat;
  for(i=0;i<8;i++)
  {
    GPIOPinWrite(LCD_PORT,LCD_CLK,0x00);
    SysCtlDelay(5*(TheSysClock/3000000));
    dat=bytename&0x80;
    if(dat)
    {
      GPIOPinWrite(LCD_PORT,LCD_DIO,0xff);  //write 1
    }
    else
    {
      GPIOPinWrite(LCD_PORT,LCD_DIO,0x00);  //write 0
    }
    bytename<<=1;
    GPIOPinWrite(LCD_PORT,LCD_CLK,0xff);
    SysCtlDelay(5*(TheSysClock/3000000));
  }
}
//set X, y position to display
void lcdSetPos(char X,char Y)  //X--row 1--4   Y-collum 1--16
{
  unsigned char sendchar;
  switch(X)
  {
  case 1: sendchar=0x80+Y-1; break;   //设定DDRAM位址到地址寄存器AC
  case 2: sendchar=0x90+Y-1; break;
  case 3: sendchar=0x88+Y-1; break;
  case 4: sendchar=0x98+Y-1; break;
  default : sendchar=0x80+Y-1;
  break;
  }
  lcdComdWrite(sendchar);
}
                                               //write string to the lcm this functon is very important: every Chinese character must execut the cycle two times
void lcdWriteStr(char X,char Y,char *string)   //note that "charcode" is char type 8-bits
{
     unsigned int count=0;	
     char temp=0x00;                            //It's best to give "temp count" initial value
     unsigned char charcode;
     lcdSetPos(X,Y);  
     switch(X)
     {
      case 1: temp=0x00+Y*2-2; break;          //temp line1 00--0Fh  line2 10--1Fh 
      case 2: temp=0x10+Y*2-2; break;
      case 3: temp=0x20+Y*2-2; break;
      case 4: temp=0x30+Y*2-2; break;
     }
      while(1)
      {
        charcode = *string++;
        if(charcode == '\0') break;
        if(charcode <=0x7e && charcode >= 0x20)     //ASCII 02--7Fh is character the othes are chinese characters
        {
           count++;                                 //used for decide whether the number of characters are odd or even if even write a space before Chinese characters
        }
        else if(count%2==0)
         {
           count=0;
         }
        else
        {
          lcdDataWrite(0x20);
          temp++;                        //After write a space，add the address，re-check whether it need to change line
          if(temp==0x10)
          {
            lcdComdWrite(0x90);          //the second line
          }
          else
            if(temp==0x20)
            {
              lcdComdWrite(0x88);
            }
          else if(temp==0x30)
          {
            lcdComdWrite(0x98);
          }
           count=0;
        } 
        lcdDataWrite(charcode);  //one time write one byte, a Chinese character need write two times   if(temp == 0x0F)
        if(temp==0x0F)
        {
            temp = 0x10;    //the second line
            lcdSetPos(2,1);
        }
        else if(temp==0x1F)
        {
           temp = 0x20;       //the third line
           lcdSetPos(3,1);    //the same as lcdComdWrite();
        }
         else if(temp==0x2F)
        {
           temp =0x30;         // the fourth line
           lcdSetPos(4,1);
        }
        else 
          temp++;
      }   
     
     
     SysCtlDelay(100*(TheSysClock/3000));
     
}
//  open display 
void lcdPictureOn(void)
{
    lcdComdWrite(0x34);                                    //  Expand instruction
    lcdComdWrite(0x36);                                     //graph enable
    lcdComdWrite(0x30);                                    //  Base instruction
}

//  关闭图片显示功能
void lcdPictureOff(void)
{
	lcdComdWrite(0x34);                                       //  Expand instruction
	lcdComdWrite(0x30);                                       //Base instruction
	lcdComdWrite(0x30);                                       //  write two times

}

void lcdGdramAddress(unsigned int  VerticalAddr,unsigned int  HorizontalAddr)
{
        VerticalAddr &= 0x1F;
        HorizontalAddr &= 0x0F;
	lcdComdWrite(0x34);                             //  Expand instruction G is 0 graph disable
	lcdComdWrite(VerticalAddr|0x80);
	lcdComdWrite(HorizontalAddr|0x80);
	lcdComdWrite(0x30);                                       //  Base instruction
}
