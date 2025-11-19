#include <stdio.h>
#include "bst.h"

int main()
{
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;

    BST t = create_empty_BST();

    add(&n1,&t,&compare_int);
    add(&n2,&t,&compare_int);
    add(&n3,&t,&compare_int);
    add(&n4,&t,&compare_int);
    add(&n5,&t,&compare_int);

    printf("Affichage prefixé : \n");   
    print_prefix(t);
    printf("\n");

    printf("Affichage infixé : \n");    
    print_infix(t);
    printf("\n");

    printf("Affichage postfixé : \n");  
    print_postfix(t);
    printf("\n");

    printf("Affichage largeur : \n");   
    print_bf(t); 
    printf("\n");

    free_BST(&t);

    return 0;
}
