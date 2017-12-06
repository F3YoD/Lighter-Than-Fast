#ifndef _GAME_
#define _GAME_

#include <stdbool.h>
#include <stdio.h>

#include "shared.h"
#include "macros.h"
#include "ships.h"
#include "map.h"
#include "menu.h"

void play_game(void);
void show_fake_loading(unsigned short);

ship_t *gen_self();

#endif
