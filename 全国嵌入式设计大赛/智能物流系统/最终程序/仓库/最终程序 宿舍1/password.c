#include "password.h"
#include "LCD_KEY.h"
#include "lcd12864.h"
char password[2]={'0','1'};
//�趨������
/*
void setPassWord(char key)
{
  //char newpwd[2];
  int i=0;
  tBoolean f=true;
  while(f)
  {
   // if(key=='o')
     //{
       
       f=false; 
       lcdWriteStr(1,1,"�����趨�ɹ�");//�����趨�ɹ�
       SysCtlDelay(100*(TheSysClock/3000));
    // }
    else
    {
     password[i]=key;
   //  newpwd[i++]=key;    
     lcdWriteStr(2,i,"*");
    }
    i++;
  }
}*/

//��������
tBoolean CheckPwd(char *psw)
{
  //char *str;
 // char pd=0;//save password
    
  tBoolean isPwdRight=true;//analyse Pwd right or wrong
   for(int i=0;i<2;i++)
   {
      if(psw[i]!=password[i])
        {
           isPwdRight=false;
        }
   }
       
    if(isPwdRight)
    {
       lcdWriteStr(3,1,"������ȷ");//������ȷ
       SysCtlDelay(1000*(TheSysClock/3000));
     }
      else
      {
        lcdWriteStr(3,1,"�������");//�������
        SysCtlDelay(1000*(TheSysClock/3000));
      }
         
  /*  else
    {
     pd[i++]=key;
     str="*";//&key;
     lcdWriteStr(1,i,str);//output *
    }*/
 // }
    return isPwdRight;
}