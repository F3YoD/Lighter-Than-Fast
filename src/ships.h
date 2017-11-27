#ifndef _SHIPS_
#define _SHIPS_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "image.h"

/***
 * TYPES
 */

struct belongings
{
    // Each ship has some amount of belongings, and some of it can be looted
    // The most important belonging is plasma, it can be used to move the ship and to shoot
    int plasma;
    // People onboard have intergalactic money that can be traded for services or other kind of belongings
    int money;
    // Some vessels have spare scraps to repair itself, but it's hard to store because it's quite large
    // Some parts of a destructed ship can sometimes become scraps
    int scraps;
};

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
    struct belongings belongings;
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
    image_t img;
    //Image of the ship
}
ship_t;

/***
 * FUNCTIONS
 */

void load_ship(ship_t *,char *,SDL_Renderer *);
//load a ship from an image
void update_ship(ship_t *,SDL_Renderer *);
//update ship 
void free_ship(ship_t *);
//Free the memory when the ship is useless

// generate dummy ship for testing purpose
ship_t * dummy_ship();

#endif
