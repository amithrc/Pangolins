#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    printf("Lock type: %x queueopts: %x\n",p_queue->lock_type,p_queue->queue_options);
    return true;
}

bool enqueue_elem(QUEUE* p_queue,
                  void*  p_elem ) {
    if (PREDICT_FALSE(p_queue == NULL))
        return FALSE;

    UINT32 queue_max_elem = GET_MAX_QUEUE_SIZE(p_queue);

    //Take lock
    TAKE_QUEUE_LOCK(p_queue);

    //Make sure the queue is not reached the upper bound. Allow more elements to add if its unbounded queue
    if (PREDICT_FALSE(p_queue->queue_size >= queue_max_elem &&
                      !IS_UNBOUNDED_QUEUE(p_queue->queue_options))) {
        RELEASE_QUEUE_LOCK(p_queue);
        return FALSE;
    }
    ELEM* elem_to_add = (ELEM* ) malloc(sizeof(ELEM));
    if(!elem_to_add) { //Failed to allocate memory
        RELEASE_QUEUE_LOCK(p_queue);
        return FALSE;
    }

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
    p_queue->queue_size++;

    RELEASE_QUEUE_LOCK(p_queue);
    return true;
}
bool dequeue_elem(QUEUE* p_queue,
                  void*  p_elem)
{
    if(PREDICT_FALSE(p_queue == NULL ))
        return FALSE;

    TAKE_QUEUE_LOCK(p_queue); //take lock

    //Nothing to dequeue
    if(PREDICT_FALSE(QUEUE_IS_EMPTY(p_queue)))
    {
        RELEASE_QUEUE_LOCK(p_queue);
        return false;
    }

    //Update the front to the next element of the front
    ELEM* elem_to_remove = p_queue->front;
    p_queue->front = p_queue->front->next;
    p_queue->queue_size--;

    RELEASE_QUEUE_LOCK(p_queue); //release the lock

    if(p_elem)
        memcpy(p_elem,elem_to_remove->data,p_queue->elem_size);

    free(elem_to_remove->data);
    free(elem_to_remove);

    return TRUE;
}

unsigned long get_queue_size(QUEUE* p_queue,bool lock)
{
    UINT32 size =0;
    if(lock){
        TAKE_QUEUE_LOCK(p_queue);
    }
    size = p_queue->queue_size;
    if(lock){
        RELEASE_QUEUE_LOCK(p_queue);
    }

    return size;
}
bool free_queue_elements(QUEUE* p_queue)
{
    TAKE_QUEUE_LOCK(p_queue);

    while(!QUEUE_IS_EMPTY(p_queue))
    {
        ELEM *elem = p_queue->front;
        p_queue->front = p_queue->front->next;
        free(elem->data);
        free(elem);
        p_queue->queue_size--;
    }

    RELEASE_QUEUE_LOCK(p_queue);
    return TRUE;

}
bool destroy_queue(QUEUE* p_queue)
{
    if(PREDICT_FALSE(p_queue == NULL) )
        return FALSE;

    if(!free_queue_elements(p_queue))
        return false;
    TAKE_QUEUE_LOCK(p_queue);

    if(IS_MUTX_LOCK(p_queue->lock_type))
        pthread_mutex_destroy(&p_queue->lock.mutx.mutex_l);
    else if(IS_SPIN_LOCK(p_queue->lock_type))
        pthread_spin_destroy(&p_queue->lock.spin.spin_l);
    p_queue->queue_size =   p_queue->elem_size  = 0x0;
    p_queue->front = p_queue->rear = NULL;
    p_queue->lock_type = E_NO_LOCK;
    p_queue->queue_options = 0;
    RELEASE_QUEUE_LOCK(p_queue);

    return TRUE;
}