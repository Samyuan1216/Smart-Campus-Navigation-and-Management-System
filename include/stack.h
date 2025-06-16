#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

#define STACK_LENGTH 100

typedef struct _Stack *Stack;
struct _Stack
{
    int *A;
    int top;
};

Stack New_Stack();
bool Is_Empty_Stack(Stack S);
bool Is_Full_Stack(Stack S);
int Pop(Stack S);
void Push(Stack S, int x);

#endif //_STACK_H_