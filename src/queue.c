#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
    if (q == NULL)
        return 1;
    return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
    /* TODO: put a new process to queue [q] */
    if (q->size >= MAX_QUEUE_SIZE)
        return;
    q->size++;
    q->proc[q->size - 1] = proc;
}
#ifdef MLQ_SCHED
struct pcb_t *dequeue(struct queue_t *q)
{
    /* TODO: return a pcb whose prioprity is the highest
     * in the queue [q] and remember to remove it from q
     * */
    struct pcb_t *ret_proc = NULL;

    if (!empty(q))
    {
        ret_proc = q->proc[0];
        for (int i = 0; i < q->size - 1; i++)
        {
            q->proc[i] = q->proc[i + 1];
        }
        q->size--;
    }
    return ret_proc;
}
#else
/*
 * @brief:	get the process that has the highest priority in the queue
 *          use only when disable MLQ_SCHED
 * @para:	pointer the queue need to get the process
 * @retval:	pointer to the process 
 *          NULL: queue is empty
 * */
struct pcb_t *dequeue(struct queue_t *q)
{
    struct pcb_t *ret_proc = NULL;
    int highestPriority = MAX_PRIO * 2;
    int index_proc = -1;
    for (int i = 0; i < q->size; i++)
    {
        if (q->proc[i]->priority < highestPriority)
        {
            highestPriority = q->proc[i]->priority;
            index_proc = i;
        }
    }
    
    if (index_proc == -1) return ret_proc; // queue is empty
}
#endif
