#ifndef _BST_H
#define _BST_H

#include "Elmt.h"

typedef struct _BSTNode{
    Elmt_t * data;
    struct _BSTNode * ls;
    struct _BSTNode * rs;
}BSTNode;

typedef BSTNode* BST;

BST create_empty_BST();
int is_empty_bst(BST);
int is_leaf(BSTNode*);
BSTNode* create_node(Elmt_t *);
void add(Elmt_t*, BST*, int (*compare_elmt)(Elmt_t*, Elmt_t*));
void print_prefix(BST t);
void print_infix(BST t);
void print_postfix(BST t);
void print_bf(BST t);
void visit_prefix(BST t, void (*action)(BST*));
void visit_infix(BST t, void (*action)(BST*));
void visit_postfix(BST t, void (*action)(BST*));
void visit_bf(BST t, void (*action)(BST*));
void print_root(BST* t);
void rotate_right(BST*);
void rotate_left(BST*);
void free_node(BST * t);
void free_BST(BST * t);

#endif
