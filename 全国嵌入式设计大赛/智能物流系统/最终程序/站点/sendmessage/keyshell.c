#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include "../keyboard/get_key.h"

char shell_s[]="\nkeyshell> ";

/*int argc, char *argv[*/
#define CMD_TPYE			(0)
#define PHONE_NUMBER		(1)
#define MAX_CMD_DEPTH  	(2)
extern volatile int STOP ;

extern char PHONE[];
void * keyshell()
{

	char cmd[256]={0,};
	char *number="1";
	int i;
	
	kbd_init();		//键盘初始化	
	
	gprs_init();		//GPRS 初始化	
	
	printf("\n<gprs control shell>");
	printf("\n [1]  give a call");		
	printf("\n [2]  respond a call");		
	printf("\n [3]  hold a call");		
	printf("\n [4]  send a msg");
	printf("\n [5]  change baudrate");
	printf("\n [6]  exit");
	printf("\n [**] help menu");
	printf("\n [7]  list message you havn't read");
	while(1){

		printf(shell_s);
		fflush(stdout);
		usleep(20000000);

		gprs_msg(number, strlen(number));
//		get_line(cmd);
		printf("\r\n");				//显示必要的输出

		
				 if(cmd[0] != 0){
		
						system(cmd);
		}
	}		
}
