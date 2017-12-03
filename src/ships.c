#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "image.h"
#include "ships.h"

void load_player_ship(player_ship_t * pS, char pDest[50]){
// role : initialise un player_ship_t
	printf("chargement du vaisseau\n");
	pS->img.tex = IMG_LoadTexture(renderer, pDest);
	pS->img.pos.x = 100;
	pS->img.pos.y = 100;

	// ================== INIT STATS PLAYER ================== //
	pS->ship.hp = 100;
	pS->ship.shield = 50;
	/***********************************************************/
}

void update_player_ship(player_ship_t * pS){
// role : met a jour, affiche notre ship
	// ======================= DRAW SHIP PLAYER =================== //
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w, &pS->img.pos.h);
	SDL_RenderCopy(renderer, pS->img.tex, NULL, &pS->img.pos);
	/****************************************************************/

	// ====================== UPDATE LIFE PLAYER ================== //
	// juste pour le test de defaite du joueur
	if(pS->ship.hp > 0) { pS->ship.hp--; }

	if(pS->ship.hp <= 0){
		if(pS->img.pos.x > -1000)
			pS->img.pos.x--;
	}
	/****************************************************************/ 
}

void free_player_ship(player_ship_t * pS){
// role : free notre player_ship_t
	printf("suppression du vaisseau\n");
	SDL_DestroyTexture(pS->img.tex);
}

//void load_stats(int ship[100]){
//	file=fopen("ships_stats.txt","r")	
//}

