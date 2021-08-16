

#include "stdio.h"

#define FWID	1000

int get_fwid(char *ch){
	sprintf(ch,"%d",FWID);
	return strlen(ch);
}


int main(void){
	
	int len;
	char fwid[4];
	len=get_fwid(fwid);
	printf("fwid:%s\r\nlen:%d\r\n",fwid,len);


}

