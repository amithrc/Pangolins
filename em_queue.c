#include <string.h>
#include <stdlib.h>
#include "em_queue.h"


T_QUEUE_RET static enqueue_internal(Queue * p_queue,void * p_data);
T_QUEUE_RET static dequeue_internal(Queue * p_queue,void * p_ret);

/***
 * Init the queue based on the memsize for the data and the queue lock
 * @param p_queue
 * @param q_memsize
 * @param lock_type
 */
void qinit(Queue *p_queue,size_t q_memsize,T_LOCK_TYPE lock_type)
{
    if(p_queue) {
        memset(p_queue,0,sizeof(Queue));
        p_queue->front     = NULL;
        p_queue->rear      = NULL;
        p_queue->q_memsize = q_memsize;
        p_queue->q_size    = 0;
        p_queue->lock_type = E_NO_LOCK;

        switch(lock_type)
        {
            case E_MUTX_LOCK: { pthread_mutex_init(&p_queue->lock.qmutx_lock,NULL); break; }
            case E_SPIN_LOCK: { pthread_spin_init(&p_queue->lock.qspin_lock,0); break; }
            case E_NO_LOCK:
                break;
        }
    }
}
/***
 * Enqueue the data into the queue
 * @param p_queue
 * @param p_data
 * @return
 */
T_QUEUE_RET static enqueue_internal(Queue * p_queue,void * p_data)
{
    if( p_queue == NULL )
        return E_QUEUE_INVALID;

    ELEM *elem = (ELEM *) malloc(sizeof(ELEM));

    if(PREDICT_FALSE( elem == NULL)) return E_QUEUE_MEM_FAIL;
    elem->q_data = malloc(p_queue->q_memsize);
    if(PREDICT_FALSE( elem->q_data == NULL) ) return E_QUEUE_MEM_FAIL;

    elem->q_next= NULL;
    memcpy(elem->q_data,p_data,p_queue->q_memsize); //copy the data
    if(IS_QUEUE_EMPTY(p_queue))
    {
        p_queue->front = p_queue->rear = elem;
    }else
    {
        p_queue->rear->q_next = elem;
        p_queue->rear = elem;
    }
    p_queue->q_size ++;

    return E_QUEUE_SUCCESS;
}

T_QUEUE_RET static dequeue_internal(Queue * p_queue,void * p_ret)
{
    if(PREDICT_FALSE( (p_queue == NULL) || (!IS_QUEUE_EMPTY(p_queue)) ) )
    {
        return E_QUEUE_EMPTY;
    }
    ELEM *p_dequeue = p_queue->front;
    if(p_queue->q_size == 0x1 )
    {
        p_queue->front  = p_queue->rear = NULL;
        goto exit;
    }else
    {
        p_queue->front = p_queue->front->q_next;
        goto exit;
    }

    exit:
        memcpy(p_ret,p_dequeue->q_data,p_queue->q_memsize);
        free(p_dequeue->q_data);
        free(p_dequeue);
        p_queue->q_size--;

    return E_QUEUE_SUCCESS;
}

bool enqueue(Queue * p_queue,void * p_data)
{
    return ( ( enqueue_internal(p_queue,p_data) == E_QUEUE_SUCCESS )? TRUE :FALSE );
}

bool dequeue(Queue * p_queue,void * p_data)
{
    return ( ( dequeue_internal(p_queue,p_data) == E_QUEUE_SUCCESS )? TRUE :FALSE);
}

size_t qsize(Queue * p_queue)
{
    return p_queue->q_size;
}

void   peek(Queue * p_queue, void * p_peek)
{

}