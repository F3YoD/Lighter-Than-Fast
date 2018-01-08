#ifndef _COMBAT_H
#define _COMBAT_H

#include <stdio.h>
#include <stdbool.h>

#include "shared.h"
#include "rules.h"
#include "tools.h"
#include "ships.h"

enum combat_choice { COMBAT_ATTACK, COMBAT_REPAIR, COMBAT_FLEE, NB_CHOICES_COMBAT };
enum shop_choice { SHOP_HEALTH, SHOP_SCRAPS, SHOP_LEAVE, NB_CHOICES_SHOP };

void shoot(ship *, ship *, unsigned short);
void repair(ship *, int);
void flee(ship *);
void exchange(ship *, ship *, struct belongings);
void loot(ship *, ship *);
void destroy(ship **);

void be_sad(ship *);
void be_happy(ship *);
void be_angry(ship *);

#endif /* _COMBAT_H */
