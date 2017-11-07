
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/signal.h>
#include "tty.h"
#include"gprs.h"
#include<sys/types.h>
#include<sys/stat.h>
#define FILE_NAME "data.txt"


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
	//char text[]="HELLO WORLD .IAM WIN";
	char text[1024];
	file=open(FILE_NAME,O_RDONLY,S_IRUSR|S_IRGRP|S_IROTH);
	read(file,text,sizeof(text));
	
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at", strlen("at"));
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));		//·¢ËÍÐÞ¸Ä×Ö·û¼¯ÃüÁî
	tty_write("at+cmgs=", strlen("at+cmgs="));	//·¢ËÍ·¢¶ÌÐÅÃüÁî£¬¾ßÌå¸ñÊ½¼ûÊÖ²á

    tty_write("\"", strlen("\""));
    tty_write(number, strlen(number));
    tty_write("\"", strlen("\""));
    tty_write(";\r", strlen(";\r"));
    
    // tty_writecmd(number, strlen(number));
	tty_write(text, strlen(text));
	tty_write(ctl, 1);
	usleep(300000);
	
	close(file);
//	Uart_SendByte(1,26); //¡°CTRL+Z"µÄASCIIÂë
}
//��ȡ���� add by myself
void gprs_read_message(int index)
{
	//�г��洢���еĶ���
	printf("�г��洢���е�����");
	tty_writecmd("at",strlen("at"));
	tty_writecmd("at",strlen("at"));
	tty_writecmd("at+cmgf=1",strlen("at+cmgf=1"));
	tty_writecmd("at+CMGL",strlen("at+CMGL"));
//	gprs_read();
	usleep(30000);
	
	

}
void gprs_baud(char *baud,int num)
{
	tty_write("at+ipr=", strlen("at+ipr="));
	tty_writecmd(baud, strlen(baud) );
	usleep(200000);
}
