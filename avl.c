#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "fifo.h"

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

AVL create_empty_AVL()
{
    return NULL;
}

int is_empty_avl(AVL t)
{
    if(t == NULL)
        return 1;
    return 0;
}

int is_leaf_avl(AVLNode* n)
{
    if(n->ls == NULL && n->rs == NULL)
        return 1;
    return 0;
}

AVLNode* create_node_avl(Elmt_t * data)
{
    AVLNode* n = (AVLNode*)malloc(sizeof(AVLNode));
    if(n == NULL)
        return NULL;
    n->data = data;
    n->ls = NULL;
    n->rs = NULL;
    n->bf = 0;
    return n;
}

void rotate_right_avl(AVL* a)
{
    AVL b = (*a)->ls;
    int a_bf = (*a)->bf;
    int b_bf = b->bf;
    
    (*a)->ls = b->rs;
    b->rs = *a;
    
    (*a)->bf = a_bf - min(b_bf, 0) + 1;
    b->bf = max(max(a_bf + 2, a_bf + b_bf + 2), b_bf + 1);
    
    *a = b;
}

void rotate_left_avl(AVL* a)
{
    AVL b = (*a)->rs;
    int a_bf = (*a)->bf;
    int b_bf = b->bf;
    
    (*a)->rs = b->ls;
    b->ls = *a;
    
    (*a)->bf = a_bf - max(b_bf, 0) - 1;
    b->bf = min(min(a_bf - 2, a_bf + b_bf - 2), b_bf - 1);
    
    *a = b;
}

void balance(AVL* a)
{
    if((*a)->bf == 2)
    {
        if((*a)->rs->bf < 0)
        {
            rotate_right_avl(&((*a)->rs));
        }
        rotate_left_avl(a);
        return;
    }
    
    if((*a)->bf == -2)
    {
        if((*a)->ls->bf > 0)
        {
            rotate_left_avl(&((*a)->ls));
        }
        rotate_right_avl(a);
        return;
    }
}

int add_avl(Elmt_t* x, AVL* t, int (*compare_elmt)(Elmt_t*, Elmt_t*))
{
    int h = 0;
    
    if(is_empty_avl(*t))
    {
        AVLNode* n = create_node_avl(x);
        *t = n;
        return 1;
    }
    
    int cmp = compare_elmt(x, (*t)->data);
    
    if(cmp < 0)
    {
        h = add_avl(x, &((*t)->ls), compare_elmt);
        h = -h;
    }
    else if(cmp > 0)
    {
        h = add_avl(x, &((*t)->rs), compare_elmt);
    }
    else
    {
        return 0;
    }
    
    if(h == 0)
        return 0;
    
    (*t)->bf = (*t)->bf + h;
    balance(t);
    
    if((*t)->bf == 0)
        return 0;
    return 1;
}

void visit_prefix_avl(AVL t, void (*action)(AVL*))
{
    if(t == NULL)
        return;
    
    action(&t);
    visit_prefix_avl(t->ls, action);
    visit_prefix_avl(t->rs, action);
}

void visit_infix_avl(AVL t, void (*action)(AVL*))
{
    if(t == NULL)
        return;
    
    visit_infix_avl(t->ls, action);
    action(&t);
    visit_infix_avl(t->rs, action);
}

void visit_postfix_avl(AVL t, void (*action)(AVL*))
{
    if(t == NULL)
        return;
    
    visit_postfix_avl(t->ls, action);
    visit_postfix_avl(t->rs, action);
    action(&t);
}

void visit_bf_avl(AVL t, void (*action)(AVL*))
{
    Fifo f = create_fifo();
    fifo_add(&f, t);
    
    while(!is_empty(f))
    {
        AVL b = (AVL)fifo_get(&f);
        if(b == NULL)
            continue;
        fifo_add(&f, b->ls);
        fifo_add(&f, b->rs);
        action(&b);
    }
}

void print_root_avl(AVL* t)
{
    printf(" %d ",*((*t)->data));
}

void print_prefix_avl(AVL t)
{
    visit_prefix_avl(t, &print_root_avl);
}

void print_infix_avl(AVL t)
{
    visit_infix_avl(t, &print_root_avl);
}

void print_postfix_avl(AVL t)
{
    visit_postfix_avl(t, &print_root_avl);
}

void print_bf_avl(AVL t)
{
    visit_bf_avl(t, &print_root_avl);
}

void free_node_avl(AVL * t)
{
    free(*t);
    *t = NULL;
}

void free_AVL(AVL * t)
{
    visit_postfix_avl(*t, &free_node_avl);
    *t = NULL;
}
