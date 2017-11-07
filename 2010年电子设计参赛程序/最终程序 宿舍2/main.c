//  包含必要的头文件
#include  "systemInit.h"
#include  "lcd12864.h"
#include  <stdio.h>
#include  "LCD_KEY.h"
#include  "uartGetPut.h"
#include  "tick.h"
#include "password.h"
#include "setMode.h"
#include <hw_types.h>
#include  <systick.h> 
#include "human.h"
#include "mq.h"
#include "count.h"
#include "NRF24L01.h"
#include "temp.h"
#include "melt.h"

#define OK 18

//本机地址
char SourceAddress[3] = {'0','0','2'};
//目的地址
char TargetAddress[3] = {'0','0','0'};

//时间设定参数
char date[2]={2,5};
char hour[2]={1,4};
char minute[2]={4,0};
char second[2]={2,3};

//  定义显示字符指针
char *line1;
char show=0;   //使程序仅显示一次
char show1=0;//
uint8 ucKey=0xff;
int flag = 0;//默认进入初始界面
int pressKeyCount=-1;//第几次按键
tBoolean hasPrintOnce = false;
char psw[2];
extern int count;
extern char FoundThief;
extern char FoundFire;

uchar presence;
char temp[10];

//  字符表(映射对应的按键图标)
uint8 code[20] = 
{
    48,49,50,51,52,53,54,55,56,57,                          //  48~57 -> 0~9
    42,35,25,27,67,60,26,24,79,62                           //  42,35 -> *,#
};                                                          //  24,25,26,27 -> 上，下，左，右    13-left 16-right                                                        //  67,79 -> 取消，确认                                                          //  60,62 -> F1,F2功能选择 ?"??

void Alarm();

//  端口B中断服务函数
void GPIO_Port_E_ISR(void)
{
    uint8 ucIntStatus;  
  //  uint8 ucKey;
  
    ucIntStatus = GPIOPinIntStatus( LCD_KEY_PORT , 1);      //  读PA口中断状态???

    if(ucIntStatus & LCD_KEY_KEY)                           //  判断是否为按键中断
        {
            GPIOPinIntClear( LCD_KEY_PORT , LCD_KEY_KEY);   //  清中断
            ucKey = zlg7289Key();                           //  读按键值
            pressKeyCount++;
            if (ucKey != 0xff)      
            {
              GPIOPinTypeOut(LCD_KEY_PORT , LCD_KEY_DIO); //   设置DIO为输出

              switch(ucKey)
              {
                 case 12:            //down 烟雾报警设置
                      flag=3;
                      hasPrintOnce = false;
                      pressKeyCount = -1;
                      break;  
                 case 13:       //leftchange   change psw mode 修改密码
                     flag=1;
                     hasPrintOnce = false;
                     pressKeyCount = -1;
                     break;
                 case 15://方框 返回主页面
                      flag=0;
                      hasPrintOnce = false;
                      pressKeyCount = -1;
                      break;
                 case 16:   //right 时间设定
                   flag = 7;
                   hasPrintOnce = false;
                   pressKeyCount = -1;

                   break;
                 case 17:           //up  防盗报警设置
                   flag=2;
                   hasPrintOnce = false;
                   pressKeyCount = -1;
                   break;
                default:
                     break;               
              }   
              
            }
        }
}

