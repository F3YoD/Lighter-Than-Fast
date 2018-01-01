#include "combat.h"

void
shoot(ship_t *dst, ship_t *src, unsigned short shoot_type)
{
    // TODO implement a way to deal more damages
    short touch_score = gen_rand(0, 100);
    unsigned short damage = gen_rand(src->damage_min, src->damage_max);

    if (touch_score < dst->dodge_score)
        return;

    if (dst->shield >= damage)
        dst->shield -= damage;
    else
    {
        damage -= dst->shield;
        dst->shield = 0;
        dst->health -= damage;
    }

    // FIXME move this to play_game
    if (dst->health <= 0)
    {
        loot(src, dst);
        destroy(dst);
    }
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
destroy(ship_t *s)
{
    if (s)
    {
        free(s);
        s = NULL;
    }
    // TODO add animation?
}
