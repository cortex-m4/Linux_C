#include "stdio.h"


int main(){
	char dat;
	char dat2;
	while(1){
	//scanf("%c",&dat);
	dat=getchar();
	//scanf("%c",&dat2);
	dat2=getchar();
	printf("dat:%c\n",dat);
	printf("dat2:%c\n",dat2);
	if(dat=='q')break;
	}
	return 0;
}
