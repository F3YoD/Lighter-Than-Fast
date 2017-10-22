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
    void * target;
    // One node can lead to other nodes, represented as an array
    struct node * next;
}
map_node_t;

// One column of the map can be one or several nodes, stored as an array
typedef map_node_t * map_col_t;

// The full map is several map columns
typedef map_col_t * map_t;

/***
 * FUNCTIONS
 */

// Highest level function
// Create map
map_t build_map();

// Lower level functions
// Generate a column of map nodes
map_col_t generate_map_col(int);
// Generate a single node
map_node_t * generate_map_node(int);

#endif
