#include "map.h"

/*
map_t gen_map(int length, int max_height)
{
    #ifdef DEBUG
    printf("Map Generation: length = %d, max_height = %d\n", length, max_height);
    #endif
    map_t map = (map_t)malloc(length * sizeof(map_col_t));
    int height;

    // Get ships (already shuffled in reading function)
    int nb_ships;
    ship_t **ship_array = load_all_ships(&nb_ships);

    int k = 0;
    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        if (i == 0 || i == length - 1)
            height = 1;
        else
            height = gen_rand(2, max_height);

        map_col_t column = (map_col_t)malloc((height + 1) * sizeof(map_node_t));

        #ifdef DEBUG
        printf("* Gen. of column %d of %d, with height %d\n", i, length, height);
        #endif

        for (int j = 0; j < height; j++)
        {
            column[j] = ship_array[k++];
            printf("%d ", j);
        }

        // NULL indicates that no more ships are in the array
        column[height] = NULL;
        puts("N ");

        map[i] = column;
    }

    #ifdef DEBUG
    puts("Done generating map");
    #endif

    free(ship_array);

    return map;
}
*/

map_t gen_map2(int length, int max_height)
{
    #ifdef DEBUG
    printf("Map Generation: length = %d, max_height = %d\n", length, max_height);
    #endif
    map_t map = (map_t)malloc(length * sizeof(map_col_t));
    int height;

    // Get ships (already shuffled in reading function)
    int nb_ships;
    list_t ship_stack = gen_ship_list(&nb_ships);

    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        if (i == 0 || i == length - 1)
            height = 1;
        else
            height = gen_rand(2, max_height);

        map_col_t column = (map_col_t)malloc((height + 1) * sizeof(map_node_t));

        #ifdef DEBUG
        printf("* Gen. of column %d of %d, with height %d\n", i, length - 1, height);
        #endif

        int n = 1;
        for (int j = 0; j < height; j++)
        {
            n = gen_rand(1, nb_ships);
            printf("Taking ship %d/%d\n", n, nb_ships);
            nb_ships -= 1;
            column[j] = (ship_t *)pop_nth(ship_stack, n);
            print_list(ship_stack);
            printf("[%s]\n", column[j]->name);
        }

        // NULL indicates that no more ships are in the array
        column[height] = NULL;
        puts("N ");

        map[i] = column;
    }

    #ifdef DEBUG
    puts("Done generating map");
    #endif

    free_list(ship_stack);

    return map;
}
