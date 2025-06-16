#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_LENGTH 100

typedef struct _Queue *Queue;
struct _Queue
{
    int *A;
    int head;
    int tail;
};

Queue New_Queue();
bool Is_Empty_Queue(Queue Q);
bool Is_Full_Queue(Queue Q);
void Enqueue(Queue Q, int x);
int Dequeue(Queue Q);

#endif //_QUEUE_H_