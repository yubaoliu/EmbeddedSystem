//  ������Ҫ��ͷ�ļ�
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

//������ַ
char SourceAddress[3] = {'0','0','2'};
//Ŀ�ĵ�ַ
char TargetAddress[3] = {'0','0','0'};

//ʱ���趨����
char date[2]={2,5};
char hour[2]={1,4};
char minute[2]={4,0};
char second[2]={2,3};

//  ������ʾ�ַ�ָ��
char *line1;
char show=0;   //ʹ�������ʾһ��
char show1=0;//
uint8 ucKey=0xff;
int flag = 0;//Ĭ�Ͻ����ʼ����
int pressKeyCount=-1;//�ڼ��ΰ���
tBoolean hasPrintOnce = false;
char psw[2];
extern int count;
extern char FoundThief;
extern char FoundFire;

uchar presence;
char temp[10];

//  �ַ���(ӳ���Ӧ�İ���ͼ��)
uint8 code[20] = 
{
    48,49,50,51,52,53,54,55,56,57,                          //  48~57 -> 0~9
    42,35,25,27,67,60,26,24,79,62                           //  42,35 -> *,#
};                                                          //  24,25,26,27 -> �ϣ��£�����    13-left 16-right                                                        //  67,79 -> ȡ����ȷ��                                                          //  60,62 -> F1,F2����ѡ�� ?"??

void Alarm();

