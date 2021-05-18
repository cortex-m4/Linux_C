/*
 * example of serial
 *
 * Author: JoStudio
 */


#include <unistd.h>
#include "serial.h"
#include "stdio.h"

int main() {
	int fd;
	char c;
	char i=0;
	fd = serial_open(0, 9600);//open serial port 0, /etc/ttyS0
	if ( fd !=-1 ) {

		while (1) {
			printf("num is %d \r\n",i);
			
			c = i+0x30;
			serial_send(fd, &c, 1);  //send '1234567890'
			sleep(1);
			if(i==9)break;
			i++;
		}

		serial_close(fd);
	}else{
		printf("failed\r\n");
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

