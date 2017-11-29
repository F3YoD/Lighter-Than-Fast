#include "map.h"

map_t gen_map(int length, int max_height)
{
    #ifdef DEBUG
    printf("Map Generation: length = %d, max_height = %d\n", length, max_height);
    #endif
    map_t map = (map_t)malloc(length * sizeof(map_col_t));
    int height;

    // Get ships (already shuffled in reading function)
    ship_t **ship_array = NULL;
    int nb_ships;
    load_all_ships(ship_array, &nb_ships);

    int k = 0;
    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        if (i == 0 || i == length - 1)
            height = 1;
        else
            height = gen_rand(2, max_height);

        map_col_t column = (map_col_t)malloc(height * sizeof(map_node_t));

        for (int j = 0; j < height; j++)
            column[j] = ship_array[k++];

        #ifdef DEBUG
        printf("* Gen. of column %d of %d, with height %d\n", i, length, height);
        #endif

        map[i] = column;

        // TODO hey, won't we delete the column here?
        /* free(column); */
    }

    free(ship_array);

    return map;
}
