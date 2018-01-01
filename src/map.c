#include "map.h"

map_t
gen_map(unsigned short height_index[], int length, int max_height)
{
    int height;
    unsigned int nb_ships;
    list_t ship_stack = gen_ship_list(&nb_ships);

    map_t map = (map_t)malloc(length * sizeof(map_col_t));

    for (int i = 0; i < length; i++)
    {
        // Generate a random number of nodes in the column if not first or last
        height = (i > 0 && i < length - 1) ? gen_rand(2, max_height) : 1;
        height_index[i] = height;

        map_col_t column = (map_col_t)malloc(height * sizeof(map_node_t));

        // Populate nodes
        if (i == length - 1)
            column[0] = load_boss();
        else
            for (int j = 0; j < height; j++)
                column[j] = (ship_t *)pop_nth(ship_stack, gen_rand(1, nb_ships--));

        map[i] = column;
    }

    // Free unnecessary ships
    free_list(ship_stack);

    return map;
}

void
free_map(map_t map, unsigned short index_height[], int length)
{
#ifdef DEBUG
    int k = 0;
#endif
    // Free non-empty nodes then columns
    for (int i = 0; i < length; i++)
    {
        if (!map[i])
            continue;

        for (int j = 0; j < index_height[i]; j++)
        {
            if (!map[i][j])
                continue;

            free(map[i][j]);
#ifdef DEBUG
            k++;
#endif
        }
        free(map[i]);
    }
    free(map);
#ifdef DEBUG
    printf("Deleted %d ships\n", k);
#endif
}
