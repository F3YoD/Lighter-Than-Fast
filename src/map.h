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

typedef struct node {
  // either a ship or a shop in a node
  void * target;
  // one node can lead to other nodes, represented as an array
  struct node * next;
} map_node_t;

// one column of the map can be one or several nodes, stored as an array
typedef map_node_t * map_col_t;

// the full map is several map columns
typedef map_col_t * map_t;

/***
 * FUNCTIONS
 */

// create map
map_t build_map();

#endif
