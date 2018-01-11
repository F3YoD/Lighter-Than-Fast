#ifndef _TOOLS_H
#define _TOOLS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
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

typedef enum horizontal_alignment { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT } h_align;
typedef enum vertical_alignment { ALIGN_TOP, ALIGN_MIDDLE, ALIGN_BOTTOM } v_align;

int gen_rand(unsigned short int, unsigned short int);

void wait_key_press(void);
SDL_Texture *create_txt(TTF_Font *, char *, SDL_Color);
SDL_Texture *load_img(char *);
SDL_Rect rect_from_texture(SDL_Texture *, unsigned short int, unsigned short int);
SDL_Texture *texture_from_text(TTF_Font *, unsigned short int, SDL_Rect, char *, SDL_Color, h_align);

bool cmpnval(unsigned, unsigned, ...);

#endif /* _TOOLS_H */
