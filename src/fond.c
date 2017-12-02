#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "fond.h"


void load_fond(fond_t * pF, char * pDest, SDL_Renderer * pR){
//
	printf("chargement du fond\n");
	pF->tex = IMG_LoadTexture(pR, pDest);
	pF->pos.x = 0; pF->pos.y = 0; 
	pF->pos.w = 1024; pF->pos.h = 768; 
}

void update_fond(fond_t pF, SDL_Renderer * pR){
//
	//printf("affichage du fond\n");
	SDL_QueryTexture(pF.tex,NULL,NULL,&pF.pos.w, &pF.pos.h);
	SDL_RenderCopy(pR, pF.tex, NULL, &pF.pos);
}

void free_fond(fond_t * pF){
	printf("suppression du fond\n");
	SDL_DestroyTexture(pF->tex);
}
