/*
 * example of serial
 *
 * Author: JoStudio
 */


#include <unistd.h>
#include "serial.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define uint8_t 	unsigned char 
#define uint16_t 	unsigned int
#define uint32_t 	unsigned long int



uint8_t touchpad_tx_dat[1024]={0};
uint8_t touchpad_rx_dat[10]={0};

uint8_t read_ota_data[512]={0};
uint8_t read_ota_data_log[512]={0};

int fd;	//串口


uint16_t CheckSumNOT(uint8_t *buf, uint16_t len) 
{ 
    uint16_t i, ret = 0;
 
		for(i=0; i<len; i++)
		{
				ret = (*(buf++)+ret)&0xffff;
		}
		ret = 0xffff-ret;
    return ret;

}

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



void Touchpad_DownloadCmd(uint32_t baudrate,uint32_t filesize,uint8_t *down_name){
	uint8_t i=0;
	uint8_t down_name_len=0;
	memset(touchpad_tx_dat,0,1024);
	touchpad_tx_dat[0]=0xee;
	touchpad_tx_dat[1]=0xb6;
	touchpad_tx_dat[2]=0x00;		//88+11+baudrate 4 +4+ota.bin
	touchpad_tx_dat[3]=17;
	touchpad_tx_dat[4]=0x88;
	touchpad_tx_dat[5]=0x11;
	touchpad_tx_dat[6]=(baudrate>>24);
	touchpad_tx_dat[7]=(baudrate>>16);
	touchpad_tx_dat[8]=(baudrate>>8);
	touchpad_tx_dat[9]=(baudrate&0xff);
	touchpad_tx_dat[10]=(filesize>>24);
	touchpad_tx_dat[11]=(filesize>>16);
	touchpad_tx_dat[12]=(filesize>>8);
	touchpad_tx_dat[13]=(filesize&0xff);
	//14 15 16 17 18 19 20
	down_name_len=strlen(down_name);
	printf("down_name len is %d \r\n",down_name_len);
	for(i=1;i<=down_name_len;i++){
		touchpad_tx_dat[13+i]=*down_name;
		down_name++;
	}
	touchpad_tx_dat[13+down_name_len+1]=0xff;
	touchpad_tx_dat[13+down_name_len+2]=0xfc;
	touchpad_tx_dat[13+down_name_len+3]=0xff;
	touchpad_tx_dat[13+down_name_len+4]=0xff;
	serial_send(fd,touchpad_tx_dat,25);
}

void Touchpad_DownloadData(uint16_t sn,uint8_t *packet,uint16_t packet_len){
	uint16_t len=0;
	uint16_t i=0;
	memset(touchpad_tx_dat,0,1024);
	touchpad_tx_dat[0]=0xee;
	touchpad_tx_dat[1]=0xb6;
	len=5+packet_len;
	touchpad_tx_dat[2]=len>>8;
	touchpad_tx_dat[3]=len&0xff;
	touchpad_tx_dat[4]=0x88;
	touchpad_tx_dat[5]=0x22;
	touchpad_tx_dat[6]=(uint8_t)sn;
	for(i=1;i<=packet_len;i++){
		
		touchpad_tx_dat[6+i]=*packet;
		packet++;
	}
	touchpad_tx_dat[6+packet_len+1]=CheckSumNOT((touchpad_tx_dat+1),packet_len+6)>>8;
	touchpad_tx_dat[6+packet_len+2]=CheckSumNOT((touchpad_tx_dat+1),packet_len+6)&0xff;
	touchpad_tx_dat[6+packet_len+3]=0xff;
	touchpad_tx_dat[6+packet_len+4]=0xfc;
	touchpad_tx_dat[6+packet_len+5]=0xff;
	touchpad_tx_dat[6+packet_len+6]=0xff;
	serial_send(fd,touchpad_tx_dat,packet_len+13);
}
void Touchpad_Upgrade(void){
	touchpad_tx_dat[0]=0xee;
	touchpad_tx_dat[1]=0xb6;
	touchpad_tx_dat[2]=0x00;
	touchpad_tx_dat[3]=0x03;
	touchpad_tx_dat[4]=0x88;
	touchpad_tx_dat[5]=0x33;
	touchpad_tx_dat[6]=0x01;
	touchpad_tx_dat[7]=0xff;
	touchpad_tx_dat[8]=0xfc;
	touchpad_tx_dat[9]=0xff;
	touchpad_tx_dat[10]=0xff;
	serial_send(fd,touchpad_tx_dat,11);
}

