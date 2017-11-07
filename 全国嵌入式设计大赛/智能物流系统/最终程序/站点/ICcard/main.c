
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <sys/signal.h>
#include <pthread.h>
#include "tty.h"
#include "IC_card.h"
#define ENDMINITERM 27 
#define FALSE		0
#define TRUE  		1

volatile int STOP=FALSE;
//extern int baud=B57600; 

main(int argc, char* argv[]){
   
	tty_init();

	keyshell();
   
  	exit(0); 
}
/**
int get_baudrate(int argc,char** argv)
{
	int v=atoi(argv[1]);
	 switch(v){
		case 4800:
			return B4800;
			
		case 9600:
			return B9600;
			
		case 19200:
			return B19200;
			
		case 38400:
			return B38400;
			
		case 57600:
			return B57600;
			
		case 115200:
			return B115200;
		default:
			return -1;
	 } 	 
}
*/
