#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ships.h"

void load_ships()
{
    char shipfiles_path[] = "../path/to/files";
    // TODO define the need for a "master" file that redirects to other files
}

ship_t get_ship(FILE *shipfile)
{
    // Parse the ship files
}

ship_t * dummy_ship()
{
    ship_t *dummy = (ship_t *)malloc(sizeof(ship_t));
    dummy->name = "hey";
    dummy->is_shop = false;
    dummy->hp = 1;
    dummy->belongings = (belongings_t *)malloc(sizeof(belongings_t));
    dummy->damage_min = 0;
    dummy->damage_max = 1;
    dummy->dodge_score = 0.1;
    dummy->shield = 1;

    return dummy;
}
