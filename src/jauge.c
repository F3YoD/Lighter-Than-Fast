#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "jauge.h"

void load_barre_vie(barre_vie_t * pB,int pVie, char * pDest, SDL_Renderer * pR){
//
	printf("chargement de la barre de vie\n");
	pB->size_bar = pVie;
	pB->img.img = IMG_Load(pDest);
	pB->img.tex = SDL_CreateTextureFromSurface(pR, (pB->img.img));
	pB->img.pos.x = 0; pB->img.pos.y = 0;
}

void update_barre_vie(barre_vie_t * pB, SDL_Renderer * pR){
	//printf("affichage de la barre de vie\n");
	SDL_QueryTexture(pB->img.tex, NULL, NULL, &(pB->img.pos.w), &(pB->img.pos.h));
	SDL_RenderCopy(pR, pB->img.tex, NULL, &pB->img.pos);
}

void free_barre_vie(barre_vie_t * pB){
	printf("suppression de la barre de vie\n");
	SDL_FreeSurface(pB->img.img);
	SDL_DestroyTexture(pB->img.tex);
}

			//****************************//
			/*	      shield	      */
			//****************************//

void load_bar_shield(bar_shield_t * pS, int pPts, char * pDest, SDL_Renderer * pR){
//
	printf("chargement du bouclier\n");
	pS->taille = pPts;
	pS->img.img = IMG_Load(pDest);
	pS->img.tex = SDL_CreateTextureFromSurface(pR, pS->img.img);
	pS->img.pos.x = 0; pS->img.pos.y = 60;
}

void update_bar_shield(bar_shield_t * pS, SDL_Renderer * pR){
//
	//printf("affichage du bouclier\n");
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w,&pS->img.pos.h);
	SDL_RenderCopy(pR, pS->img.tex, NULL, &pS->img.pos);
}

void free_bar_shield(bar_shield_t * pS){
//
	printf("suppression du bouclier\n");
	SDL_FreeSurface(pS->img.img);
	SDL_DestroyTexture(pS->img.tex);
}




