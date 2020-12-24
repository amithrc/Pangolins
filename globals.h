
#ifndef PANGOLINS_GLOBALS_H
#define PANGOLINS_GLOBALS_H

#include "common_defs.h"
#include "queue.h"

typedef struct S_GLOB {
    size_t   _max_queue_size;
#define MAX_QUEUE_ELEM glob._max_queue_size

    QUEUE    _queues[MAX_QUEUE];
#define queues glob._queues

}T_GLOB;

T_GLOB glob;
#endif //PANGOLINS_GLOBALS_H
