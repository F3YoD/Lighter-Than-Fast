#include "ships.h"

#define SHIPS_STATS_FILE "../assets/ships/ships_stats.txt"
#define SELF_SHIP_IMAGE "../assets/images/ship_player0.png"
#define BOSS_SHIP_IMAGE ""

#define SHIPS_SCALE 6

ship_t *load_foe(map_t map, unsigned line, unsigned col, unsigned col_height)
{
    ship_t *s = map[col][line];

    for (unsigned i = 0; i < col_height; i++)
        if (i != line)
            free(map[col][i]);

    free(map[col]);

    return s;
}

ship_t *load_self(void)
{
    ship_t *self = (ship_t *)malloc(sizeof(ship_t));

    strcpy(self->name, "UNSC Yvan");
    self->is_shop = false;
    self->health = 100;
    self->shield = 50;
    self->belongings.plasma = 100;
    self->belongings.money = 100;
    self->belongings.scraps = 20;
    self->damage_min = 10;
    self->damage_max = 30;
    self->dodge_score = 0.1;
    strcpy(self->img_path, SELF_SHIP_IMAGE);

    return self;
}

ship_t *load_boss(void)
{ // Create boos ship
    ship_t *boss = (ship_t *)malloc(sizeof(ship_t));

    strcpy(boss->name, "Herr FRAUFRAU");
    boss->is_shop = false;
    boss->health = 100;
    boss->shield = 50;
    boss->belongings.plasma = 100;
    boss->belongings.money = 100;
    boss->belongings.scraps = 20;
    boss->damage_min = 10;
    boss->damage_max = 30;
    boss->dodge_score = 0.1;
    strcpy(boss->img_path, BOSS_SHIP_IMAGE); // TODO

    return boss;
}

list_t gen_ship_list(unsigned *nb_ships)
{ // Create stack of ships to be used in the map
    list_t ship_stack = create_empty_list();
    FILE *fp = fopen(SHIPS_STATS_FILE, "r");
    ship_t *tmp = NULL;
    *nb_ships = 0;

    char *line = (char *)malloc(100 * sizeof(char));

    while (fgets(line, 100, fp) != NULL)
    {
        tmp = load_ship_from_line(line);
        if (!tmp)
            break;
        *nb_ships += 1;
        push(tmp, &ship_stack);
    }

    fclose(fp);
    free(line);

    return ship_stack;
}

ship_t *load_ship_from_line(char *line)
{ // Fill ship_t fields from a formatted string
    ship_t *s = (ship_t *)malloc(sizeof(ship_t));
    char *token = NULL;
    char sep[] = ",\n";
    char *str, *tofree;
    tofree = str = strdup(line);
    // Name
    if ((token = strsep(&str, sep)) != NULL)
        strcpy(s->name, token);
    // Shop
    if ((token = strsep(&str, sep)) != NULL)
        s->is_shop = atoi(token);
    // HP
    if ((token = strsep(&str, sep)) != NULL)
        s->health = atoi(token);
    // Plasma
    if ((token = strsep(&str, sep)) != NULL)
        s->belongings.plasma = atoi(token);
    // Money
    if ((token = strsep(&str, sep)) != NULL)
        s->belongings.money = atoi(token);
    // Scraps
    if ((token = strsep(&str, sep)) != NULL)
        s->belongings.scraps = atoi(token);
    // Damage min
    if ((token = strsep(&str, sep)) != NULL)
        s->damage_min = atoi(token);
    // Damage max
    if ((token = strsep(&str, sep)) != NULL)
        s->damage_max = atoi(token);
    // Dodge score
    if ((token = strsep(&str, sep)) != NULL)
        s->dodge_score = atof(token);
    // Shield
    if ((token = strsep(&str, sep)) != NULL)
        s->shield = atoi(token);
    // Image path
    if ((token = strsep(&str, sep)) != NULL)
        strcpy(s->img_path, token);

    free(tofree);
    if (token == NULL)
        free(s);

    return token != NULL ? s : NULL;
}
