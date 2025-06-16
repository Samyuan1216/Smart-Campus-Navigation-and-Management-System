#ifndef _FREE_H_
#define _FREE_H_

#include "common.h"

void Free_List(List L);
void Free_Edges(Edge e);
void Free_Graph(Graph G);
void Free_Data(Tree T, Data x);
void Free_Tree(Tree T);
void Free_Stack(Stack S);
void Free_Queue(Queue Q);
void Free_Heap_G(Heap_G H_G);

#endif //_FREE_H_