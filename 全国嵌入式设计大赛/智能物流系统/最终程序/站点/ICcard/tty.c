


#include <sys/types.h>                                                  
#include <sys/stat.h>                                                      
#include <fcntl.h>                                                       
#include <termios.h>   //����ļ�����������Ӧ��                                                    
#include <stdio.h>    

#define BAUDRATE B57600  //�������޸�,�ĵ����Ѿ�˵����Ҫʹ��57600�Ĳ�����

#define COM3 "/dev/ttyS2"
#define EXPORT COM3

static int fd;
static struct termios oldtio,newtio,oldstdtio,newstdtio;

int tty_read(char *buf,int nbytes)
{
       	int i,status = 0;
	status = read(fd,buf,nbytes);//һ�ξͽ��������ݵĶ�ȡ��
	//	printf("\nwe read:");   //�������޸�
	if(status>=0)
		for(i=0;i<nbytes;i++)  //�������޸�
		  //	printf(" %x",buf[i]);//�������޸�//����ȡ�����ݽ������
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
        //�������޸�
	int status =0;

	fd = open(EXPORT, O_RDWR ); 
       	if(fd<0) {
	    	perror(EXPORT);
		
	    	exit(-1);
  	}

	
  	tcgetattr(0,&oldstdtio);//�޸ģ�������ע��
  	tcgetattr(fd,&oldtio); /* save current modem settings */



  	tcgetattr(fd,&newstdtio); /* get working stdtio */
	tcflush(fd, TCIOFLUSH); //ˢ�������������

        //�������ݵķ�������ղ�����
	cfsetispeed(&newtio, BAUDRATE); //����ֱ����ã�//�������޸�ע�� �ֱ�������������������������ʣ����봮������˵Ĳ����� 
	cfsetospeed(&newtio, BAUDRATE);                                                    //���봮������˵Ĳ�����

    if(set_Parity(fd,8,1,'N')==0) //����8��1��n ע�⣬���������Ҫ����λ������ſ���ͨ�� ����ע���޸� �������Լ���һ���Ӻ���
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

