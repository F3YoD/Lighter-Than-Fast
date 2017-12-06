#ifndef _TOOLS_
#define _TOOLS_	
#include "ships.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
int CreeAlea(int,int);
SDL_Texture* SurfaceToTexture( SDL_Surface*);
void afficher_texte(char*,TTF_Font*,SDL_Color,SDL_Rect);
void afficher_stat_ship(player_ship_t*);

#endif
