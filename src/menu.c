#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "menu.h"
#include "image.h"

void menu(int * pState){
	///variables
	int choix_joueur = 0;
	int continuer = 1;
	SDL_Event ev;
	SDL_Texture * texture;
	SDL_Rect posFond;
	SDL_Rect posMouse;
	//bool droite = true;
	//bool bas = true;
	///fin variables

	///affichage menu
	texture = IMG_LoadTexture(renderer, "../assets/images/menu2.png");
	posFond.x = 0; posFond.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &posFond.w, &posFond.h);
	SDL_RenderCopy(renderer, texture, NULL, &posFond);
	///fin affichage menu

	while(continuer){
		SDL_PollEvent(&ev);
		switch(ev.type){
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym){
					case SDLK_SPACE :
						choix_joueur = 1;
						continuer = 0;
						break;
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				posMouse.x = ev.button.x;
				posMouse.y = ev.button.y;

				if(posMouse.x > 0 && posMouse.x < 200){
					if(posMouse.y > 0 && posMouse.y < 400){
						continuer = 0;
						choix_joueur = 1;
					}
				}
				break;
		}

		SDL_RenderCopy(renderer, texture, NULL, &posFond);
		SDL_RenderPresent(renderer);
	}
	*pState = choix_joueur;

	///On efface notre menu
	SDL_RenderClear(renderer);

	///libération texture
	printf("libération du menu\n");
	SDL_DestroyTexture(texture);
}
