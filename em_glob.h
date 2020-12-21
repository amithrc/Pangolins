#ifndef PANGOLINS_EM_GLOB_H
#define PANGOLINS_EM_GLOB_H

#include "em_thread.h"
#include "em_defs.h"
#include "em_glob.h"
#include "em_queue.h"

#define EM_MAX_QUEUE 0x8

/* Global queue used for the app */
enum em_queues
{
    EM_GENERAL_QUEUE  = 0x0,
    EM_UNUSED_QUEUE_1 = 0x1,
    EM_UNUSED_QUEUE_2 = 0x2,
    EM_UNUSED_QUEUE_3 = 0x3,
    EM_UNUSED_QUEUE_4 = 0x4,
    EM_UNUSED_QUEUE_5 = 0x5,
    EM_UNUSED_QUEUE_6 = 0x6,
    EM_UNUSED_QUEUE_7 = 0x7
};

typedef struct S_EM_GLOB{
    /* Maximum thread data structure       */
    T_EM_THREAD threads[EM_MAX_THREAD];
#define em_threads em_glob.threads

    /* Queue list used for the application */
    Queue       _queue_list[EM_MAX_QUEUE];
#define queue_list em_glob._queue_list

}T_EM_GLOB;

T_EM_GLOB em_glob;
#endif //PANGOLINS_EM_GLOB_H
