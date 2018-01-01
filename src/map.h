#ifndef _MAP_H
#define _MAP_H

#include "tools.h"
#include "ships.h"

map_t gen_map(unsigned short[], int, int);
void free_map(map_t, unsigned short[], int);

#endif /* _MAP_H */
