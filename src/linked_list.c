#include <stdio.h>

#include "linked_list.h"

void Print_Active(List L)
{
    if (L == NULL)
    {
        printf("还没有活动呐qaq\n");
        return;
    }

    List x = L;
    while (x != NULL)
    {
        printf("%02d:%02d -> %02d:%02d: %s\n", x->time[0][0], x->time[0][1], x->time[1][0], x->time[1][1], x->name);
        x = x->next;
    }
}

int Compare_Time(List a, List b)
{
    if (a->time[0][0] != b->time[0][0])
    {
        return a->time[0][0] - b->time[0][0];
    }

    return a->time[0][1] - b->time[0][1];
}

List Sort_Active(List L)
{
    if (L == NULL || L->next == NULL)
    {
        return L;
    }

    List array[1000] = {};
    int count = 0;
    List cur = L;
    while (cur != NULL)
    {
        array[count] = cur;
        count++;
        cur = cur->next;
    }

    QuickSort(array, 0, count - 1);

    List sorted = array[0];
    cur = sorted;
    for (int i = 1; i < count; i++)
    {
        cur->next = array[i];
        cur = cur->next;
    }
    cur->next = NULL;

    return sorted;
}

void QuickSort(List A[], int p, int r)
{
    if (p < r)
    {
        int q = 0;

        q = Partition(A, p, r);

        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

int Partition(List A[], int p, int r)
{
    List x = A[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++)
    {
        if (Compare_Time(A[j], x) < 0)
        {
            i++;
            
            List temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    List temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    return i + 1;
}