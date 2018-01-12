#include "combat.h"

void
shoot(ship *dst, ship *src, unsigned short shoot_type)
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
repair(ship *src, int max_health)
{
    // TODO add a chance to fail?
    if (src->belongings.scraps < RULE_COMBAT_REPAIR_COST || src->health == max_health)
        return;

    src->health += RULE_COMBAT_REPAIR_COST;
    if (src->health > max_health) src->health = max_health;
    src->belongings.scraps -= RULE_COMBAT_REPAIR_COST;
}

void
flee(ship *src)
{
    // TODO add a chance to fail?
    if (src->belongings.plasma < RULE_COMBAT_FLEE_COST)
        return;

    src->belongings.plasma -= RULE_COMBAT_FLEE_COST;
}

void
exchange(ship *dst, ship *src, struct belongings exchanged_goods)
{
    // TODO be sure the asked exchanged_goods are present in src before calling this function

    dst->belongings.plasma += exchanged_goods.plasma;
    dst->belongings.scraps += exchanged_goods.scraps;
    dst->belongings.money += exchanged_goods.money;
}

void
buy_health(ship *dst, int max_health)
{
    dst->health += RULE_SHOP_HEALTH_BACK;
    if (dst->health > max_health) dst->health = max_health;
    dst->belongings.money -= RULE_SHOP_HEALTH_COST;
}

void
buy_scraps(ship *dst, ship *src)
{
    dst->belongings.scraps += RULE_SHOP_SCRAPS_BACK;
    src->belongings.scraps -= RULE_SHOP_SCRAPS_BACK;
    dst->belongings.money -= RULE_SHOP_SCRAPS_COST;
}

void
loot(ship *dst, ship *src)
{
    exchange(dst, src, src->belongings);
}

void
taunt(ship *src)
{
    // FIXME
    // Only a funny function to spit fayah at your opponent
}

void
be_sad(ship *src)
{
    // FIXME
    // Display sad kaomoji
}

void
be_happy(ship *src)
{
    // FIXME
    // Display happy kaomoji
}

void
be_angry(ship *src)
{
    // FIXME
    // Display angry kaomoji
}

void
destroy(ship **s)
{
    if (*s)
    {
        free_image(&(*s)->img);
        free(*s);
        *s = NULL;
    }
    // TODO add animation?
}
