#ifndef PANGOLINS_EM_QUEUE_H
#define PANGOLINS_EM_QUEUE_H

#include <stdbool.h>
#include <pthread.h>
#include "em_defs.h"

#define IS_QUEUE_EMPTY(p_queue) ( p_queue->q_size == 0x0 )

typedef enum E_QUEUE_RET {
    E_QUEUE_SUCCESS   = 0x0,
    E_QUEUE_FAILURE   = 0x1,
    E_QUEUE_INVALID   = 0x2,
    E_QUEUE_EMPTY     = 0x3,
    E_QUEUE_MEM_FAIL  = 0x4,
}T_QUEUE_RET;

typedef struct S_EM_ELEM
{
#define ELEM struct S_EM_ELEM
    void  * q_data;
    ELEM  * q_next;
}T_EM_ELEM  __attribute__ ((aligned (8))) ;

typedef struct S_EM_QUEUE
{
#define Queue struct S_EM_QUEUE
    ELEM       * front;
    ELEM       * rear;
    size_t       q_size;
    size_t       q_memsize;
    T_LOCK_TYPE  lock_type;
    union {
        pthread_mutex_t     qmutx_lock;
        pthread_spinlock_t  qspin_lock;
    }lock;
}T_EM_QUEUE  __attribute__ ((aligned (8))) ;

bool   enqueue(Queue * p_queue,void * p_data);
bool   dequeue(Queue * p_queue,void * p_ret);
size_t qsize(Queue * p_queue);
void   qdestroy(Queue *p_queue);
bool   peek(Queue * p_queue, void * p_peek);
void   qinit(Queue *p_queue,size_t q_memsize,T_LOCK_TYPE lock_type);

#endif //PANGOLINS_EM_QUEUE_H
