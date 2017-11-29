#ifndef _TOOLS_
#define _TOOLS_

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct node
{
    void *value;
    struct node *next;
} node_t, *list_t;

int gen_rand(int, int);

list_t cons_empty(void);
list_t cons(void *, list_t);
void *pop_nth(list_t, int);
bool is_empty(list_t);
void free_list(list_t);

#endif