//  �˿�B�жϷ�����
void GPIO_Port_E_ISR(void)
{
    uint8 ucIntStatus;  
  //  uint8 ucKey;
  
    ucIntStatus = GPIOPinIntStatus( LCD_KEY_PORT , 1);      //  ��PA���ж�״̬???

    if(ucIntStatus & LCD_KEY_KEY)                           //  �ж��Ƿ�Ϊ�����ж�
        {
            GPIOPinIntClear( LCD_KEY_PORT , LCD_KEY_KEY);   //  ���ж�
            ucKey = zlg7289Key();                           //  ������ֵ
            pressKeyCount++;
            if (ucKey != 0xff)      
            {
              GPIOPinTypeOut(LCD_KEY_PORT , LCD_KEY_DIO); //   ����DIOΪ���

              switch(ucKey)
              {
                 case 12:            //down ����������
                      flag=3;
                      hasPrintOnce = false;
                      pressKeyCount = -1;
                      break;  
                 case 13:       //leftchange   change psw mode �޸�����
                     flag=1;
                     hasPrintOnce = false;
                     pressKeyCount = -1;
                     break;
                 case 15://���� ������ҳ��
                      flag=0;
                      hasPrintOnce = false;
                      pressKeyCount = -1;
                      break;
                 case 16:   //right ʱ���趨
                   flag = 7;
                   hasPrintOnce = false;
                   pressKeyCount = -1;

                   break;
                 case 17:           //up  ������������
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

//  ��������������ڣ�
void  main(void)
{  
    jtagWait();                                             //  ��ֹJTAGʧЧ����Ҫ��
    clockInit();                                              //  ϵͳ��ʼ��
    uartInit(); 
    lcdInit();
    
    init_io();
    RX_Mode();
    SysCtlDelay(200*(TheSysClock/3000));
  //  KeyInit();
    temp_portInit();
    meltInit();
    LedOff();         //��ʼ״̬��LED����
    
    buzzerInit();
    BZ_Init();
    humanInit();//��������ʼ��
    
    zlg7289Init();                                          //  ��ʼ��ZLG7289
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
              if(hasPrintOnce == false)//�Ƿ��Ѿ����
              { 
                clearAll();
                SysCtlDelay(100*(TheSysClock/3000));
                if(modebody==1)
                {
                  lcdWriteStr(2,5,"�����ѿ�");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                else
                {
                  lcdWriteStr(2,5,"�����ѹ�");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
              
                if(modeforg == 1)
                {
                  lcdWriteStr(2,1,"�����ѿ�");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                else
                {
                  lcdWriteStr(2,1,"�����ѹ�");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                
                char str[10];
                sprintf(str,"����:%2d",count);
                lcdWriteStr(3,5,str);
                
                if(FoundThief != 0)
                {
                  lcdWriteStr(4,1,"���ֵ���");
                  SysCtlDelay(100*(TheSysClock/3000));
                  lcdWriteStr(3,5,"���˴���");
                  SysCtlDelay(100*(TheSysClock/3000));
                }
                
                if(FoundFire != 0)
                {
                  lcdWriteStr(4,5,"���ַ���");
                }
                
               presence=Init_18B20();
               if(presence==0x04)
               {
                  lcdWriteStr(4,1,"�¶ȳ�ʼ��ʧ��");
               }       
               else
               {   
                   readTemp();
                   tempToStr();
                   sprintf(temp,"%c%c%c%c��", tempBuffer[1],tempBuffer[2],tempBuffer[3],tempBuffer[4]);
                   lcdWriteStr(3,1,temp);
               }
                hasPrintOnce = true; 
              }
              
             break;
             case 1:              //input password���������ã�������������
               if(pressKeyCount==-1)//��û���������룬��ʾ�����������
                 {
                   if(hasPrintOnce == false)//�Ƿ��Ѿ����
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"��������");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"��������λ������"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                  }
                 else//��ʼ��������
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
                        flag= 6;//ת�� ���������ý���
                        pressKeyCount =-1;
                        hasPrintOnce = false;
                     }
                     else
                     {
                     //   clearAll();
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"���������������"); 
                        SysCtlDelay(1000*(TheSysClock/3000));
                        pressKeyCount = -1;
                        flag = 1;//���롰���������ã������������桱
                        hasPrintOnce = false;
                     }
                   }
                 }               
               break;
              case 2:            //���������������������

                 if(pressKeyCount==-1)//��û���������룬��ʾ�����������
                 {
                   if(hasPrintOnce == false)//�Ƿ��Ѿ����
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"��������");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"��������λ����"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                 }
                 else//��ʼ��������
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
                        flag= 5;//ת�� �������ý���
                        pressKeyCount =-1;
                        hasPrintOnce = false;
                      }
                     else
                     {
                        //clearAll();
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"���������������"); 
                        SysCtlDelay(1000*(TheSysClock/3000));
                        pressKeyCount = -1;
                        flag = 3;
                        hasPrintOnce = false;
                     }
                   }
                 }             
            
                 break;
                case 3://�����ã������������
                 if(pressKeyCount==-1)//��û���������룬��ʾ�����������
                 {
                   if(hasPrintOnce == false)//�Ƿ��Ѿ����
                   {
                     clearAll();
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(1,1,"������");
                     SysCtlDelay(100*(TheSysClock/3000));
                     lcdWriteStr(2,1,"��������λ����"); 
                     SysCtlDelay(100*(TheSysClock/3000));
                     hasPrintOnce =true;
                   }
                  }
                 else//��ʼ��������
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
                        lcdWriteStr(3,1,"���������������"); 
                        SysCtlDelay(1000*(TheSysClock/3000));

                        flag = 3;
                        hasPrintOnce = false;
                        pressKeyCount = -1;
                     }
                   }
                 }             
            
                 break;
          case 4://�����ý���
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"�𾯼��ģʽ");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.Ԥ��ģʽ"); 
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"2.�⾯ģʽ");  
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
        case 5://�������ý���
          if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"�������ģʽ");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.Ԥ��ģʽ"); 
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(3,1,"2.�⾯ģʽ");  
                        SysCtlDelay(200*(TheSysClock/3000));
                        
                        hasPrintOnce = true;
              }
            }
            else
            {       
                        setBodyMode(code[ucKey]);
                        //�ڴ���ӷ��ͺ���
                        flag = 0;
                        pressKeyCount=-1;
                        hasPrintOnce = false;
            }
          break;
          case 6://�������趨����
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"�������趨ģʽ");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"�����������룺"); 
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
                      lcdWriteStr(3,1,"�����趨�ɹ�   ");//�����趨�ɹ�
                      SysCtlDelay(500*(TheSysClock/3000));
                    
                      flag = 0;
                      hasPrintOnce = false;
                      pressKeyCount = -1;    
                   }

             }                   
            break;
          case 7://ʱ���趨ҳ��
            if(pressKeyCount ==-1)
            {
              if(hasPrintOnce == false)
              {
                        clearAll();
                        SysCtlDelay(200*(TheSysClock/3000));
                        lcdWriteStr(1,1,"����ʱ���趨ģʽ");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"1.Сʱ�趨:"); 
                        SysCtlDelay(100*(TheSysClock/3000));  
                        lcdWriteStr(3,1,"2.�����趨:"); 
                        SysCtlDelay(100*(TheSysClock/3000)); 
                        lcdWriteStr(4,1,"3.�����趨:"); 
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
                         flag = 8;//����Сʱ�趨ҳ��
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
                        lcdWriteStr(1,1,"Сʱ�趨");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"������Сʱ��"); 
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
                        lcdWriteStr(1,1,"�����趨");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"��������ӣ�"); 
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
                        lcdWriteStr(1,1,"�����趨");
                        SysCtlDelay(100*(TheSysClock/3000));
                        lcdWriteStr(2,1,"���������ڣ�"); 
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

