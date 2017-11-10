#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "image.h"
#include "ships.h"



void load_ship(ship_t * pS, char * pDest, SDL_Renderer * pR){
//
	printf("chargement du vaisseau\n");
	pS->img.img = IMG_Load(pDest);
	pS->img.tex = SDL_CreateTextureFromSurface(pR, pS->img.img);
	pS->img.pos.x = 50; pS->img.pos.y = 215; 
	pS->img.pos.w = 500; pS->img.pos.h = 400; 
}

void update_ship(ship_t * pS, SDL_Renderer * pR){
//
	//printf("affichage du vaisseau\n");
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w, &pS->img.pos.h);
	SDL_RenderCopy(pR, pS->img.tex, NULL, &pS->img.pos);
}

void free_ship(ship_t * pS){
	printf("suppression du vaisseau\n");
	SDL_FreeSurface(pS->img.img);
	SDL_DestroyTexture(pS->img.tex);
}

