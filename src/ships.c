#include "ships.h"

ship *
load_foe(map_matrix map, unsigned line, unsigned col, unsigned col_height)
{
    static map_matrix prev_map;
    static unsigned prev_line, prev_col;
    static ship *foe;

    if (map != prev_map || col != prev_col || line != prev_line)
    {
        foe = malloc(sizeof(ship));
        *foe = *map[col][line];
    }

    /* TODO reimplement this shit is we want gray dots on map
    for (unsigned i = 0; i < col_height; i++)
        if (i != line)
            free(map[col][i]);

    free(map[col]);
    map[col] = NULL;
    */

    return foe;
}

ship *
load_self(void)
{
    ship *s = (ship *)malloc(sizeof(ship));

    strncpy(s->name, "UNSC Yvan", 50);
    s->is_shop = false;
    s->health = 100;
    s->shield = 50;
    s->belongings.plasma = 100;
    s->belongings.money = 100;
    s->belongings.scraps = 20;
    s->damage_min = 10;
    s->damage_max = 30;
    s->dodge_score = 0.1;
    s->img = load_image(SELF_SHIP_IMAGE, 200);

    return s;
}

ship *
load_boss(void)
{
    ship *s = (ship *)malloc(sizeof(ship));

    strncpy(s->name, "Herr FRAUFRAU", 50);
    s->is_shop = false;
    s->health = 100;
    s->shield = 50;
    s->belongings.plasma = 100;
    s->belongings.money = 100;
    s->belongings.scraps = 20;
    s->damage_min = 10;
    s->damage_max = 30;
    s->dodge_score = 0.1;
    s->img = load_image(BOSS_SHIP_IMAGE, 300);

    return s;
}

llist
gen_ship_list(unsigned *nb_ships)
{
    llist ship_stack = create_empty_list();
    FILE *fp = fopen(SHIPS_STATS_FILE, "r");
    ship *tmp = NULL;
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

ship *
load_ship_from_line(char *line)
{ // Fill ship fields from a formatted string
    ship *s = (ship *)malloc(sizeof(ship));
    char *token = NULL;
    char sep[] = ",\n";
    char *str, *tofree;
    tofree = str = strdup(line);
    // Name
    if ((token = strsep(&str, sep)) != NULL)
        strncpy(s->name, token, 50);
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
        s->img = load_image(token, 200);

    free(tofree);
    if (token == NULL)
        free(s);

    return token != NULL ? s : NULL;
}

void
free_ship(ship **s)
{
    free_image(&(*s)->img);
    free(*s);
    *s = NULL;
}
