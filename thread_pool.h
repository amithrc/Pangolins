#ifndef PANGOLINS_THREAD_POOL_H
#define PANGOLINS_THREAD_POOL_H

#include "common_defs.h"

typedef struct THREAD{

}T_THREAD;


typedef struct S_THREAD_POOL{
    UINT16   num_of_threads;
    T_THREAD threads;

}T_THREAD_POOL;
#endif //PANGOLINS_THREAD_POOL_H
