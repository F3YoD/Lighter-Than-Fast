#include "tools.h"
//#include "ships.h" // only for debug

int gen_rand(int min, int max)
{
    if (min == max)
        return min;
    if (min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }
    return rand() % (max - min + 1) + min;
}

list_t cons_empty(void)
{
    list_t tmp = (list_t)malloc(sizeof(node_t));
    tmp->value = NULL;
    tmp->next = NULL;
    return tmp;
}

list_t cons(void *elt, list_t next)
{
    list_t l = (list_t)malloc(sizeof(node_t));
    /* printf("cons: got %s\n", ((ship_t *)elt)->name); */
    l->value = elt;
    l->next = next;

    return l;
}

bool is_empty(list_t l)
{
    return l->value == NULL;
}

void *head(list_t l)
{
    return l->value;
}

list_t child(list_t l)
{
    if (is_empty(l))
        return NULL;
    else
        return l->next;
}

void print_list(list_t l)
{
    list_t tmp = l;
    while (!is_empty(tmp))
    {
        /* ship_t *curr = (ship_t *)tmp->value; */
        /* printf("%s %s\n", curr->name, curr->is_shop ? "(Shop)" : ""); */
        tmp = child(tmp);
    }
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

void *pop_nth(list_t l, int n)
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
