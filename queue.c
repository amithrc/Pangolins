#include <string.h>
#include <stdlib.h>

#include "queue.h"
#include "globals.h"

/***
 * Initialize the queue
 * @param p_queue
 * @param size
 * @param elem_size
 * @param queue_options
 * @return TRUE on success FALSE otherwise
 */
bool init_queue( QUEUE* p_queue,
                 size_t max_size,
                 size_t elem_size,
                 E_QUEUE_OPTION queue_options)
{
    if(PREDICT_FALSE( p_queue == NULL ) ) return FALSE;

    memset(p_queue,0, sizeof(QUEUE));
    p_queue->front = NULL;
    p_queue->rear  = NULL;
    p_queue->elem_size = elem_size;
    p_queue->queue_size = 0;
    p_queue->queue_max_elem =  (max_size)? max_size: MAX_QUEUE_ELEM;
    p_queue->queue_options = queue_options;
    if( QUEUE_USING_MUTX_LOCK(queue_options) )
    {
        pthread_mutex_init( &p_queue->lock.mutx.mutex_l, &p_queue->lock.mutx.attr);
        p_queue->lock_type = E_MUTX_LOCK;
    }else if( QUEUE_USING_SPIN_LOCK(queue_options) )
    {
        pthread_spin_init( &p_queue->lock.spin.spin_l, p_queue->lock.spin.shared);
        p_queue->lock_type = E_SPIN_LOCK;
    }else
    {
        p_queue->lock_type = E_NO_LOCK;
    }
    return true;
}

bool enqueue_elem(QUEUE* p_queue,
                  void*  p_elem ) {
    if (PREDICT_FALSE(p_queue == NULL))
        return false;

    UINT32 queue_max_elem = GET_MAX_QUEUE_SIZE(p_queue);

    //Take lock
    QUEUE_TAKE_LOCK(p_queue)

    //Make sure the queue is not reached the upper bound. Allow more elements to add if its unbounded queue
    if (PREDICT_FALSE(p_queue->queue_size >= queue_max_elem &&
                      !IS_UNBOUNDED_QUEUE(p_queue->queue_options))) {
        return false;
    }

    ELEM* elem_to_add = (ELEM* ) malloc(sizeof(ELEM));
    if(!elem_to_add)  //Failed to allocate memory
        return false;

    elem_to_add->next = NULL;
    elem_to_add->data = (void *) malloc(p_queue->elem_size);
    memcpy(elem_to_add->data, p_elem,sizeof(p_queue->elem_size));

    //Update the linked list
    if(p_queue->queue_size == 0x0 )
    {
        p_queue->front = p_queue->rear = elem_to_add;
    }else
    {
        p_queue->rear->next = elem_to_add;
        p_queue->rear = elem_to_add;
    }
    QUEUE_RELEASE_LOCK(p_queue);
    return true;
}
bool dequeue_elem(QUEUE* queue,
                  void*  p_elem)
{

}

unsigned long get_queue_size(QUEUE* queue)
{

}

bool destroy_queue(QUEUE* queue)
{

}