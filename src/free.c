#include <stdlib.h>

#include "free.h"

void Free_List(List L)
{
    while (L != NULL)
    {
        List next = L->next;
        free(L->name);
        free(L);
        L = next;
    }
}

void Free_Edges(Edge e)
{
    while (e != NULL)
    {
        Edge next = e->next;
        free(e);
        e = next;
    }
}

void Free_Graph(Graph G)
{
    if (G == NULL)
    {
        return;
    }
    
    for (int i = 1; i <= G->n; i++)
    {
        Node node = G->A[i];
        if (node != NULL)
        {
            free(node->name);
            Free_List(node->l);
            Free_Edges(node->next);
            free(node);
        }
    }
    
    free(G->A);
    free(G);
}

void Free_Data(Tree T, Data x)
{
    if (x == T->Nil)
    {
        return;
    }
    
    Free_Data(T, x->left);
    Free_Data(T, x->right);
    free(x);
}

void Free_Tree(Tree T)
{
    if (T == NULL)
    {
        return;
    }
    
    Free_Graph(T->G);
    Free_Data(T, T->root);
    
    if (T->Nil != NULL)
    {
        free(T->Nil);
    }
    
    free(T);
}

void Free_Stack(Stack S)
{
    if (S == NULL)
    {
        return;
    }

    free(S->A);
    free(S);
}

void Free_Queue(Queue Q)
{
    if (Q == NULL)
    {
        return;
    }

    free(Q->A);
    free(Q);
}

void Free_Heap_G(Heap_G H_G)
{
    if (H_G == NULL)
    {
        return;
    }
    
    free(H_G->A);
    free(H_G->pos);
    free(H_G);
}