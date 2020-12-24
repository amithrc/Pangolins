#ifndef PANGOLINS_QUEUE_H
#define PANGOLINS_QUEUE_H


/*  ======================================================================================
                        A generic version of the queue implementation
                                    Thread safe queue
   ======================================================================================= */

/* ================================ Standard includes ===================================== */
#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>
/* ================================= User includes ========================================= */
#include "common_defs.h"

/* ==================================== Defines ============================================ */
#define MAX_QUEUE      0x10

#define TAKE_QUEUE_LOCK(p_queue) if(IS_MUTX_LOCK(p_queue->lock_type) )               \
                                 {                                                   \
                                   pthread_mutex_lock(&p_queue->lock.mutx.mutex_l);  \
                                 }                                                   \
                                 else if(IS_SPIN_LOCK(p_queue->lock_type))           \
                                 {                                                   \
                                   pthread_spin_lock(&p_queue->lock.spin.spin_l);    \
                                 }                                                   \
                                 else                                                \
                                 {                                                   \
                                    ;                                                \
                                 }

#define RELEASE_QUEUE_LOCK(p_queue)  if(IS_MUTX_LOCK(p_queue->lock_type) )                \
                                     {                                                    \
                                       pthread_mutex_unlock(&p_queue->lock.mutx.mutex_l); \
                                     }                                                    \
                                     else if(IS_SPIN_LOCK(p_queue->lock_type))            \
                                     {                                                    \
                                       pthread_spin_unlock(&p_queue->lock.spin.spin_l);   \
                                     }                                                    \
                                     else                                                 \
                                     {                                                    \
                                        ;                                                 \
                                     }

typedef enum
{
    DefineOptions(NO_LOCK,             0),
    DefineOptions(MUTX_LOCK,           1),
    DefineOptions(SPIN_LOCK,           2),
    DefineOptions(NO_LOCK_FOR_SIZE,    3),
    DefineOptions(LOCAL_MAX_QUEUE_SIZE,4),
    DefineOptions(UNBOUNDED_QUEUE,     5)
}E_QUEUE_OPTION;

#define QUEUE_USING_MUTX_LOCK(queue_options)    ( queue_options & M_MUTX_LOCK )
#define QUEUE_USING_SPIN_LOCK(queue_options)    ( queue_options & M_SPIN_LOCK )
#define IS_NO_LOCK_FOR_SIZE(queue_options)      ( queue_options & M_NO_LOCK_FOR_SIZE )
#define USE_LOCK_QUEUE_MAX_ELEM(queue_options)  ( queue_options & M_LOCAL_MAX_QUEUE_SIZE )
#define IS_UNBOUNDED_QUEUE(queue_options)       ( queue_options & M_UNBOUNDED_QUEUE)

#define GET_MAX_QUEUE_SIZE(p_queue) (USE_LOCK_QUEUE_MAX_ELEM(p_queue->queue_options)) ? p_queue->queue_max_elem :MAX_QUEUE_ELEM;
#define QUEUE_IS_EMPTY(p_queue) ( p_queue->queue_size == 0x0 )
enum E_QUEUE
{
    UNUSED_QUEUE_0 = 0x0,
    UNUSED_QUEUE_1 = 0x1,
    UNUSED_QUEUE_2 = 0x2,
    UNUSED_QUEUE_3 = 0x3,
    UNUSED_QUEUE_4 = 0x4,
    UNUSED_QUEUE_5 = 0x5,
    UNUSED_QUEUE_6 = 0x6,
    UNUSED_QUEUE_7 = 0x7,
    UNUSED_QUEUE_8 = 0x8,
    UNUSED_QUEUE_9 = 0x9,
    UNUSED_QUEUE_A = 0xA,
    UNUSED_QUEUE_B = 0xB,
    UNUSED_QUEUE_C = 0xC,
    UNUSED_QUEUE_D = 0xD,
    UNUSED_QUEUE_E = 0xE,
    UNUSED_QUEUE_F = 0xF
};

typedef struct S_ELEM
{
#define ELEM struct S_ELEM
    void*  data;
    ELEM*  next;
}T_ELEM;

typedef struct S_QUEUE
{
#define QUEUE struct S_QUEUE
    size_t queue_size;
    size_t queue_max_elem;
    size_t elem_size;
    ELEM*  front;
    ELEM*  rear;
    union{
        struct s_mutx
        {
            pthread_mutex_t       mutex_l;
            pthread_mutexattr_t   attr;
        }mutx;

        struct s_spin
        {
            pthread_spinlock_t spin_l;
            int                shared;
        }spin;
    }lock;
    UINT32    queue_options;
    LOCK_TYPE lock_type;
}T_QUEUE;

/* ==================================== prototypes ============================================ */
bool init_queue( QUEUE* p_queue,
                 size_t size,
                 size_t elem_size,
                 E_QUEUE_OPTION queue_options);

bool enqueue_elem(QUEUE* p_queue,
                  void*  p_elem );

bool dequeue_elem(QUEUE* p_queue,
                  void*  p_elem);

size_t get_queue_size(QUEUE* p_queue,bool lock);

bool free_queue_elements(QUEUE* p_queue);
bool destroy_queue(QUEUE* p_queue);


#endif //PANGOLINS_QUEUE_H
