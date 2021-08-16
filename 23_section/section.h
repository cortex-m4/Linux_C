#ifndef __SECTION_H__
#define __SECTION_H__

#define MODE1   0

#if     MODE1
    #define __app_init_section      __attribute__((section(".usri_fn.0")))
    typedef struct{
        int (*func)(void);
        char *name;
    }_s_application_init;

    #define __application_init(function,funcName) \
        _s_application_init _s_a_init_##function  __app_init_section={function,funcName}

    _s_application_init _init_start;//段".application_init"的起始地址，在*.lds文件中定义
    _s_application_init _init_end;//段".application_init"的末尾地址，在*.lds文件中定义
#else
    #define __app_init_section(n)      __attribute__((section(".usri_fn."#n)))
    typedef int (*_s_application_init)(void);

    #define __application_init(function,level) \
        _s_application_init _s_a_init_##function  __app_init_section(level)=function
        
    _s_application_init _init_start;//段".application_init"的起始地址，在*.lds文件中定义
    _s_application_init _init_end;//段".application_init"的末尾地址，在*.lds文件中定义

#endif




#endif

