#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "extern.h"
#include "tools.h"

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

