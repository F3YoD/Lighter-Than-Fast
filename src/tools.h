#ifndef _TOOLS_
#define _TOOLS_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "shared.h"
#include "macros.h"

#ifdef DEBUG
#define PRINT_DEBUG 1
#else
#define PRINT_DEBUG 0
#endif

#define var_name(variable) #variable

typedef struct node
{
    void *value;
    struct node *next;
} node_t, *list_t;

int gen_rand(unsigned int, unsigned int);

SDL_Texture *create_txt(TTF_Font *, char *, SDL_Color);
SDL_Texture *load_img(char *);
SDL_Rect rect_from_texture(SDL_Texture *, unsigned int, unsigned int);

list_t cons_empty(void);
list_t cons(void *, list_t);
void *head(list_t);
list_t son(list_t);
void print_list(list_t);
void *pop_nth(list_t, unsigned int);
bool is_empty(list_t);
void free_list(list_t);

#endif
