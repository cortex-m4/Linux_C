#include "section.h"
#include "stdio.h"

static int app2(void){
    printf("%s\n",__FUNCTION__);
}


__application_init(app2,0);


