#include <stdlib.h>

#include "stack.h"

Stack New_Stack()
{
    Stack S = (Stack)malloc(sizeof(struct _Stack));
    S->top = 0;
    S->A = (int*)malloc(STACK_LENGTH * sizeof(int));

    return S;
}

bool Is_Empty_Stack(Stack S)
{
    if (S->top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Is_Full_Stack(Stack S)
{
    if (S->top == STACK_LENGTH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Pop(Stack S)
{
    S->top--;
    int t = S->A[S->top];

    return t;
}

void Push(Stack S, int x)
{
    S->A[S->top] = x;
    S->top++;
}