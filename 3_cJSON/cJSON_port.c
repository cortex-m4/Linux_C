#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <rtthread.h>

#include "cJSON.h"

int cJSON_hook_init(void)
{
    cJSON_Hooks cJSON_hook;

    cJSON_hook.malloc_fn = (void *(*)(size_t ))malloc;
    cJSON_hook.free_fn = free;
  //  cJSON_hook.reallocate_fn = (void *(*)(void *, size_t ))rt_realloc;

    cJSON_InitHooks(&cJSON_hook);

    return 1;
}
//INIT_PREV_EXPORT(cJSON_hook_init);

