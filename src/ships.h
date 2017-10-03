#ifndef _SHIPS_
#define _SHIPS_

#include <stdlib.h>
#include <bool.h>
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
  const char * name;
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


//when a ship si shooting
void shoot(ship_t* s1, ship_t* s2, int shoottype){
  //3 damage type, 1,2,3.
    int damage_min=s1->damage_min;
    int damage_max=s1->damage_min;
  //calibrate damage with the type of shoot
    if (shoottype ==2){
      damge_min++;
      damage_max++;
    }
    else if (shoottype ==3){
      damage_min=damage_min+2;
      damage_max=damage_max+2;
    }
  //damage calcul
    int damage=alea(damage_min,damage_max);
    if(touch_chance>s2.dodge_score){
      if (s2->shield<damage){
        damage=damage-s2->shield;
        s2->shield=0;
        s2->hp=s2->hp-damage;
      }
      else if (s2->shield>damage){
        s2->shield=s2->shield-damage;
      }
      else if (s2->hp<damage){
        destruction(s2);
      }
    } 
#endif
