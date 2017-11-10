#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "game.h"
#include "jauge.h"
#include "alien.h"
#include "ship.h"
#include "fond.h"

#include "interface.h"


void load_interface(interface_t * pI, SDL_Renderer * pR){
// role : ce sous programme charge l'interface qui serra présent
//        dans notre jeu et sera donc appelé dans "game.c",
//        il appel tout les sous programme de chargement qui initialise
//        nos barres de vies, de bouclier, le fond du jeu .. etc 
	printf("***** CHARGEMENT INTERFACE *****\n");
	load_fond(&pI->fond, "./assets/images/gameFond1.jpg", pR);
	load_barre_vie(&pI->barreVie, 10, "./assets/images/lifebare2.png", pR);
	load_bar_shield(&pI->shield, 100, "./assets/images/shieldbare.png", pR);
	load_ship(pI->ship, "./assets/images/ship2.png", pR);
}

void update_interface(interface_t * pI, SDL_Renderer * pR){
// role : ce sous programme gere l'interface en appelant les sous de 
//	  chacun de "objets" du jeu
	update_fond(pI->fond, pR);
	update_barre_vie(&pI->barreVie, pR);
	update_bar_shield(&pI->shield, pR);
	update_ship(pI->ship, pR);
}

void free_interface(interface_t * pI){
// role : gere les free de les élément utilisant de la mémoire, comme la
//	  bibliothèque SDL, les mallocs 
	printf("***** SUPPRESSION INTERFACE *****\n");
	free_fond(&pI->fond);
	free_barre_vie(&pI->barreVie);
	free_bar_shield(&pI->shield);
	free_ship(pI->ship);
}

