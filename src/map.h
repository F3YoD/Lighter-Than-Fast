#ifndef _LIGHTER_MAP_
#define _LIGHTER_MAP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ships.h"

/***
 * TYPES
 */

typedef struct node
{
    // Either a ship or a shop in a node
    ship_t * target;
    // One node can lead to other nodes, represented as an array
    struct node * next;
}
map_node_t;

// One column of the map can be one or several nodes, stored as an array
typedef struct
{
    int nb_nodes;
    map_node_t * nodes; // Array of nodes
}
map_col_t;

// The full map is several map columns
typedef struct
{
    int nb_col;
    map_col_t * columns; // Array of columns
}
map_t;


/***
 * FUNCTIONS
 */

// Highest level function
// Create map
map_t * build_map(const int);

// Lower level procedures
// Populate a column of map nodes
void populate_map_col(map_col_t *, const int);
// Populate a single node
void populate_map_node(map_node_t *);

#endif
