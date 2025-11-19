#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "fifo.h"

BST create_empty_BST()
{
    return NULL;
}

int is_empty_bst(BST t)
{
    if(t == NULL)
        return 1;
    return 0;
}

int is_leaf(BSTNode* n)
{
    if(n->ls == NULL && n->rs == NULL)
        return 1;
    return 0;
}

BSTNode* create_node(Elmt_t * data)
{
    BSTNode* n = (BSTNode*)malloc(sizeof(BSTNode));
    if(n == NULL)
        return NULL;
    n->data = data;
    n->ls = NULL;
    n->rs = NULL;
    return n;
}

void add(Elmt_t* x, BST* t, int (*compare_elmt)(Elmt_t*, Elmt_t*))
{
    if(is_empty_bst(*t))
    {
        BSTNode* n = create_node(x);
        *t = n;
        return;
    }
    
    int cmp = compare_elmt(x, (*t)->data);
    
    if(cmp < 0)
    {
        add(x, &((*t)->ls), compare_elmt);
        return;
    }
    else if(cmp > 0)
    {
        add(x, &((*t)->rs), compare_elmt);
        return;
    }
    else
    {
        return;
    }
}

void visit_prefix(BST t, void (*action)(BST*))
{
    if(t == NULL)
        return;
    
    action(&t);
    visit_prefix(t->ls, action);
    visit_prefix(t->rs, action);
}

void visit_infix(BST t, void (*action)(BST*))
{
    if(t == NULL)
        return;
    
    visit_infix(t->ls, action);
    action(&t);
    visit_infix(t->rs, action);
}

void visit_postfix(BST t, void (*action)(BST*))
{
    if(t == NULL)
        return;
    
    visit_postfix(t->ls, action);
    visit_postfix(t->rs, action);
    action(&t);
}

void visit_bf(BST t, void (*action)(BST*))
{
    Fifo f = create_fifo();
    fifo_add(&f, t);
    
    while(!is_empty(f))
    {
        BST b = (BST)fifo_get(&f);
        if(b == NULL)
            continue;
        fifo_add(&f, b->ls);
        fifo_add(&f, b->rs);
        action(&b);
    }
}

void print_root(BST* t)
{
    printf(" %d ",*((*t)->data));
}

void print_prefix(BST t)
{
    visit_prefix(t, &print_root);
}

void print_infix(BST t)
{
    visit_infix(t, &print_root);
}

void print_postfix(BST t)
{
    visit_postfix(t, &print_root);
}

void print_bf(BST t)
{
    visit_bf(t, &print_root);
}

void rotate_right(BST* a)
{
    BST b = (*a)->ls;
    (*a)->ls = b->rs;
    b->rs = *a;
    *a = b;
}

void rotate_left(BST* a)
{
    BST b = (*a)->rs;
    (*a)->rs = b->ls;
    b->ls = *a;
    *a = b;
}

void free_node(BST * t)
{
    free(*t);
    *t = NULL;
}

void free_BST(BST * t)
{
    visit_postfix(*t, &free_node);
    *t = NULL;
}
