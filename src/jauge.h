#ifndef _JAUGE_
#define _JAUGE_
	
#include <SDL2/SDL.h>
#include "image.h"
	
typedef struct {
	int size_bar; // taille de la barre de vie affiché
	image_t img;
}barre_vie_t;

typedef struct {
	int taille;
	image_t img;	
}bar_shield_t;

void load_barre_vie(barre_vie_t *,int , char *, SDL_Renderer *);
void update_barre_vie(barre_vie_t *, SDL_Renderer *);
void free_barre_vie(barre_vie_t *);

			//****************************//
			/*	      shield	      */
			//****************************//

void load_bar_shield(bar_shield_t *, int, char *, SDL_Renderer *);
void update_bar_shield(bar_shield_t *, SDL_Renderer *);
void free_bar_shield(bar_shield_t *);

#endif 
