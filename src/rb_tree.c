#include <stdio.h>
#include <stdlib.h>

#include "rb_tree.h"

Tree New_RB_Tree()
{
    Tree T = (Tree)malloc(sizeof(struct _Tree));
    T->Nil = (Data)malloc(sizeof(struct _Data));
    T->Nil->u = NULL;
    T->Nil->left = T->Nil;
    T->Nil->right = T->Nil;
    T->Nil->parent = T->Nil;
    T->Nil->color = Black;

    T->root = T->Nil;
    T->G = NULL;
    T->n = 0;

    return T;
}

Data New_Data(Tree T, Node x)
{
    Data d = (Data)malloc(sizeof(struct _Data));
    d->u = x;
    d->color = Red;
    d->left = T->Nil;
    d->right = T->Nil;
    d->parent = T->Nil;

    return d;
}

void RB_Inorder_Tree_Walk(Tree T, Data x)
{
    if (x != T->Nil)
    {
        RB_Inorder_Tree_Walk(T, x->left);
        printf("%2d: %s\n", x->u->u, x->u->name);
        RB_Inorder_Tree_Walk(T, x->right);
    }
}

Data RB_Search_Tree(Tree T, Data x, int key)
{
    if (key == x->u->u)
    {
        return x;
    }
    else if (key < x->u->u)
    {
        return RB_Search_Tree(T, x->left, key);
    }
    else
    {
        return RB_Search_Tree(T, x->right, key);
    }
}

Data RB_Minimum_Tree(Tree T, Data x)
{
    while (x->left != T->Nil)
    {
        x = x->left;
    }

    return x;
}

Data RB_Maximum_Tree(Tree T, Data x)
{
    while (x->right != T->Nil)
    {
        x = x->right;
    }

    return x;
}

Data RB_Successor_Tree(Tree T, Data x)
{
    if (x->right != T->Nil)
    {
        return RB_Minimum_Tree(T, x->right);
    }

    Data y = x->parent;
    while (y != T->Nil && x == y->right)
    {
        x = x->parent;
        y = y->parent;
    }

    return y;
}

Data RB_Predecessor_Tree(Tree T, Data x)
{
    if (x->left != T->Nil)
    {
        return RB_Maximum_Tree(T, x->left);
    }

    Data y = x->parent;
    while (y != T->Nil && x == y->left)
    {
        x = x->parent;
        y = y->parent;
    }

    return y;
}

void Left_Rotate(Tree T, Data x)
{
    Data y = x->right;
    x->right = y->left;

    if (y->left != T->Nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x == T->root)
    {
        T->root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }

    y->left = x;
    x->parent = y;
}

void Right_Rotate(Tree T, Data x)
{
    Data y = x->left;
    x->left = y->right;

    if (y->right != T->Nil)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == T->Nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

void RB_Insert_Tree(Tree T, Data z)
{
    Data x = T->root, y = T->Nil;
    while (x != T->Nil)
    {
        y = x;
        if (z->u->u < x->u->u)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == T->Nil)
    {
        T->root = z;
    }
    else if (z->u->u < y->u->u)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    RB_Insert_Fixup(T, z);

    T->n++;
}

void RB_Insert_Fixup(Tree T, Data z)
{
    while (z->parent->color == Red)
    {
        if (z->parent == z->parent->parent->left)
        {
            Data y = z->parent->parent->right;

            if (y->color == Red)
            {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    Left_Rotate(T, z);
                }

                z->parent->color = Black;
                z->parent->parent->color = Red;
                Right_Rotate(T, z->parent->parent);
            }
        }
        else
        {
            Data y = z->parent->parent->left;

            if (y->color == Red)
            {
                z->parent->color = Black;
                y->color = Black;
                z->parent->parent->color = Red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    Right_Rotate(T, z);
                }

                z->parent->color = Black;
                z->parent->parent->color = Red;
                Left_Rotate(T, z->parent->parent);
            }
        }
    }

    T->root->color = Black;
}

void RB_Transplant(Tree T, Data u, Data v)
{
    if (u->parent == T->Nil)
    {
        T->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

void RB_Delete_Tree(Tree T, Data z)
{
    Data x = T->Nil, y = z;
    Color y_original_color = y->color;

    if (z->left == T->Nil)
    {
        x = z->right;
        RB_Transplant(T, z, z->right);
    }
    else if (z->right == T->Nil)
    {
        x = z->left;
        RB_Transplant(T, z, z->left);
    }
    else
    {
        y = RB_Minimum_Tree(T, z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            RB_Transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        RB_Transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == Black)
    {
        RB_Delete_Fixup(T, x);
    }

    T->n--;
}

void RB_Delete_Fixup(Tree T, Data x)
{
    while (x != T->root && x->color == Black)
    {
        if (x == x->parent->left)
        {
            Data w = x->parent->right;

            if (w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;
                Left_Rotate(T, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == Black && w->right->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == Black)
                {
                    w->left->color = Black;
                    w->color = Red;
                    Right_Rotate(T, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = Black;
                w->right->color = Black;
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            Data w = x->parent->left;

            if (w->color == Red)
            {
                w->color = Black;
                x->parent->color = Red;
                Right_Rotate(T, x->parent);
                w = x->parent->left;
            }

            if (w->left->color == Black && w->right->color == Black)
            {
                w->color = Red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == Black)
                {
                    w->right->color = Black;
                    w->color = Red;
                    Left_Rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = Black;
                w->left->color = Black;
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }

    x->color = Black;
}