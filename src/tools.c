#include "tools.h"

int gen_rand(unsigned int min, unsigned int max)
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

SDL_Texture *load_img(char *path)
{
    SDL_Texture *t;
    t = IMG_LoadTexture(renderer, path);
    check_IMG(t);

    return t;
}

SDL_Texture *create_txt(TTF_Font *font, char *str, SDL_Color color)
{
    SDL_Texture *t;
    SDL_Surface *tmp;
    tmp = TTF_RenderText_Blended(font, str, color);
    if (!tmp)
    {
        fprintf(stderr, "could not write \"%s\": %s\n", str, TTF_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit(); /* This frees memory for everything SDL-related */
        exit(EXIT_FAILURE);
    }
    else if (PRINT_DEBUG)
        printf("\"%s\" loaded as surface -> ", str);
    t = SDL_CreateTextureFromSurface(renderer, tmp);
    check_SDL(t);
    SDL_FreeSurface(tmp);

    return t;
}

SDL_Rect rect_from_texture(SDL_Texture *t, unsigned int x, unsigned int y)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);

    return r;
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

void *pop_nth(list_t l, unsigned int n)
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
