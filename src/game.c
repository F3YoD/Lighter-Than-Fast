#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "game.h"
#include "alien.h"
#include "option.h"

#include "ships.h"
#include "fond.h"
#include "jauge.h"
#include "tools.h"

void game(SDL_Surface * pEcran, char pNom[20]){
// role : gere la partie jouable du jeu
//
// nb : la partie interface sera supprimé car jugé comme obsolète 
	int continuer = 1;
	SDL_Event ev;
	bool clique = false;	
		
	// ========================= LOADING ======================== //
	fenetre_option_t fenetre_option;
	fond_t fond;
	barre_vie_t life;
	bar_shield_t shield;
	player_ship_t * my_ship = (player_ship_t *)malloc(sizeof(player_ship_t));
	
	load_fenetre_option(&fenetre_option);
	load_fond(&fond);
	load_barre_vie(&life, 10, "../assets/images/lifebare2.png");
	load_bar_shield(&shield, 100, "../assets/images/shieldbare.png");
	load_player_ship(my_ship, "../assets/images/ship2.png", pNom);
	
	team_t * team = (team_t *)malloc(sizeof(team_t));
	load_team(team);
	/**************************************************************/	

	// =========================== TTF =========================== //
	
	TTF_Init();
	printf("init ttf\n");	
	
	/***************************************************************/

	// ====================  GESTION DU TEMPS ==================== //
	int temps_precedent = 0, temps_actuel = 0;
	/***************************************************************/ 

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
					case SDLK_TAB:
						clique = true;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(ev.key.keysym.sym){
					case SDLK_TAB:
						if(clique){
							clique = false;
							if(fenetre_option.actif)
								fenetre_option.actif = false;
							else
								fenetre_option.actif = true;
						}
						break;
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
		}
		// ======================= GESTION DU TEMPS ==================== //
		temps_actuel = SDL_GetTicks();
		if (temps_actuel - temps_precedent > 2){	
			// ==================== UPDATE ================== //
			update_fond(&fond);
			//update_barre_vie(&life);
			//update_bar_shield(&shield);
			update_player_ship(my_ship);
			update_team(team, ev, my_ship, control);
		
			//affichage du texte 
			//AfficherTexte("Bienvenue",police,couleur,posTexte);
			//SDL_RenderCopy( renderer, texturetexte, NULL, &posTexte);
			afficher_stat_ship(my_ship);
			update_fenetre_option(&fenetre_option);
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
			/**************************************************/
			
			temps_precedent = temps_actuel;
		}
		/******************************************************************/
	}
	
	///libération	
	TTF_Quit();
	//SDL_DestroyTexture(texturetexte);
	//printf("libération du ttf \n");
	freeTeam(team);
	
	free_fond(&fond);
	free_barre_vie(&life);
	free_bar_shield(&shield);
	free_player_ship(my_ship);
	free_fenetre_option(&fenetre_option);

	free(team);

} 
