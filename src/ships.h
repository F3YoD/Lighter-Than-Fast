#ifndef _SHIPS_
#define _SHIPS_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/***
 * TYPES
 */

typedef struct {
  // each ship has some amount of belongings, and some of it can be looted
  // the most important belonging is plasma, it can be used to move the ship and to shoot
  int plasma;
  // people onboard have intergalactic money that can be traded for services or other kind of belongings
  int money;
  // some vessels have spare scraps to repair itself, but it's hard to store because it's quite large
  // some parts of a destructed ship can sometimes become scraps
  int scraps;
} belongings_t;

typedef struct {
  // a ship is identified by a name
  // maybe some part of it should be randomly generated?
  char * name;
  // a ship has health, it is destroyed if this goes to or bellow 0
  int hp;
  // a ship has belongings onboard
  belongings_t belongings;
  // a ship deals damage to others, with some room for randomness
  int damage_min;
  int damage_max;
  // a skilled pilot can dodge attacks
  int dodge_score;
  // shield can reduce damages
  // should it be extra health or constantly reduce damages?
  int shield;
  /* IDEAS */
  // int crew_size;
} ship_t;

/***
 * FUNCTIONS
 */

// load all the ships from dedicated text files
void load_ships();

// load one single ship
ship_t get_ship(FILE *);

#endif
