#ifndef _SHIP_
#define _SHIP_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tools.h"

struct belongings
{
    // Plasma is an energy, used to move the ship and fire
    // Scraps are used to repair the ship on the go
    int plasma, money, scraps;
};

typedef struct
{
    char name[50];
    int is_shop; // actually a boolean, kept as an integer for fscanf
    int health, shield;
    struct belongings belongings;
    int damage_min, damage_max;
    float dodge_score;
    char img_path[50];
} ship_t, *map_node_t, **map_col_t, ***map_t;

void load_all_ships(ship_t **, int *);

#endif
