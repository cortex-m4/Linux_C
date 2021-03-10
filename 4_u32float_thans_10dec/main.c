#include "stdio.h"
#include "string.h"
 
int main() 
{	
	unsigned char s[4]; 
	 
	s[0]=0x00;  //低位
	s[1]=0x00;
	s[2]=0x16;
	s[3]=0x30;  //高位
	
	float *pf1=(float*)s;
	float f2;
	memcpy(&f2 ,s ,sizeof(s));
 
	printf("结果:\r\n");
    printf("%lf\r\n",*pf1);
    printf("f2=%lf\r\n",f2);
 
	return 0;
}
