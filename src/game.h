#ifndef _GAME_
#define _GAME_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "image.h"
#include "extern.h"
#include "alien.h"
#include "option.h"
#include "battle.h"
#include "ships.h"
#include "fond.h"
#include "jauge.h"
#include "tools.h"


void game(SDL_Surface *, char*);

#endif
