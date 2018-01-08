#include "list.h"

llist
create_empty_list(void)
{
    llist tmp = (llist)malloc(sizeof(node));
    tmp->value = NULL;
    tmp->next = NULL;
    return tmp;
}

void
push(void *elt, llist *list)
{
    llist l = (llist)malloc(sizeof(node));
    l->value = elt;
    l->next = *list;
    *list = l;
}

bool
is_empty(llist l)
{
    return l->value == NULL && l->next == NULL;
}

void
free_list(llist l)
{
    llist tmp1 = l;
    llist tmp2 = NULL;
    while (!is_empty(tmp1))
    {
        tmp2 = tmp1->next;
        free(tmp1->value);
        free(tmp1);
        tmp1 = tmp2;
    }
}

void
*pop_nth(llist l, unsigned short n)
{
    void *res = NULL;
    llist tmp1 = l;
    llist tmp2 = NULL;

    while (n-- > 1 && !is_empty(tmp1))
        tmp1 = tmp1->next;

    res = tmp1->value;
    tmp2 = tmp1->next;
    tmp1->value = tmp2->value;
    tmp1->next = tmp2->next;
    free(tmp2);

    return res;
}
