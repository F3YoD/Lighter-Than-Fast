#ifndef _SHIPS_
#define _SHIPS_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "image.h"
#include "extern.h"

#define NB_IMAGE_SHIP_PLAYER 4
#define FRAME_TIME 400 // (400 ms)
#define SCALE_PLAYER 8
#define POS_X 100
#define POS_Y 300
#define POS_PLAYER_SHIP_X POS_X/SCALE_PLAYER
#define POS_PLAYER_SHIP_Y POS_Y/SCALE_PLAYER

/***
 * TYPES
 */

typedef struct belongings
{
    // Each ship has some amount of belongings, and some of it can be looted
    // The most important belonging is plasma, it can be used to move the ship and to shoot
    int plasma;
    // People onboard have intergalactic money that can be traded for services or other kind of belongings
    int money;
    // Some vessels have spare scraps to repair itself, but it's hard to store because it's quite large
    // Some parts of a destructed ship can sometimes become scraps
    int scraps;
}belongings_t;

typedef struct
{
    // A ship is identified by a name
    // Maybe some part of it should be randomly generated?
    char name[50];
    // A shop is just a ship willing to trade stuff
    bool is_shop;
    // A ship has health, it is destroyed if this goes to or bellow 0
    int hp;
    // A ship has belongings onboard
    //int plasma, money, scraps; 
    belongings_t *belongings;
    // A ship deals damage to others, with some room for randomness
    int damage_min;
    int damage_max;
    // A skilled pilot can dodge attacks
    float dodge_score;
    // Shield can reduce damages
    // Should it be extra health or constantly reduce damages?
    int shield;
    /* IDEAS */
    // int crew_size;
    // Enemy and self level, to balance gameplay, e.g. having more enemies of class X if player is class X
    // int level;
    char img_path[50];
    //Image of the ship
}
ship_t, * map_node_t, ** map_col_t, *** map_t;

typedef struct {
	ship_t ship;
	int current_img;
	SDL_Texture *tex[NB_IMAGE_SHIP_PLAYER];
	SDL_Rect pos;
	double angle;   // angle de notre vaisseaux sur l'écran
			// qui sera modifié a la destruction du vaisseau
}player_ship_t;

/***
 * FUNCTIONS
 */

void load_player_ship(player_ship_t *,char *);
//load a ship from an image
void update_player_ship(player_ship_t *);
//update ship 
void free_player_ship(player_ship_t *);
//Free the memory when the ship is useless

// generate dummy ship for testing purpose
ship_t * dummy_ship();

void load_ship(ship_t*);
void update_ship(ship_t*);
#endif