int file_size(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);
    
    return size;
}

/*
	参数 1：端口号	
	参数 2：波特率
*/
int main(int argc,char *argv[]) {
	
	uint16_t i=0;
	uint16_t j=0;
	uint16_t pos=0;
	size_t read_data_flag=0;
	uint32_t file_size_t=0;
	uint16_t packet_len=0;
	uint16_t last_packet_len=0;
	uint16_t send_len=0;

	char port;
	uint16_t wait_time=atoi(argv[3]);
	int baundrate=atoi(argv[2]);
	FILE *fpR=NULL;
	port=atoi(argv[1]);
	printf("user input args num:%d \n",argc);
	for(i=0;i<=(argc-1);i++){
		printf("argv[%d] is %s \n",i,argv[i]);
	}
	printf("open serial %d ,baundrate is %d\r\n",port,baundrate);
	//打开串口
	fd = serial_open(port, baundrate);
	//参数输入合法
	if(argc==4){
		if ( fd > 0 ) {
			file_size_t=file_size("./file/ota.bin");
			packet_len=file_size_t/512;
			last_packet_len=file_size_t%512;
			printf("open serial success!\r\n");
			printf("file size is %d \r\n",(int)file_size_t);
			printf("packet len is %d \r\n",packet_len);
			printf("last packet len is %d \r\n",last_packet_len);
			fpR = fopen("./file/ota.bin", "r");
			fseek(fpR,0,SEEK_SET);
			
			//发送开始升级指令
			Touchpad_DownloadCmd(baundrate,file_size_t,"ota.bin");
			//开始下载
			printf("start download\r\n");
			usleep(wait_time*1000);
			pos=0;
			i=0;
			while (1) {
				if(i==(packet_len)){
					printf("last \r\n");
					send_len=last_packet_len;
					read_data_flag=fread(read_ota_data,last_packet_len,1,(FILE *)fpR);
				}else{
					send_len=512;
					read_data_flag=fread(read_ota_data,512,1,(FILE *)fpR);
				}
				if(1){
					send:{
						Touchpad_DownloadData(pos,read_ota_data,send_len);
						memset(touchpad_rx_dat,0,10);
						//serial_receive(fd,touchpad_rx_dat,10);
						usleep(wait_time*1000);
						printf("packet %d data:",pos);
						for(j=0;j<10;j++){
							printf("%#X ",touchpad_rx_dat[j]);
						}
						printf("\r\n");
					}
					switch(touchpad_rx_dat[3]){
						case 0x80:
							/*
							i=i+1;
							if(i>255)i=0;
							pos=i;
							memcpy(read_ota_data_log,read_ota_data,512);
							*/
						break;
						case 0x82:
							//pos=touchpad_rx_dat[4];
							pos=i-1;
							pos=i%256;
							memcpy(read_ota_data,read_ota_data_log,512);
							goto send;
						break;
						case 0x83:
							
						break;
						//触摸屏没有回消息
						default:
							//goto send;
						break;

					}
				}
				i=i+1;
				pos=i%256;
				if(i==(packet_len+1))break;
			}
			printf("send over!\r\n");
			Touchpad_Upgrade();
			serial_receive(fd,touchpad_rx_dat,10);
			usleep(1000000);
			printf("packet %d data:",999);
			for(j=0;j<10;j++){
				printf("%#X ",touchpad_rx_dat[j]);
			}
			printf("\r\n");
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

