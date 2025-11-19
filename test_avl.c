#include <stdio.h>
#include "avl.h"

int main()
{
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;
    int n6 = 6;
    int n7 = 7;
    int n8 = 8;
    int n9 = 9;
    int n10 = 10;

    AVL t = create_empty_AVL();

    add_avl(&n5,&t,&compare_int);
    add_avl(&n3,&t,&compare_int);
    add_avl(&n7,&t,&compare_int);
    add_avl(&n2,&t,&compare_int);
    add_avl(&n4,&t,&compare_int);
    add_avl(&n6,&t,&compare_int);
    add_avl(&n8,&t,&compare_int);
    add_avl(&n1,&t,&compare_int);
    add_avl(&n9,&t,&compare_int);
    add_avl(&n10,&t,&compare_int);

    printf("Affichage prefixé : \n");   
    print_prefix_avl(t);
    printf("\n");

    printf("Affichage infixé : \n");    
    print_infix_avl(t);
    printf("\n");

    printf("Affichage postfixé : \n");  
    print_postfix_avl(t);
    printf("\n");

    printf("Affichage largeur : \n");   
    print_bf_avl(t); 
    printf("\n");

    free_AVL(&t);

    return 0;
}
