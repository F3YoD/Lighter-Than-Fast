#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "jauge.h"

void load_barre_vie(barre_vie_t * pB,int pVie, char * pDest){
//
	printf("chargement de la barre de vie\n");
	pB->size_bar = pVie;
	pB->img.tex = IMG_LoadTexture(renderer, pDest);
	pB->img.pos.x = 0; pB->img.pos.y = 0;
}

void update_barre_vie(barre_vie_t * pB){
	//printf("affichage de la barre de vie\n");
	SDL_QueryTexture(pB->img.tex, NULL, NULL, &(pB->img.pos.w), &(pB->img.pos.h));
	SDL_RenderCopy(renderer, pB->img.tex, NULL, &pB->img.pos);
}

void free_barre_vie(barre_vie_t * pB){
	printf("suppression de la barre de vie\n");
	SDL_DestroyTexture(pB->img.tex);
}

			//****************************//
			/*	      shield	      */
			//****************************//

void load_bar_shield(bar_shield_t * pS, int pPts, char * pDest){
//
	printf("chargement du bouclier\n");
	pS->taille = pPts;
	pS->img.tex = IMG_LoadTexture(renderer, pDest);
	pS->img.pos.x = 0; pS->img.pos.y = 60;
}

void update_bar_shield(bar_shield_t * pS){
//
	//printf("affichage du bouclier\n");
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w,&pS->img.pos.h);
	SDL_RenderCopy(renderer, pS->img.tex, NULL, &pS->img.pos);
}

void free_bar_shield(bar_shield_t * pS){
//
	printf("suppression du bouclier\n");
	SDL_DestroyTexture(pS->img.tex);
}




