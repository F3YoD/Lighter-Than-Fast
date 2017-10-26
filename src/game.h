#ifndef _GAME_
#define _GAME_
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "image.h"
#include "barre_vie.h"
#include "ship.h"

typedef struct {
	int nbrePoints;
	image_t img;	
}shield_t;

typedef struct {
	SDL_Surface * img;
	SDL_Texture * tex;
	SDL_Rect pos;
}fond_t;

typedef struct {
	fond_t fond;
	barre_vie_t barreVie;
	shield_t shield;
	ship_t ship;	
}interface_t;

void game(SDL_Renderer *, SDL_Surface*);

#endif
