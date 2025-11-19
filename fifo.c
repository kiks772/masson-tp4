#include <stdlib.h>
#include "fifo.h"

int is_empty(Fifo f)
{
    return f.first == NULL;
}

Cell* create_cell(void * data)
{
    Cell* c = (Cell*)malloc(sizeof(Cell));
    if(c == NULL)
        return NULL;
    c->data = data;
    c->next = NULL;
    return c;
}

void free_cell(Cell* c)
{
    free(c);
}

Fifo create_fifo()
{
    Fifo f;
    f.first = NULL;
    f.last = NULL;
    return f;
}

Cell* fifo_add(Fifo* f, void* data)
{
    Cell* c = create_cell(data);
    if(c == NULL)
        return NULL;
    
    if(f->first == NULL)
    {
        f->first = c;
        f->last = c;
    }
    else
    {
        f->last->next = c;
        f->last = c;
    }
    
    return c;
}

void* fifo_get(Fifo* f)
{
    if(f->first == NULL)
        return NULL;
    
    Cell* c = f->first;
    void* data = c->data;
    f->first = c->next;
    
    if(f->first == NULL)
        f->last = NULL;
    
    free_cell(c);
    return data;
}
