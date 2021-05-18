#include <stdio.h>
#include "string.h"
#include "stdlib.h"

#define BUFF_SIZE	64
int main()
{

	FILE *fpW = NULL;
	FILE *fpR = NULL; 
	size_t result;
	char buff[BUFF_SIZE];      //读取数据暂存
    
	fpR = fopen("./tmp/test.txt", "r");
	
	//查找文件开头
	fseek(fpR,0,SEEK_SET);
	
	//读取并且显示数据
	memset(buff,0,BUFF_SIZE);
	result=fread(buff,10,1,fpR);
	printf("1. num is '%s' \r\n",buff);
	printf("result is %d \n",result);
	
	memset(buff,0,BUFF_SIZE);
	result=fread(buff,27,1,fpR);
	printf("1. char is '%s' \r\n",buff);
	printf("result is %d \n",result);
	
	fclose(fpR);

   return 0;
}