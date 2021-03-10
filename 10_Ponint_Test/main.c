#include "stdio.h"
#include "string.h"
#define UART_BUF_LEN	128
char uartRxBuf[UART_BUF_LEN]={0};
void LoadUartData(char *dat){
	int i;
	for(i=0;i<UART_BUF_LEN;i++){
		*dat=i;
		dat++;
	}
}
void ReadDataTest(char *dat,unsigned int len){
	memcpy(dat,uartRxBuf+2,len);
}
void SecondReadData(char *dat){
	ReadDataTest(dat,34);
}
void main(){
	char dataBuf[34]={0};
	int i=0;
	//auto load input data buf
	LoadUartData(uartRxBuf);
	//cpy data
	SecondReadData(dataBuf);
	//display data
	printf("\nstart print data\n");
	printf("\r\n");
	for(i=0;i<34;i++){
		printf("%d,",dataBuf[i]);
	}
	printf("\r\n");
}


