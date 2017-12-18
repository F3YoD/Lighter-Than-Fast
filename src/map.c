#include "map.h"

void gen_map(map_t map, unsigned short height_index[], int length, int max_height)
{
    int height;
    unsigned int nb_ships;
    list_t ship_stack = gen_ship_list(&nb_ships);

    for (int i = 0; i < length; i++)
    {
        // Only one entry node and one exit node
        height = (i > 0 && i < length - 1) ? gen_rand(2, max_height) : 1;
        height_index[i] = height;

        map_col_t column = (map_col_t)malloc(height * sizeof(map_node_t));

        int n = 1;
        for (int j = 0; j < height; j++)
        {
            n = gen_rand(1, nb_ships);
            nb_ships -= 1;
            if (i != length - 1)
                column[j] = (ship_t *)pop_nth(ship_stack, n);
            else
                column[j] = load_boss();
        }

        map[i] = column;
    }

    free_list(ship_stack);
}

void free_map(map_t map, unsigned short index_height[], int length)
{
#ifdef DEBUG
    int k = 0;
#endif
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < index_height[i]; j++)
        {
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
