#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "extern.h"
#include "tools.h" 
#include "ships.h"

int CreeAlea(int min, int max){
// ce sous programme retourne un entier aleatoire entre min et max
	return rand()%(max - min+1) + min;
}

SDL_Texture* SurfaceToTexture( SDL_Surface* surfacedutexte )
{
	SDL_Texture* texte;

	texte = SDL_CreateTextureFromSurface( renderer, surfacedutexte );

	SDL_FreeSurface( surfacedutexte );

	return texte;
}

void AfficherTexte(char texte[],TTF_Font* police, SDL_Color couleur,SDL_Rect position){

	SDL_Surface* txt = TTF_RenderText_Blended(police,texte,couleur);
	SDL_Texture* texturetexte = SurfaceToTexture(txt);

	SDL_QueryTexture(texturetexte,NULL,NULL,&position.w,&position.h);
	SDL_RenderCopy(renderer,texturetexte,NULL,&position);

	//libération de la texture pour eviter de faire planter le jeu
	SDL_DestroyTexture(texturetexte);
}

void AfficherStatShip(player_ship_t* ps){
	//Initialisation		
	TTF_Font* police = TTF_OpenFont("../assets/fonts/Inter-UI-Regular.ttf", 12);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	SDL_Color couleur = { 255, 0, 0};
	SDL_Rect position;
	position.x = 15; position.y = 15;
	char ecrire[25];

	//ecriture des stats
	sprintf(ecrire,"Nom du vaisseau : %s",ps->ship.name);
	AfficherTexte(ecrire,police,couleur,position);

	position.y=position.y+15;
	sprintf(ecrire,"Vie: %d",ps->ship.hp);
	AfficherTexte(ecrire,police,couleur,position);

	position.y=position.y+15;
	sprintf(ecrire,"Bouclier: %d",ps->ship.shield);
	AfficherTexte(ecrire,police,couleur,position);
	
	position.y=position.y+15;
	sprintf(ecrire,"Degats minimum : %d",ps->ship.damage_min);
	AfficherTexte(ecrire,police,couleur,position);
	
	position.y=position.y+15;
	sprintf(ecrire,"Degats maximum :%d",ps->ship.damage_max);
	AfficherTexte(ecrire,police,couleur,position);

	/*position.y=position.y+15;
	sprintf(ecrire,"Plasma :%d",ps->ship.belongings->plasma);
	AfficherTexte(ecrire,police,couleur,position);

	position.y=position.y+15;
	sprintf(ecrire,"Money :%d",ps->ship.belongings->money);
	AfficherTexte(ecrire,police,couleur,position);

	position.y=position.y+15;
	sprintf(ecrire,"Scraps :%d",ps->ship.belongings->scraps);
	AfficherTexte(ecrire,police,couleur,position);*/
	
	TTF_CloseFont(police);	
}
