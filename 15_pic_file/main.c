/*
	只能读取bmp 1位图
	图片风格：一行必须是4byte的倍数
	byte 19 行像素bit
	byte 23 列像素个数
	byte 3	文件大小
*/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define uint8_t 	unsigned char 
#define uint16_t 	unsigned int
#define uint32_t 	unsigned long int

#define BUFF_SIZE	1024

#define FILE_NAME	"./pic/pic.bmp"

uint8_t pic_buf[BUFF_SIZE]={0};

int file_sizeof(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);
    
    return size;
}

void print_byte(uint8_t buf){
	uint8_t i;
	for(i=0;i<8;i++){
		if((buf<<i)&0x80){
			printf("%s","_ ");
		}else{
			printf("%s","M ");
		}
	}
}

void print_hang(uint8_t *buf,uint16_t len){
	uint16_t i;
	for(i=0;i<(len/8);i++){
		print_byte(*buf);
		buf++;
	}
	for(i=0;i<(len%8);i++){
		if((*buf<<i)&0x80){
			printf("%s","_ ");
		}else{
			printf("%s","M ");
		}
	}
	
}

int main(int argc,char *argv[])
{
	uint32_t i=0;
	uint32_t j=0;
	uint16_t pic_num=1;
	uint16_t pic_len=0;
	FILE *fp = NULL; 
	int file_size=0;
	uint8_t read_flag=0;

	uint16_t hang_scan=0;	//一行的byte
	uint16_t lie=0;			//多少列
	uint16_t pic_size=0;	//图片大小
	uint16_t hang=0;		//一行的bit
	char buf[32]={0};
	if(argc==2){
	pic_len=atoi(argv[1]);
	while(pic_num<=pic_len){
		snprintf(buf,sizeof buf,"./pic/%d.bmp",pic_num);
		file_size=file_sizeof(buf);
		if(file_size==-1){
			printf("open file failed!\n");
			return 0;
		}
		fp = fopen(buf, "r");
		fseek(fp,0,SEEK_SET);
		read_flag=fread(pic_buf,file_size,1,fp);
		/*
		printf("file size is %d \r\n",file_size);
		
		//打印图片原始数据
		printf("pic data is :\r\n");
		for(i=62;i<file_size;i++ ,j++){
			if(j%4==0) printf("\r\n");
			printf("%d:",i);
			if(pic_buf[i]==0)printf("0x0%d ",pic_buf[i]);
			else printf("%#X ",pic_buf[i]);
		}
		printf("\r\n");
		*/
		//打印图片
		lie=pic_buf[22];
		hang=pic_buf[18];
		pic_size=file_size-62;
		//printf("pic size is:%d\n",pic_size);
		hang_scan=((hang/32)*4);
		if(hang%32){
			hang_scan+=4;
		}
		//printf("hang_scan is:%d\n",hang_scan);
		//printf("hang is:%d bit\n",hang);
		//printf("lie is:%d bit\n",lie);
		for(i=(file_size-hang_scan);i>=62;i-=hang_scan){
			print_hang(&pic_buf[i],hang);
			/*
			//inforamtion
			printf("pos %d:",i);
			if(pic_buf[i]==0)printf("0x0%d ",pic_buf[i]);
			else printf("%#X ",pic_buf[i]);
			
			*/
			printf("\r\n");
		}
		//printf("\r\n%c\r\n",'M');

		fclose(fp);
		sleep(1);
		pic_num++;
	}
	}else{
		printf("command failed\r\n");
	}
   return 0;
}

