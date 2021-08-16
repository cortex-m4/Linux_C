#include <stdio.h>
#include <string.h>
#include "section.h"


static int application_start(void) {
    printf("init start!\n");
    return 0;
}
 
static int application_init_a(void)
{
    printf("execute funtion A\n");
    return 0;
}

 
static int application_init_b(void)
{
    printf("execute funtion B\n");
    return 0;
}

 
static int application_init_c(void)
{
    printf("execute funtion C\n");
    return 0;
}
static int application_end(void) {
    printf("init end!\n");
    return 0;
}


#if MODE1
    __application_init(application_init_a,"funA");

    __application_init(application_init_c,"funC");

    
    __application_init(application_init_b,"funB");
#else
    __application_init(application_start,0);

    __application_init(application_init_a,0);

    __application_init(application_init_b,0);
    __application_init(application_init_c,0);

     __application_init(application_end,1);

   

   

#endif
 
int main(int argc, char **argv)
{
    /*
     * 从段的起始地址开始获取数据，直到末尾地址
     */
#if MODE1
    _s_application_init *pf_init = &_init_start;
    for(pf_init;pf_init<&_init_end;pf_init++){
        if(pf_init!=NULL){
            printf("function name:%s\n", pf_init->name);
            pf_init->func();
        }else{
            break;
        }
    }
#else
    static _s_application_init *pf_init = &_s_a_init_application_start;
    for(pf_init;pf_init<&_s_a_init_application_end;pf_init++){
        if(pf_init!=NULL){
            (*pf_init)();
        }else{
            break;
        }
    }
#endif
    printf("end\n");
    return 0;
}



