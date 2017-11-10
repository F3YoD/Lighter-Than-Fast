#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "ships.h"
#include "menu.h"
#include "battle.h"

void choices(int choice, ship_t * your_ship, ship_t * ennemy_ship) {
	//This code is here to manage the choises in the menu during a battle, shoot and ship_t are in the file battle.c
	if (choice == 1) {  //shoottype 1
		//TODO Fire animation
		shoot(your_ship, ennemy_ship, choice);
	}
	else if(choice == 2) { //shoottype 2
		//TODO Fire animation
		shoot(your_ship, ennemy_ship, choice);
	}
	else if(choice == 3) { //shoottype 3
		//TODO Fire animation
		shoot(your_ship, ennemy_ship, choice);
	}
	else if(choice == 4) { //Try to escape 
		//TODO, Don't know yet how we manage this case
	}
	else if(choice == 5) { //Try to pay some scraps or plasma to the enemy to escape the fight
		pay(your_ship, ennemy_ship, prix); //don't know now how calculate this price
		//TODO Pay function
	}
}

void menu(int * pState, SDL_Renderer * pRend) {
	///variable
	int choix_joueur = 0;
	int continuer = 1;
	SDL_Event ev;
	SDL_Surface * imgMenu;
	SDL_Surface * imgPl;
	SDL_Texture * texture;
	SDL_Texture * texture2;
	SDL_Rect posFond;
	SDL_Rect posPl;
	SDL_Rect posMouse;
	bool droite = true; 
	bool bas = true;
	///fin variable

	///affichage menu
	imgMenu = SDL_LoadBMP("./assets/images/menu.bmp");
	imgPl = SDL_LoadBMP("./assets/images/planete.bmp");
	texture = SDL_CreateTextureFromSurface(pRend, imgMenu);
	texture2 = SDL_CreateTextureFromSurface(pRend, imgPl);
	posFond.x = 0; posFond.y = 0;
	posPl.x = 0; posPl.y = 300;
	SDL_QueryTexture(texture, NULL, NULL, &posFond.w, &posFond.h);
	SDL_QueryTexture(texture2, NULL, NULL, &posPl.w, &posPl.h);
	SDL_RenderCopy(pRend, texture, NULL, &posFond);
	SDL_RenderCopy(pRend, texture2, NULL, &posPl);
	//SDL_RenderPresent(pRend);
	///fin affichage menu

	while(continuer) {
		SDL_PollEvent(&ev);
		switch(ev.type) {
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym) {
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

				if(posMouse.x > 0 && posMouse.x < 200) {
				      if(posMouse.y > 0 && posMouse.y < 400)
						continuer = 0;
						choix_joueur = 1;
				}
				break;
		}

		if(posPl.x > 600) {
			droite = false;
		}
		if(posPl.x < 0) {
			droite = true;
		}

		if(posPl.y > 600) {
			bas = false;
		}
		if(posPl.y < 0) {
			bas = true;
		}

		if(droite)
			posPl.x++;
		else
			posPl.x--;

		if(bas)
			posPl.y++;
		else
			posPl.y--;

		//SDL_RenderClear(pRend);
		SDL_RenderCopy(pRend, texture, NULL, &posFond);
		SDL_RenderCopy(pRend, texture2, NULL, &posPl);
		SDL_RenderPresent(pRend);
	}
	*pState = choix_joueur;

	///On efface notre menu
	SDL_RenderClear(pRend);

	///libération texture
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture2);
	SDL_FreeSurface(imgMenu);
	SDL_FreeSurface(imgPl);
}
