#ifndef _FIFO_H
#define _FIFO_H

typedef struct _cell{
    void * data;
    struct _cell * next;
}Cell;

typedef struct{
    Cell* first;
    Cell* last;
}Fifo;

int is_empty(Fifo);
Cell* create_cell(void *);
void free_cell(Cell*); 
Fifo create_fifo();
Cell* fifo_add(Fifo*, void*);
void* fifo_get(Fifo*);

#endif
