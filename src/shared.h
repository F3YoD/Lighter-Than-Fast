#ifndef _SHARED_H
#define _SHARED_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define BACKGROUND_IMAGE "../assets/images/starbg.jpg"
#define SELF_SHIP_IMAGE  "../assets/images/player%d.png"
#define BOSS_SHIP_IMAGE  "../assets/images/boss%d.png"

#define SHIPS_STATS_FILE "../assets/ships/ships_stats.txt"

#define SHIPS_SCALE 6

extern SDL_Renderer *renderer;
extern TTF_Font *font;

#endif
