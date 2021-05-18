/*
 * example of serial
 *
 * Author: JoStudio
 */


#include <unistd.h>
#include "serial.h"
#include "stdio.h"
#include "stdlib.h"

/*
#include <termios.h>
//keyborad


static struct termios initial_settings, new_settings;
static int peek_character = -1;
void init_keyboard(void);
void close_keyboard(void);
int kbhit(void);
int readch(void); 
void init_keyboard()
{
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag |= ICANON;
	new_settings.c_lflag |= ECHO;
	new_settings.c_lflag |= ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}
 
void close_keyboard()
{
	tcsetattr(0, TCSANOW, &initial_settings);
}
 
int kbhit()
{
	unsigned char ch;
	int nread;
 
	if (peek_character != -1) return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);
	if(nread == 1) 
	{
		peek_character = ch;
		return 1;
	}
	return 0;
}
 
int readch()
{
	char ch;
 
	if(peek_character != -1) 
	{
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0,&ch,1);
	return ch;
}
*/


int main(int argc,char *argv[]) {
	int fd;
	char i;
	char c;
	char port;
	int baundrate=atoi(argv[2]);
	port=atoi(argv[1]);
	printf("user input args num:%d \n",argc);
	for(i=0;i<=(argc-1);i++){
		printf("argv[%d] is %s \n",i,argv[i]);
	}
	printf("open serial %d ,baundrate is %d\r\n",port,baundrate);
	fd = serial_open(port, baundrate);//open serial port 0, /etc/ttyS0
	if(argc==3){
		if ( fd > 0 ) {
			i=0;
			while (1) {
				
				// kbhit();
				// input=readch();
				// if(input!=0)break;
				c = i+0x30;
				serial_send(fd, &c, 1); //send '1'
				sleep(1);
				if(i==3)break;
				i++;
				
			}
			serial_close(fd);
		}else{
			printf("open serial failed!\r\n");
		}
	}else{
		printf("command error!\r\n");
	}

}


/*
int main() {
	int fd;
	int i;
	char c;
	char buf[2];

	fd = serial_open(0, 57600);
	if ( fd < 0 ) {
		printf("open serial port 0 failed\n");
		exit(1);
	}

	//serial_set_attr(fd, 8, PARITY_NONE, 1, FLOW_CONTROL_NONE);

	c = '0';
	for ( i = 0; i < 10; i++ ) {
		c = (c == '0') ? '1' : '0';
		printf("send %c\n", c);
		buf[0] = c; buf[1] = 0;
		write(fd, buf, 2);
		sleep(1);
	}

	serial_close(fd);
}
*/

