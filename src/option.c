#include "option.h"

void load_fenetre_option(fenetre_option_t * fO){
// role : charge notre fenetre d'option, c'est a dire, sa position, son image et
//	  l'image de son curseur
	printf("*****chargement de la fenetre d'option*****\n");
	fO->actif = true;
	fO->img_fenetre.tex = IMG_LoadTexture(renderer, 
		"../assets/images/option.png"	
	);
	fO->img_fenetre.pos.x = 100;
	fO->img_fenetre.pos.y = 100;
}

void update_fenetre_option(fenetre_option_t * fO){
// role : met a jour et affiche notre fenetre d'option
	if(fO->actif){
		SDL_QueryTexture(fO->img_fenetre.tex, NULL, NULL,
			&fO->img_fenetre.pos.w, &fO->img_fenetre.pos.h
		);
		SDL_RenderCopy(renderer, fO->img_fenetre.tex, NULL,
			&fO->img_fenetre.pos	
		);
	}
}

void free_fenetre_option(fenetre_option_t * fO){
// role : libère la mémoire
	SDL_DestroyTexture(fO->img_fenetre.tex);
}
