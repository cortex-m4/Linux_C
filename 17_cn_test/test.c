
#include "stdio.h" 
#include "string.h"
//char ch1[] = {-28,-67,-96,-27,-91,-67};
char ch1[10] = {0};
typedef union
{
  int integer;   /* 整数 */
  float  point;       /* 浮点数 */
  unsigned int uint;
}Packet_t;

void func(char *param){
	int i;
	memset(ch1,0,10);
	memcpy(ch1,"你好",10);
	while(1){
		printf("%c", *param++);
		if(*param==0)break;
	}
}
int main()
{
  Packet_t packet = { 0 };
  packet.integer = 0x40900000;
  printf("packet.integer = %d\r\n", packet.integer);
  printf("packet.point = %f\r\n", packet.point);
  printf("packet.uint = %#x\r\n", packet.uint);
  printf("ch1=%s\r\n",ch1);
  printf("chinese:");
  func(ch1);
  return 0;
}