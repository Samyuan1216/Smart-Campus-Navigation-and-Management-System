#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "linked_list.h"

#define MAX_LENGTH 10000
#define NAME_LENGTH 30

typedef struct _Node *Node;
typedef Node PtrToNode;
typedef struct _Graph *Graph;

typedef struct _Edge *Edge;
typedef Edge PtrToEdge;

typedef struct _Heap_G *Heap_G;

struct _Node
{
    int u;
    char *name;
    int d;
    PtrToEdge next;
    PtrToNode parent;
    List l;
};

struct _Graph
{
    Node *A;
    int n;
};

struct _Edge
{
    int v;
    int w;
    PtrToEdge next;
};

struct _Heap_G
{
    Node *A;
    int *pos;
    int length;
    int heap_size;
};

Graph Read_Graph();
void Dijkstra(Graph G, Node s);
void Initialized_Single_Source(Graph G, Node s);
void Relax(Node u, Node v, int w);
void Print_Path(Node x);

Heap_G New_Heap_G(Graph G);
void Build_Min_Heap_G(Heap_G H_G);
void Min_Heapify_G(Heap_G H_G, int i);
Node Heap_Extract_Min_G(Heap_G H_G);
void Heap_Increase_Key_G(Heap_G H_G, Node u, int key);
int Left(int i);
int Right(int i);
int Parent(int i);

#endif //_GRAPH_H_