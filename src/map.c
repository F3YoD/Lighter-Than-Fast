#include "map.h"

map_t _gen_map(int length, int max_height)
{
    #ifdef DEBUG
    printf("Map Generation: length = %d, max_height = %d\n", length, max_height);
    #endif
    map_t map = (map_t)malloc(length * sizeof(map_col_t));
    int height;

    // Get ships (already shuffled in reading function)
    int nb_ships;
    int height_index[length];
    list_t ship_stack = gen_ship_list(&nb_ships);

    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        if (i == 0 || i == length - 1)
            height = 1;
        else
            height = gen_rand(2, max_height);

        height_index[i] = height;

        map_col_t column = (map_col_t)malloc((height + 1) * sizeof(map_node_t));

        int n = 1;
        for (int j = 0; j < height; j++)
        {
            n = gen_rand(1, nb_ships);
            /* printf("Taking ship %d/%d\n", n, nb_ships); */
            nb_ships -= 1;
            column[j] = (ship_t *)pop_nth(ship_stack, n);
            print_list(ship_stack);
            /* printf("[%s]\n", column[j]->name); */
        }

        // NULL indicates that no more ships are in the array
        // with height_index this might be obsolete
        column[height] = NULL;

        map[i] = column;
    }

    free_list(ship_stack);

    return map;
}

void gen_map(map_t map, int height_index[], int length, int max_height)
{
    #ifdef DEBUG
    printf("Map Generation: length = %d, max_height = %d\n", length, max_height);
    #endif
    int height;
    int nb_ships;
    list_t ship_stack = gen_ship_list(&nb_ships);

    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        if (i == 0 || i == length - 1)
            height = 1;
        else
            height = gen_rand(2, max_height);

        height_index[i] = height;

        map_col_t column = (map_col_t)malloc((height + 1) * sizeof(map_node_t));

        int n = 1;
        for (int j = 0; j < height; j++)
        {
            n = gen_rand(1, nb_ships);
            /* printf("Taking ship %d/%d\n", n, nb_ships); */
            nb_ships -= 1;
            column[j] = (ship_t *)pop_nth(ship_stack, n);
            print_list(ship_stack);
            /* printf("[%s]\n", column[j]->name); */
        }

        // NULL indicates that no more ships are in the array
        // with height_index this might be obsolete
        column[height] = NULL;

        map[i] = column;
    }

    free_list(ship_stack);
}
