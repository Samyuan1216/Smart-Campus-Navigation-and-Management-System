#include <stdio.h>

#include "common.h"

Tree Load_Graph();
void Navigation_System(Tree T);
void Display_Graph(Tree T);
void Search_Path(Tree T);
void Search_Active(Tree T);
void Undo(Stack S, Tree T);

int main()
{
    printf("欢迎来到智慧校园导航系统~\n");
    Tree T = Load_Graph();

    Navigation_System(T);
    printf("感谢使用智慧校园导航系统~\n");

    Free_Tree(T);

    return 0;
}

Tree Load_Graph()
{
    Graph G = Read_Graph();

    if (G == NULL)
    {
        return NULL;
    }

    Tree T = New_RB_Tree();
    T->G = G;

    for (int i = 1; i <= G->n; i++)
    {
        Data d = New_Data(T, G->A[i]);
        RB_Insert_Tree(T, d);
    }

    return T;
}

void Navigation_System(Tree T)
{
    if (T == NULL)
    {
        printf("无地图信息, 无法导航xwx\n");
        return;
    }

    char y_n = '\0';
    Stack S = New_Stack();

    do
    {
        printf("\n---导航系统---\n");
        printf("1. 显示地图\n");
        printf("2. 查询路线\n");
        printf("3. 查询活动\n");
        printf("4. 进行上次操作\n");
        printf("0. 退出\n");

        printf("请选择: ");
        
        int choice = 0;
        scanf("%d", &choice);
        getchar();

        if (choice == 1 || choice == 2 || choice == 3)
        {
            Push(S, choice);
        }

        switch (choice)
        {
        case 1:
            Display_Graph(T);
            break;
        case 2:
            Search_Path(T);
            break;
        case 3:
            Search_Active(T);
            break;
        case 4:
            Undo(S, T);
            break;
        case 0:
            return;
        default:
            printf("输错啦, 参数不对!");
            break;
        }

        do
        {
            printf("是否继续(Y/n): ");
            y_n = getchar();
            getchar();
        } while (y_n != 'y' && y_n != 'Y' && y_n != 'n' && y_n != 'N');
    } while (y_n == 'y' || y_n == 'Y');

    Free_Stack(S);
}

void Display_Graph(Tree T)
{
    printf("\n---校园地图---\n");

    RB_Inorder_Tree_Walk(T, T->root);
}

void Search_Path(Tree T)
{
    int n = 0;
    printf("请输入查询条数: ");
    scanf("%d", &n);
    getchar();

    Queue Q = New_Queue();
    for (int i = 1; i <= n; i++)
    {
        int a = 0, b = 0;

        printf("请输入第%d个开始与结束的地点编号: ", i);
        scanf("%d %d", &a, &b);
        getchar();

        Enqueue(Q, a);
        Enqueue(Q, b);
    }

    while (Is_Empty_Queue(Q) == false)
    {
        int a = Dequeue(Q);
        int b = Dequeue(Q);
        Dijkstra(T->G, T->G->A[a]);

        Print_Path(T->G->A[b]);
        printf("\n");
    }

    Free_Queue(Q);
}

void Search_Active(Tree T)
{
    int n = 0;
    printf("请输入查询条数: ");
    scanf("%d", &n);
    getchar();

    Queue Q = New_Queue();
    for (int i = 1; i <= n; i++)
    {
        int a = 0;

        printf("请输入第%d个地点编号: ", i);
        scanf("%d", &a);
        getchar();

        Enqueue(Q, a);
    }

    while (Is_Empty_Queue(Q) == false)
    {
        int a = Dequeue(Q);

        List sorted_list = Sort_Active(T->G->A[a]->l);

        printf("\n这是在%s的活动\n", T->G->A[a]->name);
        Print_Active(sorted_list);
    }

    Free_Queue(Q);
}

void Undo(Stack S, Tree T)
{
    if (Is_Empty_Stack(S) == true)
    {
        printf("还没有操作过呐!\n");
        return;
    }

    int choice = Pop(S);

    switch (choice)
    {
    case 1:
        Display_Graph(T);
        break;
    case 2:
        Search_Path(T);
        break;
    case 3:
        Search_Active(T);
        break;
    }
}