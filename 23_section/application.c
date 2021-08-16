#include "section.h"
#include "stdio.h"





static int task_handler_init(void){
    printf("%s\n",__FUNCTION__);
}


__application_init(task_handler_init,0);



