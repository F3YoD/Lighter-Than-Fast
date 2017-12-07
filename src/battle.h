#ifndef _BATTLE_
#define _BATTLE_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ships.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// one vessel can shoot at another
void shoot(ship_t *, ship_t *, const int);

// One vessel can give ressources to another
int exchange(ship_t *, ship_t *, belongings_t *, belongings_t *);

// The player loots his foe when he kills it
void loot(ship_t *, ship_t *);

//show the combat menu
void init_menu_combat();

#endif
