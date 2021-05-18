
#include "main.h"
#include "string.h"

int main(void){
    int i;
    double temp_1,temp_2,temp_3,temp_4;
    char *car;
    printf("========pb encode start======\r\n");
    encode_buffer();
    printf("output:");
    for(i=0;i<1024;i++){
        printf("%#X,",pb_buffer[i]);
    }

    
    printf("\r\n========pb decode start======\r\n");
    decode_buffer();
    temp_1=_hgf_temp_status_unpack.temp1;
    temp_2=_hgf_temp_status_unpack.temp2;
    temp_3=_hgf_temp_status_unpack.temp3;

    printf("temp1=%f\r\n",temp_1);
    printf("temp2=%f\r\n",temp_2);
    printf("temp3=%f\r\n",temp_3);

    printf("car_num=%s\r\n",_hgf_temp_status_unpack.nowCarNum);
    //目前不知道字符串如何打印
}

