#include "combat.h"

void
shoot(ship_t *dst, ship_t *src, unsigned short shoot_type)
{
    // TODO implement a way to deal more damages w/ shoot_type
    short touch_score = gen_rand(0, 100);
    unsigned short damage = gen_rand(src->damage_min, src->damage_max);

    if (touch_score < dst->dodge_score || src->belongings.plasma < RULE_COMBAT_ATTACK_COST)
        return;

    if (dst->shield >= damage)
        dst->shield -= damage;
    else
    {
        damage -= dst->shield;
        dst->shield = 0;
        dst->health -= damage;
    }

    src->belongings.plasma -= RULE_COMBAT_ATTACK_COST;
}

void
repair(ship_t *src, int max_health)
{
    // TODO add a chance to fail?
    if (src->belongings.scraps < RULE_COMBAT_REPAIR_COST || src->health == max_health)
        return;

    src->health += RULE_COMBAT_REPAIR_COST;
    src->belongings.scraps -= RULE_COMBAT_REPAIR_COST;
}

void
flee(ship_t *src)
{
    // TODO add a chance to fail?
    if (src->belongings.plasma < RULE_COMBAT_FLEE_COST)
        return;

    src->belongings.plasma -= RULE_COMBAT_FLEE_COST;
}

void
exchange(ship_t *dst, ship_t *src, struct belongings exchanged_goods)
{
    // TODO be sure the asked exchanged_goods are present in src before calling this function

    dst->belongings.plasma += exchanged_goods.plasma;
    dst->belongings.scraps += exchanged_goods.scraps;
    dst->belongings.money += exchanged_goods.money;
}

void
loot(ship_t *dst, ship_t *src)
{
    exchange(dst, src, src->belongings);
}

void
taunt(ship_t *src)
{
    // FIXME
    // Only a funny function to spit fayah at your opponent
}

void
be_sad(ship_t *src)
{
    // FIXME
    // Display sad kaomoji
}

void
be_happy(ship_t *src)
{
    // FIXME
    // Display happy kaomoji
}

void
be_angry(ship_t *src)
{
    // FIXME
    // Display angry kaomoji
}

void
destroy(ship_t **s)
{
    if (*s)
    {
        free(*s);
        *s = NULL;
    }
    // TODO add animation?
}
