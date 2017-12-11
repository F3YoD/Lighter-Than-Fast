#ifndef _SHARED_H
#define _SHARED_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

extern SDL_Renderer *renderer;
extern TTF_Font *font;
extern TTF_Font *big_symbol_font;

#endif
