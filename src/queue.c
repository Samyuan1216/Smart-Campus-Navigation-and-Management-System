#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

Queue New_Queue()
{
    Queue Q = (Queue)malloc(sizeof(struct _Queue));
    Q->head = 0;
    Q->tail = 0;
    Q->A = (int*)malloc(QUEUE_LENGTH * sizeof(int));

    return Q;
}

bool Is_Empty_Queue(Queue Q)
{
    if (Q->head == Q->tail)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Is_Full_Queue(Queue Q)
{
    if (Q->tail == Q->head - 1 || Q->head - Q->tail == QUEUE_LENGTH - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Enqueue(Queue Q, int x)
{
    Q->A[Q->tail] = x;
    Q->tail++;

    if (Q->tail == QUEUE_LENGTH)
    {
        Q->tail = 0;
    }
}

int Dequeue(Queue Q)
{
    int t = Q->A[Q->head];
    Q->head++;

    if (Q->head == QUEUE_LENGTH)
    {
        Q->head = 0;
    }

    return t;
}