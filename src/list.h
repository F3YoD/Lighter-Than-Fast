#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    void *value;
    struct node *next;
} node, *llist;

llist create_empty_list(void);
void push(void *, llist *);
void *pop_nth(llist, unsigned short);
bool is_empty(llist);
void free_list(llist);

#endif /* _LIST_H */
