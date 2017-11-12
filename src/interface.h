#ifndef _INTERFACE_
#define _INTERFACE_

#include "image.h"
#include "jauge.h"
#include "ships.h"
#include "game.h"
#include "fond.h"

typedef struct {
	fond_t fond;
	barre_vie_t barreVie;
	bar_shield_t shield;
	ship_t * ship;	
}interface_t;


void load_interface(interface_t *, SDL_Renderer *);
void update_interface(interface_t *, SDL_Renderer *);
void free_interface(interface_t *);

#endif
