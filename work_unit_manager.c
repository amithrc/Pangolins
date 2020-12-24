#include <string.h>

#include "work_unit_manager.h"
#include "globals.h"



void  init_globals(void)
{
    MAX_QUEUE_ELEM = 0x1000;
    memset( &queues, 0, sizeof(QUEUE) * MAX_QUEUE);


}












