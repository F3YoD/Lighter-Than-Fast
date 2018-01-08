#ifndef _MAP_H
#define _MAP_H

#include "tools.h"
#include "ships.h"

map_matrix gen_map(unsigned short[], int, int);
void free_map(map_matrix, unsigned short[], int);

#endif /* _MAP_H */
