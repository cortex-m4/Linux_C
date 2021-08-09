#include <stdio.h>
#include <string.h>

#define __app_init_section      __attribute__((section(".usri_fn.")))

#define MODE1   1

#if     MODE1
    typedef struct{
        int (*func)(void);
        char *name;
    }_s_application_init;

    #define __application_init(function,funcName) \
        _s_application_init _s_a_init_##function  __app_init_section={function,funcName}

    _s_application_init _init_start;//��".application_init"����ʼ��ַ����*.lds�ļ��ж���
    _s_application_init _init_end;//��".application_init"��ĩβ��ַ����*.lds�ļ��ж���
#else
    typedef int (*_s_application_init)(void);

    #define __application_init(function) \
        _s_application_init _s_a_init_##function  __app_init_section=function
        
    _s_application_init _init_start;//��".application_init"����ʼ��ַ����*.lds�ļ��ж���
    _s_application_init _init_end;//��".application_init"��ĩβ��ַ����*.lds�ļ��ж���

#endif






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
    __application_init(application_start);

    __application_init(application_init_a);

    __application_init(application_init_b);

    __application_init(application_init_c);

    __application_init(application_end);

#endif
 
int main(int argc, char **argv)
{
    /*
     * �Ӷε���ʼ��ַ��ʼ��ȡ���ݣ�ֱ��ĩβ��ַ
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
