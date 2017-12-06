#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "image.h"
#include "ships.h"

void load_player_ship(player_ship_t * pS, char pDest[50], char pNom[20]){
// role : initialise un player_ship_t
	printf("chargement du vaisseau\n");
	pS->img.tex = IMG_LoadTexture(renderer, pDest);
	pS->img.pos.x = 100;
	pS->img.pos.y = 150;
	pS->angle = 180.0; // angle ship's image
	
	// ================== INIT STATS PLAYER ================== //
	pS->ship.hp = 100;
	pS->ship.shield = 50;
	sprintf(pS->ship.name,"Vaisseau de %s",pNom);
	pS->ship.damage_min = 5;
	pS->ship.damage_max = 10;

	pS->ship.belongings = (belongings_t*)malloc(sizeof(belongings_t));
	
	pS->ship.belongings->plasma = 10;
	pS->ship.belongings->money = 10;
	pS->ship.belongings->scraps = 5;
	/***********************************************************/
}

void update_player_ship(player_ship_t * pS){
// role : met a jour, affiche notre ship
	// ======================= DRAW SHIP PLAYER =================== //
	SDL_QueryTexture(pS->img.tex,NULL,NULL,&pS->img.pos.w, &pS->img.pos.h);
	//SDL_RenderCopy(renderer, pS->img.tex, NULL, &pS->img.pos);
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
	SDL_RenderCopyEx(
		renderer, pS->img.tex, NULL, &pS->img.pos,pS->angle, NULL, flip
	);
	
	/****************************************************************/

	// ====================== DRAW LIFE BAR ======================== /
	SDL_SetRenderDrawColor(renderer, 20,200,20, 255);	
	// color green for life bar
	
	SDL_Rect bar_hp; // the rectangle of life bar
	bar_hp.x = pS->img.pos.x + pS->img.pos.w - 50;
	bar_hp.y = pS->img.pos.y + pS->img.pos.h - 100;
	bar_hp.w = pS->ship.hp * 3;
	bar_hp.h = 20;

	SDL_RenderFillRect(renderer, &bar_hp); // drawing life bar
	/****************************************************************/
	// ====================== DRAW SHIELD BAR ======================== /
	SDL_SetRenderDrawColor(renderer, 20,20,200, 255);	
	// color blue
	
	SDL_Rect bar_shield; // the rectangle of life bar
	bar_shield.x = pS->img.pos.x + pS->img.pos.w - 50;
	bar_shield.y = pS->img.pos.y + pS->img.pos.h - 75;
	bar_shield.w = pS->ship.shield * 3;
	bar_shield.h = 20;

	SDL_RenderFillRect(renderer, &bar_shield); // drawing life bar
	/****************************************************************/

	// ====================== UPDATE LIFE PLAYER ================== //
	// juste pour le test de defaite du joueur
	if(pS->ship.hp > 0){ pS->ship.hp--; }

	if(pS->ship.hp <= 0){
		if(pS->img.pos.x > -1000)
			pS->img.pos.x--;
			pS->angle--;
	}
	/****************************************************************/ 
}

void free_player_ship(player_ship_t * pS){
// role : free notre player_ship_t
	printf("suppression du vaisseau\n");
	free(pS->ship.belongings);
	SDL_DestroyTexture(pS->img.tex);
}

//void load_stats(int ship[100]){
//	file=fopen("ships_stats.txt","r")	
//}

