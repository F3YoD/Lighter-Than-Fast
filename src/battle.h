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

/// ========== ///
#define NE_FAIT_RIEN 0
#define CHOI_ATTAQUE 1
#define CHOI_DEFENSE 2
#define CHOI_FUITE 3

// one vessel can shoot at another
void shoot(ship_t *, ship_t *, const int);

// One vessel can give ressources to another
int exchange(ship_t *, ship_t *, belongings_t *, belongings_t *);

// The player loots his foe when he kills it
void loot(ship_t *, ship_t *);

//show the combat menu
void init_menu_combat();


// =========================== //
void combat(player_ship_t*, ship_t*, int*, SDL_Event, bool*, int*, SDL_Rect*);

#endif
