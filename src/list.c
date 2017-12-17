#include "list.h"

list_t create_empty_list(void)
{
    list_t tmp = (list_t)malloc(sizeof(node_t));
    tmp->value = NULL;
    tmp->next = NULL;
    return tmp;
}

void push(void *elt, list_t *list)
{
    list_t l = (list_t)malloc(sizeof(node_t));
    l->value = elt;
    l->next = *list;
    *list = l;
}

bool is_empty(list_t l)
{
    return l->value == NULL && l->next == NULL;
}

void free_list(list_t l)
{
    list_t tmp1 = l;
    list_t tmp2 = NULL;
    while (!is_empty(tmp1))
    {
        tmp2 = tmp1->next;
        free(tmp1->value);
        free(tmp1);
        tmp1 = tmp2;
    }
}

void *pop_nth(list_t l, unsigned short n)
{
    void *res = NULL;
    list_t tmp1 = l;
    list_t tmp2 = NULL;
    while (n-- > 1 && !is_empty(tmp1))
        tmp1 = tmp1->next;
    res = tmp1->value;
    tmp2 = tmp1->next;
    tmp1->value = tmp2->value;
    tmp1->next = tmp2->next;
    free(tmp2);
    return res;
}
