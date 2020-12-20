#ifndef PANGOLINS_EM_GLOB_H
#define PANGOLINS_EM_GLOB_H

#include "em_thread.h"
#include "em_defs.h"
#include "em_glob.h"
#include "em_generic_queue.h"

typedef struct S_EM_GLOB{
    /* Maximum thread data structure */
    T_EM_THREAD threads[EM_MAX_THREAD];
#define em_threads em_glob.threads

    UINT64      thread_count;
#define em_thrd_count em_glob.thread_count

}T_EM_GLOB;

T_EM_GLOB em_glob;
#endif //PANGOLINS_EM_GLOB_H
