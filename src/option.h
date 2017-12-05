#ifndef _OPTION_
#define _OPTION_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "image.h"
#include "extern.h"

typedef struct {
	bool actif;
	image_t img_fenetre;
	//image_t img_curseur;
}fenetre_option_t;

void load_fenetre_option(fenetre_option_t*);
void update_fenetre_option(fenetre_option_t*);
void free_fenetre_option(fenetre_option_t*);


#endif
