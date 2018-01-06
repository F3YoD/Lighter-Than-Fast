#ifndef _SHIP_H
#define _SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "tools.h"
#include "list.h"
#include "image.h"

struct belongings
{
    // Plasma is an energy, used to move the ship and fire
    // Scraps are used to repair the ship on the go
    union
    {
        struct
        {
            int plasma, money, scraps;
        };
        int all[3];
    };
};

typedef struct
{
    char name[50];
    int is_shop; // actually a boolean, kept as an integer for fscanf
    int health, shield;
    struct belongings belongings;
    int damage_min, damage_max;
    float dodge_score;
    image *img;
} ship_t, *map_node_t, **map_col_t, ***map_t;

ship_t *load_foe(map_t, unsigned, unsigned, unsigned);
ship_t *load_self(void);
ship_t *load_boss(void);
list_t gen_ship_list(unsigned *);
ship_t *load_ship_from_line(char *);
void free_ship(ship_t **);

#endif
