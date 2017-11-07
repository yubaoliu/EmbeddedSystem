#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include "keyshell.h"
#define CMD_TPYE			(0)
#define PHONE_NUMBER		(1)
#define MAX_CMD_DEPTH  	(2)

#define DCM_IOCTRL_SETPWM 			(0x10)
#define DCM_TCNTB0				(16384)

#define FILE_NAME "ic.txt"
char *DCM_DEV="/dev/dcm/0raw";
extern volatile int STOP ;
extern char PHONE[];

void  *keyshell()
{	
	int file;
	uchar buf[1024];
	int i;
        int m=0;
	char cmd[256]={0,};	

	uchar CardNo[4],CardKey[6];
	uchar CardData[16];
	uchar Default_CardBlock=0x01;
	uchar Choose_CardBlock=0x01;
	for(i=0;i<16;i++)CardData[i]=0x00;
	for(i=0;i<4;i++) CardNo[i]=0;
  /*	**************************************************/
	file=open(FILE_NAME,O_RDWR|O_TRUNC|O_CREAT,S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
	if(file<0)
	{
		printf("open file error");
		exit(1);
	}
	else
	{
		printf("file open success");
	}

	while(1)
	  {
	   
	        fflush(stdout);
		fflush(stdin);
	        tty_fflush();//05-22
	       	Rd_DefBlock(CardNo,CardData,0);
	//	usleep(30000);
//		CLR_Set();
//		TurnOff_Card();
//	       	if((CardNo[0]==0)&&(CardNo[1]==0))      ////////////////&&(CardNo[2]==0)&&(CardNo[3]==0))
//		  {  printf("m=%d",m);
//		     CLR_Set();
//		     TurnOff_Card();
		      
//		  }
if(((CardNo[0] ==0x32)&&(CardNo[1] ==0x5a)&&(CardNo[2]==0xab)&&(CardNo[3] ==0x55))||((CardNo[0] ==0x52)&&(CardNo[1] ==0x29)&&(CardNo[2]==0xaa)&&(CardNo[3] ==0x55)))		
	       	  {
		       int m ,n ;
		       int t = 0;
		       int status = 1;
		       int setpwm = 0;
		       int dcm_fd = -1;
		       int o=5;
		       printf("\nThe ICcard NO.:");
		       for(i=0;i<4;i++)
			{
				printf(" %x",CardNo[i]);
				sprintf(buf,"%x",CardNo[i]);
				write(file,buf,2);
			}
			lseek(file,0,SEEK_SET);

      		       printf("\nThe Datas:");
		       for(i=0;i<16;i++)printf(" %x",CardData[i]);
		       printf("\nwe do success!");
		       //usleep(50000);
		      
		     
		        if((dcm_fd=open(DCM_DEV, O_WRONLY))<0)
		        {
		      	 printf("Error opening %s device\n", DCM_DEV);
		      	 return 1;
		         }
	
	
		  //	for (o=0;o<10;o++) {
	        //	for (i=-512; i<=512; i++) {
		//	if(status == 1)
		//		setpwm = i;
		//	else
		//		setpwm = -i;
			//iostl(dcm_fd, DCM_IOCTRL_SETPWM,(512 * ( DCM_TCNTB0 / 102)));
		//	sleep(5);
		//	iostl(dcm_fd, DCM_IOCTRL_SETPWM,0);
	//		ioctl(dcm_fd, DCM_IOCTRL_SETPWM, (setpwm * ( DCM_TCNTB0/102)));		       
			ioctl(dcm_fd, DCM_IOCTRL_SETPWM , (512 * (DCM_TCNTB0 / 102)));
			sleep(5);
			ioctl(dcm_fd, DCM_IOCTRL_SETPWM , 0);
		//	for(m = 500;m>0;m--)
		//	for(n=0;n<400;n++);
			
		//}
	//	status = -status;
//	}
	
           	close(dcm_fd);	
	      	CLR_Set();
		usleep(30000);
		TurnOff_Card();
		usleep(30000);
		sleep(1);
         	}
	  }
	close(file);
}
