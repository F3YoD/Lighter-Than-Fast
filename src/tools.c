#include "tools.h"

int gen_rand(int min, int max)
{
    if (min == max)
        return min;
    return rand() % (max - min + 1) + min;
}

list_t cons_empty(void)
{
    return NULL;
}

list_t cons(void *elt, list_t next)
{
    list_t l = (list_t)malloc(sizeof(node_t));
    l->value = elt;
    l->next = next;

    return l;
}

void *pop_nth(list_t l, int n)
{
    if (is_empty(l) || is_empty(l->next))
        return NULL;
    else if (n == 1)
    {
        list_t tmp = l;
        void *res = l->value;
        l = l->next;
        free(tmp);
        return res;
    }
    else if (n == 2)
    {
        list_t tmp = l->next;
        void *res = tmp->value;
        l->next = tmp->next;
        free(tmp);
        return res;
    }
    return pop_nth(l->next, n - 1);
}

bool is_empty(list_t l)
{
    return l == NULL;
}

void free_list(list_t l)
{
    if (!is_empty(l->next))
        free_list(l->next);
    free(l);
}
