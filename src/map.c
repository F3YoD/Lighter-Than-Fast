#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"

#include "ships.h"

map_t build_map()
{
    // Should we differentiate the entry and exit nodes?
    // create entry node

    // create each columns

    // create exit node
}

map_col_t generate_map_col(int nb_nodes)
{
    // Create nb_nodes nodes and make an array out of it
    map_col_t column = (map_col_t)malloc(nb_nodes * sizeof(map_node_t));

    return column;
}

map_node_t * generate_map_node(int type)
{
    /*
     * Nodes can be of different types:
     *  -1 is an entry node
     *   0 is a normal node
     *   1 is an exit node
     */
    // Create a node
    map_node_t *node = (map_node_t *)malloc(sizeof(map_node_t));

    return node;
}
