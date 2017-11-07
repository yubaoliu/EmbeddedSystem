
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/signal.h>
#include "tty.h"
#include"gprs.h"
#include<sys/types.h>
#include<sys/stat.h>
#define FILE_NAME "sendmessage.txt"

void gprs_init()
{ 
	int i;
	for(i=0; i<5; i++) {
		tty_writecmd(cmd[i], strlen(cmd[i])); 
	}

	//脧脗脙忙脩隆脭帽脥篓碌脌0拢卢脢鹿脫脙脝脮脥篓碌莽禄掳禄掳卤煤
	/*
	  gprs_cmd("AT+CHFA=0\r"); //脡猫脰脙脥篓禄掳脥篓碌脌脦陋0
	  usleep(1000);
	  gprs_cmd("AT+CLVL=100\r");//脡猫脰脙脢脺禄掳脝梅脪么脕驴脳卯麓贸
	  usleep(1000);
	  gprs_cmd("AT+CMIC=0,10\r");//脡猫脰脙脥篓碌脌0碌脛禄掳脥虏脭枚脪忙
	  usleep(1000);
	*/
}

void gprs_hold()
{
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ath", strlen("ath"));//路垄脣脥鹿脪禄煤脙眉脕卯ATH
}

void gprs_ans()
{ 
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ata", strlen("ata"));//路垄脣脥陆脫脤媒脙眉脕卯ATA
}

//虏娄陆脨  
void gprs_call(char *number, int num)			
{ 

	tty_write("atd", strlen("atd")); //路垄脣脥虏娄麓貌脙眉脕卯ATD	
	tty_write(number, num);
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//路垄脣脥露脤脨脜
//void gprs_msg(char *number,char *text) 			//路垄脣脥露脤脨脜

	

void gprs_msg(char *number, int num)		
{ 
	int file;
	char ctl[]={26,0};
	char tel[1024];
char s[12];
	char text[]="Your package has received,please take it away quickly";
	file=open(FILE_NAME,O_RDWR,S_IRUSR|S_IRGRP|S_IROTH);
	read(file,tel,sizeof(tel));
sprintf(s,"%c",tel[0]);
if(s[0]!='#')
{
	
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));		//·¢ËÍÐÞ¸Ä×Ö·û¼¯ÃüÁî
	tty_write("at+cmgs=", strlen("at+cmgs="));	//·¢ËÍ·¢¶ÌÐÅÃüÁî£¬¾ßÌå¸ñÊ½¼ûÊÖ²á

    tty_write("\"", strlen("\""));
    tty_write(tel, strlen(tel));
    tty_write("\"", strlen("\""));
    tty_write(";\r", strlen(";\r"));
    
    // tty_writecmd(number, strlen(number));
	tty_write(text, strlen(text));
	tty_write(ctl, 1);
	usleep(300000);
lseek(file,0,SEEK_SET);
write(file,"#",1);
}
	
	close(file);
//	Uart_SendByte(1,26); //¡°CTRL+Z"µÄASCIIÂë
}
void gprs_baud(char *baud,int num)
{
	tty_write("at+ipr=", strlen("at+ipr="));
	tty_writecmd(baud, strlen(baud) );
	usleep(200000);
}
