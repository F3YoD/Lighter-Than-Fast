#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"

#include "ships.h"

map_t *build_map(const int map_width)
{
    map_t *map = (map_t *)malloc(sizeof(map_t));

    map->nb_col = map_width;
    map->columns = (map_col_t *)malloc(map_width * sizeof(map_col_t));

    // Create 1st (entry) node
    populate_map_col(&map->columns[0], 1);
    // Create middle columns
    for (int i = 1; i < map_width - 1; i++) {
        // Generate random number for nodes in columns
        int nb_nodes = 2; // TODO
        // Generate column
        populate_map_col(&map->columns[i], nb_nodes);
    }
    // Create end column
    populate_map_col(&map->columns[map_width - 1], 1);

    return map;
}

void populate_map_col(map_col_t *column, const int nb_nodes)
{
    // Allocate memory for nodes in column
    column->nodes = (map_node_t *)malloc(nb_nodes * sizeof(map_node_t));

    // Populate column
    for (int i = 0; i < nb_nodes; i++)
        populate_map_node(&column->nodes[i]);
}

void populate_map_node(map_node_t *node)
{
    node->target = (ship_t *)malloc(sizeof(ship_t));

    // Assign ship to node
    // node->target = &one_ship;

    // Do not link the node's ship to another node yet, will be done in build_map
}
