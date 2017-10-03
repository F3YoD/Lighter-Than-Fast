#include <stdlib.h>
#include <bool.h>
#include <string.h>
#include <math.h>

#include "battle.h"

void shoot(ship_t* s1, ship_t* s2, const int shoottype)
{
  // we can shoot one, two or three times at once
  // the more we shoot, the more expensive in plasma it is
  int damage_min = s1->damage_min;
  int damage_max = s1->damage_min;

  // increase damage depending on type
  // TODO establish realistic rates
  // maybe:
  // damage_min *= shoottype;
  if (shoottype == 2) {
    damage_min++;
    damage_max++;
  }
  else if (shoottype == 3) {
    damage_min = damage_min+2;
    damage_max = damage_max+2;
  }

  // determine inflicted damage
  int damage = alea(damage_min, damage_max);
  if (touch_chance > s2.dodge_score) {
    if (s2->shield < damage) {
      damage = damage-s2->shield;
      s2->shield = 0;
      s2->hp = s2->hp - damage;
    }
    else if (s2->shield > damage) {
      s2->shield = s2->shield - damage;
    }
    else if (s2->hp < damage) {
      destruction(s2);
    }
    if (s2->hp <= 0){
      destruction(s2);
    }  
  }
}
