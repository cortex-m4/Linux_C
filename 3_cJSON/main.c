#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"
#include "string.h"
#include "stdarg.h"
cJSON * root = NULL;
cJSON * item = NULL;//cjson对象
//打印json 最里层的数据
/*
void printJson(cJSON * root)                        //以递归的方式打印json的最内层键值对
{
    for(int i=0; i<cJSON_GetArraySize(root); i++)   //遍历最外层json键值对
    {
        cJSON * item = cJSON_GetArrayItem(root, i);
        if(cJSON_Object == item->type)      //如果对应键的值仍为cJSON_Object就递归调用printJson
            printJson(item);
        else                                //值不为json对象就直接打印出键和值
        {
            printf("%s->",item->string);
            printf("%s\n",cJSON_Print(item));
        }
    }
}
*/
/*
{
    "semantic": {
        "slots":    {
            "name": "张三"
        }
    },
    "rc":   0,
    "operation":    "CALL",
    "service":  "telephone",
    "text": "打电话给张三"
}
*/
//抓包
/*
	input_dat:输入的数据 必须是Json数据
	target_dat:目标捕获数据的内容
    layer:抓取报文的层数
    ...要抓的分层
*/
void get_json_pakage(char *input_dat,char *target_data,unsigned char layer,...){

    va_list valist;
    unsigned char i;
    va_start(valist,layer);
    root = cJSON_Parse(input_dat);
    printf("初始化valist\r\n");
    for(i=0;i<layer;i++){
        printf("%d\r\n",i);
        root = cJSON_GetObjectItem(root,va_arg(valist,char *));
    }
    va_end(valist);
    printf("结束va\r\n");
	strcpy(target_data,root->valuestring);
    printf("cpy target 字符串\r\n");
}
//解包
int main()
{
    char * json_str = "{\"status\":200,\"message\":null,\"data\":{\"rel\":1,\"relCode\":0,\"deviceSecret\":\"f091ee20562aff5768ca91b01c5de43e\",\"deviceName\":\"4e0aUETrJ4PZCUh8A471Vl\",\"productKey\":\"a1hGhCIRMxR\",\"version\":\"1\",\"port\":0,\"binSize\":0,\"crc\":0,\"filepath\":\"\"},\"rel\":true}";

    char json_outstr[30]={0};  //输出的目标值
	
	char *test_char;
	
	int test_int=250;
	
	int sprintf_size=0;

    root = cJSON_Parse(json_str);
    if(!root)
    {
        printf("Error before: %s\n",cJSON_GetErrorPtr());
    }
    else
    {
        printf("%s\n", "有格式的方式打印Json:");
        printf("%s\n\n", cJSON_Print(root));
        printf("%s\n", "无格式方式打印json：");
        printf("%s\n\n", cJSON_PrintUnformatted(root));

        printf("开始抓包:\r\n");
        memset(json_outstr,0,strlen(json_outstr));
        get_json_pakage(json_str,json_outstr,2,"data","deviceSecret");
        printf("target data:%s\r\n",json_outstr);
        memset(json_outstr,0,strlen(json_outstr));
        get_json_pakage(json_str,json_outstr,2,"data","deviceName");
        printf("target data:%s\r\n",json_outstr);
        memset(json_outstr,0,strlen(json_outstr));
        get_json_pakage(json_str,json_outstr,2,"data","productKey");
        printf("target data:%s\r\n",json_outstr);

        //看一下cjson对象的结构体中这两个成员的意思
        //printf("%s:", item->string);            //  
        //printf("%s\n", item->valuestring);      //

        //printf("\n%s\n", "打印json所有最内层键值对:");
        //printJson(root);

        printf("\r\n第一个出现{的位置为%d\r\n",strchr(json_str,'{'));
        printf("\r\n最后一个出现}的位置为%d\r\n",strrchr(json_str,'}'));
		test_char=(char *)malloc(32);
		sprintf_size=sprintf(test_char,"num is %d\r\n",test_int);
		printf("data is:%s\r\n",test_char);
		free(test_char);
		printf("sprintf_size is %d",sprintf_size);
    }
    return 0;
}