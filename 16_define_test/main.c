#include "stdio.h"

#define INPUT_PARAM	3,4


int getAdd(int a,int b){
	return a+b;
}


int main(void){
	int sum;
	sum=getAdd(INPUT_PARAM);
	printf("sum is %d\r\n",sum);
}


