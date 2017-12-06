#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//#include "image.h"
#include "fond.h"


void load_fond(fond_t * pF){
//
	printf("chargement du fond\n");
	pF->fond.tex = IMG_LoadTexture(renderer, 
	"../assets/images/Interface/Fond.jpg");

	pF->fond_top.tex = IMG_LoadTexture(renderer,
	"../assets/images/Interface/Top.png");

	pF->fond_right.tex = IMG_LoadTexture(renderer,
	"../assets/images/Interface/Right.png");
	
	pF->fond.pos.x = 0; pF->fond.pos.y = 0;
	pF->fond_top.pos.x = 0; pF->fond_top.pos.y = -215;  
	pF->fond_right.pos.x = 1024; pF->fond_right.pos.y = 48;  
}

void update_fond(fond_t * pF){
//
	printf("affichage du fond\n");
	SDL_QueryTexture(pF->fond.tex,NULL,NULL,&pF->fond.pos.w, 
			&pF->fond.pos.h);
	SDL_RenderCopy(renderer, pF->fond.tex, NULL, &pF->fond.pos);
	
	SDL_QueryTexture(pF->fond_top.tex, NULL, NULL, &pF->fond_top.pos.w, 
			&pF->fond_top.pos.h);
	SDL_RenderCopy(renderer, pF->fond_top.tex, NULL, &pF->fond_top.pos);
	
	SDL_QueryTexture(pF->fond_right.tex, NULL, NULL, &pF->fond_right.pos.w,
			&pF->fond_right.pos.h);
	SDL_RenderCopy(renderer, pF->fond_right.tex, NULL, &pF->fond_right.pos);

	if (pF->fond_top.pos.y < 0)
		pF->fond_top.pos.y++;
	if (pF->fond_right.pos.x > 1024 - 366)
		pF->fond_right.pos.x--;  
}

void free_fond(fond_t * pF){
	printf("suppression du fond\n");
	SDL_DestroyTexture(pF->fond.tex);
	SDL_DestroyTexture(pF->fond_top.tex);
	SDL_DestroyTexture(pF->fond_right.tex);
}
