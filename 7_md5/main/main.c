#include "stdio.h"
#include "utils_md5.h"
#include "string.h"
char test_str[]={"deviceId00013230353031395105002C0026device_version_id7YmSYmlPJRll4odfE5j1rEequiptype_id2FjFncsh63dZpmrIddjCnpfirmware_version1time1603013726muyuan"};
char output_str[16]={0};
char md5_str[32]={0};
/*
    buf input data
    buflen  data long
    out output data
*/
void arrayToStr(unsigned char *buf, unsigned int buflen, unsigned char *out)
{
	unsigned char strBuf[33] = {0};
	unsigned char pbuf[32];
	unsigned char i;
	for(i = 0; i < buflen; i++)
	{
	    sprintf(pbuf, "%02X", buf[i]);
	    strncat(strBuf, pbuf, 2);
	}
	strncpy(out, strBuf, buflen * 2);
	out[buflen*2] = 0;
}

int main(void){
    int i=0;
    unsigned char buf=0;
    printf("hello,world!\r\n");
    utils_md5(test_str,strlen(test_str),output_str);
    for(i=0;i<16;i++){
        md5_str[i*2]=utils_hb2hex(output_str[i]>>4);
        md5_str[i*2+1]=utils_hb2hex(output_str[i]);
        buf=output_str[i]&0x000000ff;
        printf("%#x\r\n",buf);
    }
    //将数组 用 16 进制的方式 转换为 16进制字符串
    //arrayToStr(output_str,strlen(output_str),md5_str);
    printf("%s",md5_str);

    return 0;
}

