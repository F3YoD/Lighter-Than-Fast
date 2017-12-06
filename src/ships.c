#include "ships.h"

#define SHIPS_STATS_FILE "../assets/ships/ships_stats.txt"

list_t gen_ship_list(int *nb_ships)
{
    #ifdef DEBUG
    printf("** Loading ships from %s\n", SHIPS_STATS_FILE);
    #endif
    FILE *fp = fopen(SHIPS_STATS_FILE, "r");
    ship_t *tmp = NULL;

    *nb_ships = 0;
    list_t ship_stack = cons_empty();

    char *line = (char *)malloc(100 * sizeof(char));

    while (fgets(line, 100, fp) != NULL)
    {
        /* puts("*** Read new line from file"); */
        tmp = load_ship_from_line(line);
        if (tmp == NULL)
            break;
        *nb_ships += 1;
        ship_t *new_ship = tmp;
        ship_stack = cons(new_ship, ship_stack);
        /* printf("Ship %d: ", *nb_ships); */
        /* printf("%s,%d,%d,%d,%d,%d,%d,%d,%f,%d,%s\n\n", tmp->name, tmp->is_shop, tmp->health, tmp->belongings.plasma, tmp->belongings.money, tmp->belongings.scraps, tmp->damage_min, tmp->damage_max, tmp->dodge_score, tmp->shield, tmp->img_path); */
    }

    fclose(fp);
    free(line);
    if (tmp != NULL)
        free(tmp);

    return ship_stack;
}

ship_t *load_ship_from_line(char *line)
{
    ship_t *tmp = (ship_t *)malloc(sizeof(ship_t));
    char *token = NULL;
    char sep[] = ",\n\r";
    // Name
    token = strtok(line, sep);
    if (token == NULL)
        goto Failure;
    sprintf(tmp->name, "%s", token); // TODO use function allowing to control nb of copied characters and avoid overflows
    // Shop
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->is_shop = atoi(token);
    // HP
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->health = atoi(token);
    // Plasma
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->belongings.plasma = atoi(token);
    // Money
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->belongings.money = atoi(token);
    // Scraps
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->belongings.scraps = atoi(token);
    // Damage min
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->damage_min = atoi(token);
    // Damage max
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->damage_max = atoi(token);
    // Dodge score
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->dodge_score = atof(token);
    // Shield
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    tmp->shield = atoi(token);
    // Image path
    token = strtok(NULL, sep);
    if (token == NULL)
        goto Failure;
    sprintf(tmp->img_path, "%s", token);

    return tmp;

Failure:
    /* puts("Stopped looking for ships"); */
    free(tmp);
    return NULL;
}
