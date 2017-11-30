#include "ships.h"

#define SHIPS_STATS_FILE "../assets/ships/ships_stats.txt"

void load_all_ships(ship_t **all_ships, int *nb_ships)
{
    FILE *file = fopen(SHIPS_STATS_FILE, "r");
    ship_t *tmp;
    tmp = (ship_t *)malloc(sizeof(ship_t));

    *nb_ships = 0;
    list_t ship_stack = cons_empty();
    while (fscanf(file, "%s,%d,%d,%d,%d,%d,%d,%d,%f,%d,%s",
                  tmp->name, &tmp->is_shop, &tmp->health, &tmp->belongings.plasma,
                  &tmp->belongings.money, &tmp->belongings.scraps,
                  &tmp->damage_min, &tmp->damage_max, &tmp->dodge_score,
                  &tmp->shield, tmp->img_path) == 11)
    {
        *nb_ships += 1;
        // Stack ships in a linked list
        // TODO differentiate *self* from other ships -> maybe don't define it among the others
        ship_t new_ship = *tmp;
        ship_stack = cons(&new_ship, ship_stack);
    }

    // Unstack and shuffle the ships into an array
    all_ships = (ship_t **)malloc(*nb_ships * sizeof(ship_t *));
    for (int i = 0; i < *nb_ships; i++)
        all_ships[i] = pop_nth(ship_stack, gen_rand(1, *nb_ships - i));

    fclose(file);
    free(tmp);
    free(ship_stack);
}
