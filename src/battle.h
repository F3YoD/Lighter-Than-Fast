#ifndef _BATTLE_
#define _BATTLE_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ships.h"

// one vessel can shoot at another
void shoot(ship_t *, ship_t *, const int);

#endif
