#ifndef _ALIEN_
#define _ALIEN_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "ships.h"

#include "extern.h"

// ======================================= //
//		CONSTANTE ALIENS	   //
// ======================================= //

#define NBRE_ALIENS 4 // pas plus de 5 membres d'équipages

typedef struct {
	int id, pv;
	SDL_Surface * img[4];
	SDL_Texture * tex[4];
	SDL_Rect pos;
}alien_t;

typedef struct {
	alien_t aliens[5]; 
	int taille;
}team_t;

/* ALIEN */
void load_alien(alien_t *, int , SDL_Rect);
void update_alien(alien_t *, SDL_Event, player_ship_t *, int);
void free_alien(alien_t *);
/* TEAM */
void load_team(team_t *);
void update_team(team_t *, SDL_Event, player_ship_t *, int);
void freeTeam(team_t *);

#endif
