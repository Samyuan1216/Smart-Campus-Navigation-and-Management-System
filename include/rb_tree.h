#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include "graph.h"

typedef struct _Data *Data;
typedef Data PtrToData;

typedef struct _Tree *Tree;

typedef enum
{
    Red, Black
} Color;

struct _Data
{
    Node u;
    PtrToData parent;
    PtrToData left;
    PtrToData right;
    Color color;
};

struct _Tree
{
    Data root;
    Data Nil;
    Graph G;
    int n;
};

Tree New_RB_Tree();
Data New_Data(Tree T, Node x);
void RB_Inorder_Tree_Walk(Tree T, Data x);
Data RB_Search_Tree(Tree T, Data x, int key);
Data RB_Minimum_Tree(Tree T, Data x);
Data RB_Maximum_Tree(Tree T, Data x);
Data RB_Successor_Tree(Tree T, Data x);
Data RB_Predecessor_Tree(Tree T, Data x);
void Left_Rotate(Tree T, Data x);
void Right_Rotate(Tree T, Data x);
void RB_Insert_Tree(Tree T, Data z);
void RB_Insert_Fixup(Tree T, Data z);
void RB_Transplant(Tree T, Data u, Data v);
void RB_Delete_Tree(Tree T, Data z);
void RB_Delete_Fixup(Tree T, Data x);

#endif //_RB_TREE_H_