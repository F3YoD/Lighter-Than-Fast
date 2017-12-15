#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "image.h"
#include "ships.h"

void load_player_ship(player_ship_t * pS, char pNom[20]){
// role : initialise un player_ship_t
	printf("chargement du vaisseau\n");
	pS->current_img = 0;
	pS->tex[0] = IMG_LoadTexture(renderer, 
		"../assets/images/ship_player/ship_player0.png");
	pS->tex[1] = IMG_LoadTexture(renderer, 
		"../assets/images/ship_player/ship_player1.png");
	pS->tex[2] = IMG_LoadTexture(renderer, 
		"../assets/images/ship_player/ship_player2.png");
	pS->tex[3] = IMG_LoadTexture(renderer, 
		"../assets/images/ship_player/ship_player3.png");
	pS->pos.x = POS_PLAYER_SHIP_X; // 100
	pS->pos.y = POS_PLAYER_SHIP_Y; // 200
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
	SDL_RenderSetScale(renderer, SCALE_PLAYER, SCALE_PLAYER);

	SDL_QueryTexture(pS->tex[pS->current_img],NULL,NULL,&pS->pos.w,&pS->pos.h);
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
	SDL_RenderCopyEx(
		renderer, pS->tex[pS->current_img], NULL, 
		&pS->pos,pS->angle, NULL, flip
	);
	SDL_RenderSetScale(renderer, 1, 1);
	
	/****************************************************************/

	// ====================== DRAW LIFE BAR ======================== /
	SDL_SetRenderDrawColor(renderer, 20,200,20, 255);	
	// color green for life bar
	
	SDL_Rect bar_hp; // the rectangle of life bar
	bar_hp.x = pS->pos.x + (pS->pos.w * SCALE_PLAYER) - 50;
	bar_hp.y = pS->pos.y + (pS->pos.h * SCALE_PLAYER) - 100;
	bar_hp.w = pS->ship.hp * 3;
	bar_hp.h = 20;

	SDL_RenderFillRect(renderer, &bar_hp); // drawing life bar
	/****************************************************************/
	// ====================== DRAW SHIELD BAR ======================== /
	SDL_SetRenderDrawColor(renderer, 20,20,200, 255);	
	// color blue
	
	SDL_Rect bar_shield; // the rectangle of life bar
	bar_shield.x = pS->pos.x + (pS->pos.w * SCALE_PLAYER) - 50;
	bar_shield.y = pS->pos.y + (pS->pos.h * SCALE_PLAYER) - 75;
	bar_shield.w = pS->ship.shield * 3;
	bar_shield.h = 20;

	SDL_RenderFillRect(renderer, &bar_shield); // drawing life bar
	/****************************************************************/

	// ====================== UPDATE LIFE PLAYER ================== //
	// juste pour le test de defaite du joueur
	//if(pS->ship.hp > 0){ pS->ship.hp--; }

	if(pS->ship.hp <= 0){
		if(pS->pos.x > -1000)
			pS->pos.x--;
			pS->angle--;
	}
	/****************************************************************/ 
}

void free_player_ship(player_ship_t * pS){
// role : free notre player_ship_t
	printf("suppression du vaisseau\n");
	free(pS->ship.belongings);
	for(int i = 0; i < NB_IMAGE_SHIP_PLAYER; i++)
		SDL_DestroyTexture(pS->tex[i]);
}

//void load_stats(int ship[100]){
//	file=fopen("ships_stats.txt","r")	
//}

void load_ship(ship_t * pS){
// role : initialise un player_ship_t
	printf("chargement du vaisseau ennemi\n");
	
	// ================== INIT STATS PLAYER ================== //
	pS->hp = 100;
	pS->shield = 50;
	sprintf(pS->name,"Vaisseau de ennemi");
	pS->damage_min = 5;
	pS->damage_max = 10;

	pS->belongings = (belongings_t*)malloc(sizeof(belongings_t));
	
	pS->belongings->plasma = 10;
	pS->belongings->money = 10;
	pS->belongings->scraps = 5;
	/***********************************************************/
}

void update_ship(ship_t *pS){

	// ====================== DRAW LIFE BAR ======================== /
	SDL_SetRenderDrawColor(renderer, 200,20,20, 255);	
	// color green for life bar
	
	SDL_Rect bar_hp; // the rectangle of life bar
	bar_hp.x = 550;
	bar_hp.y = 30;
	bar_hp.w = pS->hp * 3;
	bar_hp.h = 20;


	SDL_RenderFillRect(renderer, &bar_hp); // drawing life bar
	/***************************DRAW SHIELD BAR************************/
	SDL_SetRenderDrawColor(renderer,0,0,225,255);
	//color blue

	SDL_Rect shield_bar; //the rectangle of shield bar
	shield_bar.x=550;
	shield_bar.y=50;
	shield_bar.w=pS->shield * 3;
	shield_bar.h=20;

	SDL_RenderFillRect(renderer,&shield_bar); //drawing shield bar 

}
