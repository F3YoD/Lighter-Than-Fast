#ifndef _COMBAT_H
#define _COMBAT_H

#include <stdio.h>
#include <stdbool.h>

#include "shared.h"
#include "tools.h"
#include "ships.h"

enum combat_choice { COMBAT_ATTACK, COMBAT_FLEE, NB_CHOICES_COMBAT };

void display_combat_dialog(enum combat_choice *);

void shoot(ship_t *, ship_t *, unsigned short);
void exchange(ship_t *, ship_t *, struct belongings);
void loot(ship_t *, ship_t *);

#endif /* _COMBAT_H */
