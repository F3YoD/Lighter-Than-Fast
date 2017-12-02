#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "game.h"
#include "alien.h"
#include "interface.h"

// ============================================================= //
//			TEST STRUCT ET SS-PROG			 //
// ============================================================= //
			
			//****************************//
			/*	      shield	      */
			//****************************//


///////////////////////////////////////////////////////////////////

void game(SDL_Renderer * pRend, SDL_Surface * pEcran){ // mettre l'ecran en parametre
// role : gere la partie jouable du jeu
//
// nb : la partie interface sera supprimé car jugé comme obsolète 
	int continuer = 1;
	SDL_Event ev;
			/* ecrire test */
	SDL_Surface * texte = NULL;
	TTF_Font * police = NULL;
	SDL_Color couleurRouge = { 255, 0, 255, 0 };
	SDL_Rect posTexte;
	
	interface_t * inter = (interface_t *)malloc(sizeof(interface_t));
	inter->ship = (player_ship_t *)malloc(sizeof(player_ship_t));
	load_interface(inter, pRend);
	team_t * team = (team_t *)malloc(sizeof(team_t));
	load_team(team, pRend);

	
	///init TTF
	TTF_Init();
	printf("init ttf\n");
	posTexte.x = 0; posTexte.y = 0;		
	/* police = TTF_OpenFont("../assets/police/arial.ttf", 21); */
	police = TTF_OpenFont("../assets/fonts/Inter-UI-Regular.ttf", 21);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	texte = TTF_RenderText_Blended(police, "BIENVENUE", couleurRouge);
	SDL_BlitSurface(texte, NULL, pEcran, &posTexte);
	///fin init TTF

	int control = 0;
	while(continuer){
		SDL_PollEvent(&ev);
		switch(ev.type){
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_SPACE:
						if(control < team->taille - 1)
							control++;
						else 
							control = 0;
						break;
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
		}
		
		update_interface(inter, pRend);
		update_team(team, pRend, ev, inter->ship, control);
		//SDL_BlitSurface(texte, NULL, pEcran, &posTexte);
		SDL_RenderPresent(pRend);
		SDL_RenderClear(pRend);
	
	}
	
	///libération	
	
	TTF_CloseFont(police);	
	SDL_FreeSurface(texte);
	TTF_Quit();

	freeTeam(team);
	free_interface(inter);
	free(inter->ship);
	free(inter);
	free(team);

} 
