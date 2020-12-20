#ifndef PANGOLINS_EM_THREAD_H
#define PANGOLINS_EM_THREAD_H

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

/******************************** Acronyms *******************************
 * EM - Execution model
 * WU - Work units


*************************************************************************/

#define EM_MAX_THRD_NAME   40
#define EM_MAX_THREAD      20

typedef struct S_EM_THREAD
{
    char           thrd_name[EM_MAX_THRD_NAME];
    pthread_t      tid;
    pthread_attr_t attr;
}T_EM_THREAD;


void print_counter();
#endif //PANGOLINS_EM_THREAD_H
