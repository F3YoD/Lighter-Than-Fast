#ifndef _FOND_
#define _FOND_

#include <SDL2/SDL.h>
#include "extern.h"

typedef struct {
	SDL_Surface * img;
	SDL_Texture * tex;
	SDL_Rect pos;
}fond_t;


void load_fond(fond_t *, char * pDest);
void update_fond(fond_t);
void free_fond(fond_t *);


#endif
