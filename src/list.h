#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    void *value;
    struct node *next;
} node_t, *list_t;

list_t create_empty_list(void);
void push(void *, list_t *);
void *pop_nth(list_t, unsigned short);
bool is_empty(list_t);
void free_list(list_t);

#endif /* _LIST_H */
