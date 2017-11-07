


#include <sys/types.h>                                                  
#include <sys/stat.h>                                                      
#include <fcntl.h>                                                       
#include <termios.h>   //这个文件用来进行相应的                                                    
#include <stdio.h>    

#define BAUDRATE B57600  //进行了修改,文档中已经说明了要使用57600的波特率

#define COM3 "/dev/ttyS2"
#define EXPORT COM3

static int fd;
static struct termios oldtio,newtio,oldstdtio,newstdtio;

int tty_read(char *buf,int nbytes)
{
       	int i,status = 0;
	status = read(fd,buf,nbytes);//一次就进行了数据的读取。
	//	printf("\nwe read:");   //进行了修改
	if(status>=0)
		for(i=0;i<nbytes;i++)  //进行了修改
		  //	printf(" %x",buf[i]);//进行了修改//将读取的数据进行输出
	return status;
}

int tty_write(char *buf,int nbytes)
{
	int i,code = 0;
	
	for(i=0; i<nbytes; i++) {
	  code += write(fd,&buf[i],1);
		usleep(100);
	}

	return tcdrain(fd);
}


int tty_init()
{
        //进行了修改
	int status =0;

	fd = open(EXPORT, O_RDWR ); 
       	if(fd<0) {
	    	perror(EXPORT);
		
	    	exit(-1);
  	}

	
  	tcgetattr(0,&oldstdtio);//修改，进行了注释
  	tcgetattr(fd,&oldtio); /* save current modem settings */



  	tcgetattr(fd,&newstdtio); /* get working stdtio */
	tcflush(fd, TCIOFLUSH); //刷新输入输出缓冲

        //设置数据的发送与接收波特率
	cfsetispeed(&newtio, BAUDRATE); //这里分别设置，//进行了修改注释 分别设置了输入与输出的数据速率，填入串口输入端的波特率 
	cfsetospeed(&newtio, BAUDRATE);                                                    //填入串口输出端的波特率

    if(set_Parity(fd,8,1,'N')==0) //设置8，1，n 注意，这里和上面要和下位机相符才可能通信 ／／注释修改 调用了自己的一个子函数
	{
		printf("\nSet Parity Error\n");
		return 1;
	}
	return 0;
}


int set_Parity(int fd,int databits,int stopbits,int parity) 
{       int FALSE=0,TRUE=1;
        struct termios new_cfg,old_cfg;
        int speed;

if(tcgetattr(fd,&old_cfg)!=0)
{
   perror("tcgetattr");
       return -1;
 }

new_cfg = old_cfg;
cfmakeraw(&new_cfg);
new_cfg.c_cflag &= ~CSIZE;
new_cfg.c_cflag |=CS8;
new_cfg.c_cflag &=~PARENB;
new_cfg.c_iflag &=~INPCK;
new_cfg.c_cflag &=~CSTOPB;
new_cfg.c_cc[VTIME]=150;
new_cfg.c_cc[VMIN]=0;

tcflush(fd,TCIFLUSH);
if((tcsetattr(fd,TCSADRAIN,&new_cfg))!=0)
{
   perror("tcsetattr");
      return -1;
}
return (TRUE);
}

void tty_fflush(){
	tcflush(fd,TCIFLUSH);

}