//  主函数（程序入口）
void  main(void)
{  
    jtagWait();                                             //  防止JTAG失效，重要！
    clockInit();                                              //  系统初始化
    uartInit(); 
    lcdInit();
    
    init_io();
    RX_Mode();
    SysCtlDelay(200*(TheSysClock/3000));
  //  KeyInit();
    temp_portInit();
    meltInit();
    LedOff();         //初始状态让LED灯灭
    
    buzzerInit();
    BZ_Init();
    humanInit();//防盗检测初始化
    
    zlg7289Init();                                          //  初始化ZLG7289
    sysTick_Init();
    
    adcInit(); 
    
    IntMasterEnable();    
    setTime(date,hour,minute,second);    
    SysCtlDelay(100*(TheSysClock/3000));  
        for(;;)
        {
          receiveData();
          Alarm();
          
          switch(flag)
          {
            case 0:
              if(hasPrintOnce == false)//是否已经输出
              { 
                clearAll();
                SysCtlDelay(100*(TheSysClock/3000));
                if(modebody==1)
                {
                  lcdWriteStr(2,5,"防盗已开");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                else
                {
                  lcdWriteStr(2,5,"防盗已关");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
              
                if(modeforg == 1)
                {
                  lcdWriteStr(2,1,"防火已开");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                else
                {
                  lcdWriteStr(2,1,"防火已关");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                
                char str[10];
                sprintf(str,"人数:%2d",count);
                lcdWriteStr(3,5,str);
                
                if(FoundThief != 0)
                {
                  lcdWriteStr(4,1,"发现盗贼");
                  SysCtlDelay(100*(TheSysClock/3000));
                  lcdWriteStr(3,5,"有人闯入");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                
                if(FoundFire != 0)
                {
                  lcdWriteStr(4,5,"火灾发生");
                }
                
               presence=Init_18B20();
               if(presence==0x04)
               {
                  lcdWriteStr(4,1,"温度初始化失败");
               }       
               else
               {   
                   readTemp();
                   tempToStr();
                   sprintf(temp,"%c%c%c%c度", tempBuffer[1],tempBuffer[2],tempBuffer[3],tempBuffer[4]);
                   lcdWriteStr(3,1,temp);
               }
                hasPrintOnce = true; 
              }
              
             break;
             case 1:              //input password新密码设置，输入旧密码界面
               if(pressKeyCount==-1)//还没有输入密码，显示输入密码界面
                 {
                   if(hasPrintOnce == false)//是否已经输出
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"密码设置");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"请输入两位旧密码"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                  }
                 else//开始输入密码
                 {
                   if(ucKey != OK)
                   {
                       psw[pressKeyCount]=code[ucKey];
                       lcdWriteStr(3,pressKeyCount+1,"*"); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                     if(CheckPwd(psw)==true)
                     {
                        flag= 6;//转入 新密码设置界面
                        pressKeyCount =-1;
                        hasPrintOnce = false;
                     }
                     else
                     {
                     //   clearAll();
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"密码错误重新输入"); 
                        SysCtlDelay(1000*(TheSysClock/3000));
                        pressKeyCount = -1;
                        flag = 1;//进入“新密码设置，输入旧密码界面”
                        hasPrintOnce = false;
                     }
                   }
                 }               
               break;
              case 2:            //防盗报警，密码输入界面

                 if(pressKeyCount==-1)//还没有输入密码，显示输入密码界面
                 {
                   if(hasPrintOnce == false)//是否已经输出
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"防盗设置");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"请输入两位密码"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                 }
                 else//开始输入密码
                 {
                   if(ucKey != OK)
                   {
                       psw[pressKeyCount]=code[ucKey];
                       lcdWriteStr(3,pressKeyCount+1,"*"); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                     if(CheckPwd(psw)==true)
                      {
                        flag= 5;//转入 防盗设置界面
                        pressKeyCount =-1;
                        hasPrintOnce = false;
                      }
                     else
                     {
                        //clearAll();
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"密码错误重新输入"); 
                        SysCtlDelay(1000*(TheSysClock/3000));
                        pressKeyCount = -1;
                        flag = 3;
                        hasPrintOnce = false;
                     }
                   }
                 }             
            
                 break;
                case 3://火警设置，输入密码界面
                 if(pressKeyCount==-1)//还没有输入密码，显示输入密码界面
                 {
                   if(hasPrintOnce == false)//是否已经输出
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"火警设置");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"请输入两位密码"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                  }
                 else//开始输入密码
                 {
                   if(ucKey != OK)
                   {
                       psw[pressKeyCount]=code[ucKey];
                       lcdWriteStr(3,pressKeyCount+1,"*"); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                     if(CheckPwd(psw)==true)
                      {
                        flag= 4;
                        pressKeyCount =-1;
                        hasPrintOnce = false;
                      }
                     else
                     {
                      //  clearAll();
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"密码错误重新输入"); 
                        SysCtlDelay(1000*(TheSysClock/3000));

                        flag = 3;
                        hasPrintOnce = false;
                        pressKeyCount = -1;
                     }
                   }
                 }             
            
                 break;
          case 4://火警设置界面
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"火警检测模式");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.预警模式"); 
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"2.解警模式");  
                        SysCtlDelay(200*(TheSysClock/3000));
                        
                        hasPrintOnce = true;
              }
            }
            else
            {       
                        setForgMode(code[ucKey]);
                        flag = 0;
                        pressKeyCount=-1;
                        hasPrintOnce = false;
            }
            break;
        case 5://防盗设置界面
          if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"防盗检测模式");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.预警模式"); 
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"2.解警模式");  
                        SysCtlDelay(200*(TheSysClock/3000));
                        
                        hasPrintOnce = true;
              }
            }
            else
            {       
                        setBodyMode(code[ucKey]);
                        //在此添加发送函数
                        flag = 0;
                        pressKeyCount=-1;
                        hasPrintOnce = false;
            }
          break;
          case 6://新密码设定界面
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"新密码设定模式");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"请输入新密码："); 
                        SysCtlDelay(100*(TheSysClock/3000));                       
                        hasPrintOnce = true;
              }
            }
            else
            {       
                   if(ucKey != OK)
                   {
                       psw[pressKeyCount]=code[ucKey];
                       lcdWriteStr(3,pressKeyCount+1,"*"); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                     for(int i=0;i<2;i++)
                     {
                       password[i]=psw[i];
                     }
                      lcdWriteStr(3,1,"密码设定成功   ");//密码设定成功
                      SysCtlDelay(500*(TheSysClock/3000));
                    
                      flag = 0;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             }                   
            break;
          case 7://时间设定页面
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"进入时间设定模式");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.小时设定:"); 
                        SysCtlDelay(100*(TheSysClock/3000));  
                        lcdWriteStr(3,1,"2.分钟设定:"); 
                        SysCtlDelay(100*(TheSysClock/3000)); 
                        lcdWriteStr(4,1,"3.日期设定:"); 
                        SysCtlDelay(100*(TheSysClock/3000)); 
                        hasPrintOnce = true;
              }
            }
            else
            {       
                   if(ucKey != OK)
                   {
                       if(code[ucKey] == '1')
                       {
                         flag = 8;//进入小时设定页面
                         hasPrintOnce = false;
                         pressKeyCount = -1; 
                       }
                       else if(code[ucKey] == '2')
                       {
                         flag = 9;
                         hasPrintOnce = false;
                         pressKeyCount = -1; 
                       }
                       else if(code[ucKey]== '3')
                       {
                         flag = 10;
                         hasPrintOnce = false;
                         pressKeyCount = -1; 
                       }
                   }
                   else
                   {  setTime(date,hour,minute,second);              
                      flag = 0;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             }   
            break;
          case 8:
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"小时设定");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"请输入小时："); 
                        SysCtlDelay(100*(TheSysClock/3000));  
                        hasPrintOnce = true;
              }
            }
            else
            {       
                   if(ucKey != OK)
                   {
                       char str_hour[5];
                       hour[pressKeyCount]=code[ucKey]-'0';
                       sprintf(str_hour,"%c",code[ucKey]);
                       lcdWriteStr(3,pressKeyCount+1,str_hour); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                      flag = 7;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             }  
            break;
          case 9:
             if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"分钟设定");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"请输入分钟："); 
                        SysCtlDelay(100*(TheSysClock/3000));  
                        hasPrintOnce = true;
              }
            }
            else
            {       
                   if(ucKey != OK)
                   {
                       char str_minute[5];
                       minute[pressKeyCount]=code[ucKey]-'0';
                       sprintf(str_minute,"%c",code[ucKey]);
                       lcdWriteStr(3,pressKeyCount+1,str_minute); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                      flag = 7;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             } 
            break;
          case 10:
             if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"日期设定");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"请输入日期："); 
                        SysCtlDelay(100*(TheSysClock/3000));  
                        hasPrintOnce = true;
              }
            }
            else
            {       
                   if(ucKey != OK)
                   {
                       char str_date[5];
                       date[pressKeyCount]=code[ucKey]-'0';
                       sprintf(str_date,"%c",code[ucKey]);
                       lcdWriteStr(3,pressKeyCount+1,str_date); 
                       SysCtlDelay(100*(TheSysClock/3000));
                   }
                   else
                   {
                      flag = 7;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             } 
            break;
            default:
                        break;
           }

        }
       
}

void Alarm()
{
          if(modebody==1)
          {
            humanSound();
          }
          else
          {
            GPIOPinWrite(ALARM_LED_PORT,ALARM_LED_PIN,0x00);
          }
          
          if(modeforg==1)
          {
            mq_Alarm();
          }
         readMeltState();  
}

