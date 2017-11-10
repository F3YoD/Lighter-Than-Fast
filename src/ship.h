#ifndef _SHIP_
#define _SHIP_

#include "image.h"

typedef struct {
	image_t img;
}ship_t;

void load_ship(ship_t *, char *, SDL_Renderer *);
void update_ship(ship_t *, SDL_Renderer *);
void free_ship(ship_t *);
#endif
