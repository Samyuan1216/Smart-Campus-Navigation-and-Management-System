#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "free.h"

Graph Read_Graph()
{
    FILE *fp = fopen("data/graph", "r");

    if (fp == NULL)
    {
        printf("无法加载地图qaq\n");
        return NULL;
    }

    Graph G = (Graph)malloc(sizeof(struct _Graph));
    fscanf(fp, "%d", &G->n);
    fgetc(fp);

    G->A = (Node*)malloc((G->n + 1) * sizeof(Node));
    for (int i = 1; i <= G->n; i++)
    {
        G->A[i] = (Node)malloc(sizeof(struct _Node));
        G->A[i]->u = i;
        G->A[i]->next = NULL;
        G->A[i]->l = NULL;

        G->A[i]->name = (char*)calloc(NAME_LENGTH + 1, sizeof(char));
        fgets(G->A[i]->name, NAME_LENGTH + 2, fp);
        G->A[i]->name[strcspn(G->A[i]->name, "\n")] = '\0';

        int k = 0;
        fscanf(fp, "%d", &k);
        fgetc(fp);

        if (k > 0)
        {
            for (int j = 0; j < k; j++)
            {
                char line[256] = {};
                fgets(line, sizeof(line), fp);
                
                List t = (List)malloc(sizeof(struct _List));
                t->name = (char*)calloc(NAME_LENGTH + 1, sizeof(char));
                
                sscanf(line, "%d:%d -> %d:%d", &t->time[0][0], &t->time[0][1], &t->time[1][0], &t->time[1][1]);
                
                char *desc_start = strrchr(line, ':');

                desc_start++;
                while (*desc_start == ' ')
                {
                    desc_start++;
                }

                strncpy(t->name, desc_start, NAME_LENGTH);
                t->name[strcspn(t->name, "\n")] = '\0';

                t->next = G->A[i]->l;
                G->A[i]->l = t;
            }
        }
    }

    int m = 0;
    fscanf(fp, "%d", &m);

    for (int i = 1; i <= m; i++)
    {
        int a = 0, b = 0, w = 0;
        fscanf(fp, "%d %d %d", &a, &b, &w);

        Edge t1 = (Edge)malloc(sizeof(struct _Edge));
        t1->v = b;
        t1->w = w;
        t1->next = G->A[a]->next;
        G->A[a]->next = t1;

        Edge t2 = (Edge)malloc(sizeof(struct _Edge));
        t2->v = a;
        t2->w = w;
        t2->next = G->A[b]->next;
        G->A[b]->next = t2;
    }

    printf("成功加载%d个地点><\n", G->n);

    fclose(fp);

    return G;
}

void Dijkstra(Graph G, Node s)
{
    Initialized_Single_Source(G, s);

    Heap_G H_G = New_Heap_G(G);

    while (H_G->heap_size > 0 && H_G->A[0]->d < MAX_LENGTH)
    {
        Node u = Heap_Extract_Min_G(H_G);
        for (Edge v = u->next; v != NULL; v = v->next)
        {
            int old_d = G->A[v->v]->d;
            Relax(u, G->A[v->v], v->w);

            if (G->A[v->v]->d != old_d)
            {
                Heap_Increase_Key_G(H_G, G->A[v->v], G->A[v->v]->d);
            }
        }
    }

    Free_Heap_G(H_G);
}

void Initialized_Single_Source(Graph G, Node s)
{
    for (int i = 1; i <= G->n; i++)
    {
        G->A[i]->d = MAX_LENGTH;
        G->A[i]->parent = NULL;
    }

    s->d = 0;
}

void Relax(Node u, Node v, int w)
{
    if (v->d > u->d + w)
    {
        v->d = u->d + w;
        v->parent = u;
    }
}

void Print_Path(Node x)
{
    if (x->parent == NULL)
    {
        printf("[%s: %d分钟]", x->name, x->d);
    }
    else
    {
        Print_Path(x->parent);
        printf(" -> [%s: %d分钟]", x->name, x->d);
    }
}

Heap_G New_Heap_G(Graph G)
{
    Heap_G H_G = (Heap_G)malloc(sizeof(struct _Heap_G));
    H_G->length = G->n;

    H_G->A = (Node*)malloc(H_G->length * sizeof(Node));
    H_G->pos = (int*)malloc((H_G->length + 1) * sizeof(int));
    for (int i = 0; i < G->n; i++)
    {
        H_G->A[i] = G->A[i + 1];
        H_G->pos[G->A[i + 1]->u] = i;
    }

    Build_Min_Heap_G(H_G);

    return H_G;
}

void Build_Min_Heap_G(Heap_G H_G)
{
    H_G->heap_size = H_G->length - 1;
    for (int i = (H_G->heap_size - 1) / 2; i >= 0; i--)
    {
        Min_Heapify_G(H_G, i);
    }
}

void Min_Heapify_G(Heap_G H_G, int i)
{
    int l = Left(i), r = Right(i), min = 0;
    
    if (l <= H_G->heap_size && H_G->A[l]->d < H_G->A[i]->d)
    {
        min = l;
    }
    else
    {
        min = i;
    }

    if (r <= H_G->heap_size && H_G->A[r]->d < H_G->A[min]->d)
    {
        min = r;
    }

    if (min != i)
    {
        Node temp = H_G->A[i];
        H_G->A[i] = H_G->A[min];
        H_G->A[min] = temp;

        H_G->pos[H_G->A[min]->u] = min;
        H_G->pos[H_G->A[i]->u] = i;

        Min_Heapify_G(H_G, min);
    }
}

Node Heap_Extract_Min_G(Heap_G H_G)
{
    Node t = H_G->A[0];
    H_G->A[0] = H_G->A[H_G->heap_size];
    H_G->heap_size--;

    Min_Heapify_G(H_G, 0);

    return t;
}

void Heap_Increase_Key_G(Heap_G H_G, Node u, int key)
{
    for (int i = H_G->pos[u->u]; i > 0 && H_G->A[i]->d < H_G->A[Parent(i)]->d; i = Parent(i))
    {
        Node temp = H_G->A[i];
        H_G->A[i] = H_G->A[Parent(i)];
        H_G->A[Parent(i)] = temp;

        H_G->pos[H_G->A[i]->u] = i;
        H_G->pos[H_G->A[Parent(i)]->u] = Parent(i);
    }
}

int Left(int i)
{
    return i * 2 + 1;
}

int Right(int i)
{
    return (i + 1) * 2;
}

int Parent(int i)
{
    return (i - 1) / 2;
}