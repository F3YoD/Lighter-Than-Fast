#ifndef _SHIP_H
#define _SHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared.h"
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
} ship, *map_node, **map_col, ***map_matrix;

ship *load_foe(map_matrix, unsigned, unsigned, unsigned);
ship *load_self(void);
ship *load_boss(void);
llist gen_ship_list(unsigned *);
ship *load_ship_from_line(char *);
void free_ship(ship **);

#endif
