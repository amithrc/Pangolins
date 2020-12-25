#ifndef PANGOLINS_THREAD_POOL_H
#define PANGOLINS_THREAD_POOL_H

#include <pthread.h>

#include "common_defs.h"

/* Function pointer */
typedef void* (*function_p)(void*);

#define THREAD_MAX_NAME 40

typedef struct THREAD{
    char            thread_name[THREAD_MAX_NAME];
    pthread_t       thread_id;
    pthread_attr_t  attr;
}T_THREAD __attribute__ ((aligned (8)));

typedef struct S_THREAD_POOL {
    volatile UINT8     total_threads;
    volatile UINT8     actv_threads;
    T_THREAD         * threads_f;     /* Pointer to the front thread  */
    T_THREAD         * threads_r;     /* Pointer to the rear  thread  */
    pthread_mutex_t    mutx_l;
    pthread_cond_t     cond_t;
}T_THREAD_POOL __attribute__ ((aligned (8)));

#endif //PANGOLINS_THREAD_POOL_H
