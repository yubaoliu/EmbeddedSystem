#include  <systick.h> 
#include  "tick.h"
#include "lcd12864.h"
#include <stdio.h>

unsigned long  time=0;
char day=0;
char s[30];
extern int flag;
void setTime(char *date,char* hh,char* mm,char* ss)
{
  day=date[0]*10+date[1];
  time=(hh[0]*10+hh[1])*3600+(mm[0]*10+mm[1])*60+ss[0];
  //sysTick_Init();
}
char *getTime(void)
{
  char *str;
  str=s;
  return str;
}
void sysTick_Init(void)   //1 second
{
  SysTickPeriodSet(6000000UL);
  SysTickIntEnable();
  IntMasterEnable();
  SysTickEnable();
}
void SysTick_ISR(void)
{
  unsigned int minute,hour,second,temp;   //   硬件会自动清除SysTick中断状态 
  char chour[10],cminute[10],csecond[10],cday[10];
  time++;
  temp=time;
  sprintf(cday,"%d",day);
  if((temp/3600)/24>=1)
  {
    day++;
  }
  hour=(temp/3600)%24;
  if(hour>=10) sprintf(chour,"%ld",hour);
  else sprintf(chour,"0%ld",hour);
  temp%=3600;
  minute=temp/60;
  if(minute>=10) sprintf(cminute,"%ld",minute);
  else sprintf(cminute,"0%d",minute);
  temp%=60;
  second=temp;
  if(second>=10) sprintf(csecond,"%ld",second);
  else sprintf(csecond,"0%ld",second);
  sprintf(s,"11-7-%s %s:%s:%s",cday,chour,cminute,csecond);
  
  if(flag == 0)
    lcdWriteStr(1,1,s);

}
