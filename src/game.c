#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "game.h"
#include "alien.h"

#include "ships.h"
#include "fond.h"
#include "jauge.h"
#include "tools.h"




void game(SDL_Surface * pEcran){
// role : gere la partie jouable du jeu
//
// nb : la partie interface sera supprimé car jugé comme obsolète 
	int continuer = 1;
	SDL_Event ev;
			/* ecrire test */
	SDL_Surface * texte = NULL;
	TTF_Font * police = NULL;
	SDL_Color couleurRouge = { 255, 0, 0};
	SDL_Rect posTexte;
		
	
	// ========================= LOADING ======================== //
	fond_t fond;
	barre_vie_t life;
	bar_shield_t shield;
	player_ship_t * my_ship = (player_ship_t *)malloc(sizeof(player_ship_t));
	
	load_fond(&fond, "../assets/images/gameFond1.jpg");
	load_barre_vie(&life, 10, "../assets/images/lifebare2.png");
	load_bar_shield(&shield, 100, "../assets/images/shieldbare.png");
	load_player_ship(my_ship, "../assets/images/ship2.png");
	
	team_t * team = (team_t *)malloc(sizeof(team_t));
	load_team(team);
	/**************************************************************/	


	// =========================== TTF =========================== //
	
	// nb : for the moment, ttf don't run because we don't know create
	//	a 
	
	TTF_Init();
	printf("init ttf\n");
	posTexte.x = 500; posTexte.y = 500;		
	/* police = TTF_OpenFont("../assets/police/arial.ttf", 21); */
	police = TTF_OpenFont("../assets/fonts/Inter-UI-Regular.ttf", 21);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	texte = TTF_RenderText_Blended(police, "BIENVENUE", couleurRouge);
	SDL_Texture* texturetexte = SurfaceToTexture( texte );
	SDL_QueryTexture( texturetexte, NULL, NULL,&posTexte.w,&posTexte.h );
	
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
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
		}
		
		// ==================== UPDATE ================== //
		update_fond(fond);
		update_barre_vie(&life);
		update_bar_shield(&shield);
		update_player_ship(my_ship);
		update_team(team, ev, my_ship, control);
		
		//affichage du texte 
		SDL_RenderCopy( renderer, texturetexte, NULL, &posTexte);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		/**************************************************/
	
	}
	
	///libération	
	
	TTF_CloseFont(police);	
	SDL_FreeSurface(texte);
	SDL_DestroyTexture(texturetexte);
	TTF_Quit();
	printf("libération du ttf \n");
	freeTeam(team);
	
	free_fond(&fond);
	free_barre_vie(&life);
	free_bar_shield(&shield);
	free_player_ship(my_ship);

	free(team);

} 
