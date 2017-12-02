#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "image.h"
#include "ships.h"

void load_player_ship(player_ship_t * pS, char pDest[50], SDL_Renderer * pRend){
// role : initialise un player_ship_t
	printf("chargement du vaisseau\n");
	pS->img.tex = IMG_LoadTexture(pRend, pDest);
	pS->img.pos.x = 100;
	pS->img.pos.y = 100;
}

void update_player_ship(player_ship_t * pS, SDL_Renderer * pR){
// role : met a jour, affiche notre ship
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w, &pS->img.pos.h);
	SDL_RenderCopy(pR, pS->img.tex, NULL, &pS->img.pos);
}

void free_player_ship(player_ship_t * pS){
// role : free notre player_ship_t
	printf("suppression du vaisseau\n");
	SDL_DestroyTexture(pS->img.tex);
}
