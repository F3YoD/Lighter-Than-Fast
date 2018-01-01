#ifndef _SHARED_H
#define _SHARED_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"
#define SELF_SHIP_IMAGE  "../assets/images/ship_player0.png"
#define BOSS_SHIP_IMAGE  ""

#define SHIPS_STATS_FILE "../assets/ships/ships_stats.txt"

#define SHIPS_SCALE 6

extern SDL_Renderer *renderer;
extern TTF_Font *font;
extern TTF_Font *big_symbol_font;

#endif
