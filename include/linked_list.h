#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct _List *List;
typedef List PtrToList;

struct _List
{
    char *name;
    int time[2][2];
    PtrToList next;
};

void Print_Active(List L);
int Compare_Time(List a, List b);
List Sort_Active(List L);
void QuickSort(List A[], int p, int r);
int Partition(List A[], int p, int r);

#endif //_LINKED_LIST_H_