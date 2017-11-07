
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

	//ÏÂÃæÑ¡ÔñÍ¨µÀ0£¬Ê¹ÓÃÆÕÍ¨µç»°»°±ú
	/*
	  gprs_cmd("AT+CHFA=0\r"); //ÉèÖÃÍ¨»°Í¨µÀÎª0
	  usleep(1000);
	  gprs_cmd("AT+CLVL=100\r");//ÉèÖÃÊÜ»°Æ÷ÒôÁ¿×î´ó
	  usleep(1000);
	  gprs_cmd("AT+CMIC=0,10\r");//ÉèÖÃÍ¨µÀ0µÄ»°Í²ÔöÒæ
	  usleep(1000);
	*/
}

void gprs_hold()
{
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ath", strlen("ath"));//·¢ËÍ¹Ò»úÃüÁîATH
}

void gprs_ans()
{ 
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ata", strlen("ata"));//·¢ËÍ½ÓÌýÃüÁîATA
}

//²¦½Ð  
void gprs_call(char *number, int num)			
{ 

	tty_write("atd", strlen("atd")); //·¢ËÍ²¦´òÃüÁîATD	
	tty_write(number, num);
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//·¢ËÍ¶ÌÐÅ
//void gprs_msg(char *number,char *text) 			//·¢ËÍ¶ÌÐÅ

	

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
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));		//���0�4�0�9�0�1�0�4�0�7�0�0�0�2���0�0���0�4�0�4�0�4�0�1���0�9�0�6
	tty_write("at+cmgs=", strlen("at+cmgs="));	//���0�4�0�9�0�1���0�4�0�9�0�0�0�4�0�3�0�1���0�9�0�6�0�5�0�1�0�6�0�8�0�0�0�2�0�0�0�9�0�8�0�5�0�4�0�4�0�8�0�0�0�5��

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
//	Uart_SendByte(1,26); //�0�3��CTRL+Z"�0�8�0�2ASCII�0�0�0�5
}
void gprs_baud(char *baud,int num)
{
	tty_write("at+ipr=", strlen("at+ipr="));
	tty_writecmd(baud, strlen(baud) );
	usleep(200000);
}
