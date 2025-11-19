#ifndef _AVL_H
#define _AVL_H

#include "Elmt.h"

typedef struct _AVLNode{
    Elmt_t * data;
    struct _AVLNode * ls;
    struct _AVLNode * rs;
    int bf;
}AVLNode;

typedef AVLNode* AVL;

AVL create_empty_AVL();
int is_empty_avl(AVL);
int is_leaf_avl(AVLNode*);
AVLNode* create_node_avl(Elmt_t *);
int add_avl(Elmt_t*, AVL*, int (*compare_elmt)(Elmt_t*, Elmt_t*));
void print_prefix_avl(AVL t);
void print_infix_avl(AVL t);
void print_postfix_avl(AVL t);
void print_bf_avl(AVL t);
void visit_prefix_avl(AVL t, void (*action)(AVL*));
void visit_infix_avl(AVL t, void (*action)(AVL*));
void visit_postfix_avl(AVL t, void (*action)(AVL*));
void visit_bf_avl(AVL t, void (*action)(AVL*));
void print_root_avl(AVL* t);
void rotate_right_avl(AVL*);
void rotate_left_avl(AVL*);
void balance(AVL*);
void free_node_avl(AVL * t);
void free_AVL(AVL * t);

int max(int a, int b);
int min(int a, int b);

#endif
