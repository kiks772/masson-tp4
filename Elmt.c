#include "Elmt.h"

int compare_int(Elmt_t* a, Elmt_t* b)
{
    if(*a < *b)
        return -1;
    if(*a > *b)
        return 1;
    return 0;
}
