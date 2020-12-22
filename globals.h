
#ifndef PANGOLINS_GLOBALS_H
#define PANGOLINS_GLOBALS_H

#include "common_defs.h"

typedef struct S_GLOB {
    size_t   _max_queue_size;
#define MAX_QUEUE_ELEM em_glob._max_queue_size

}T_GLOB;

T_GLOB em_glob;
#endif //PANGOLINS_GLOBALS_H
