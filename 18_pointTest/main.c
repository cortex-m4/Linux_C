#include "stdio.h"

int main(){
	extern int a[];
	printf("&a is:%d\n",&a);
	printf("a is:%d\n",a);
	printf("*a is:%d\n",*a);
}
