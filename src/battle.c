#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "battle.h"
#include "ships.h"
#include "tools.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void shoot(ship_t *s1, ship_t *s2, const int shoottype)
{
    // We can shoot one, two or three times at once
    // The more we shoot, the more expensive in plasma it is
    int damage_min = s1->damage_min;
    int damage_max = s1->damage_min;

    // Increase damage depending on type
    // TODO establish realistic rates
    // Maybe:
    // damage_min *= shoottype;
    if (shoottype == 2)
    {
        damage_min++;
        damage_max++;
    }
    else if (shoottype == 3)
    {
        damage_min = damage_min+2;
        damage_max = damage_max+2;
    }

    // Determine inflicted damage
    int touch_chance = CreeAlea(0, 100);
    int damage = CreeAlea(damage_min, damage_max);
    if (touch_chance > s2->dodge_score)
    {
        if (s2->shield < damage)
        {
            damage = damage-s2->shield;
            s2->shield = 0;
            s2->hp = s2->hp - damage;
        }
        else if (s2->shield > damage)
        {
            s2->shield = s2->shield - damage;
        }
        else if (s2->hp < damage)
        {
            // destruction(s2);
            // TODO à la destruction, ne pas oublier de loot()
        }
        if (s2->hp <= 0){
            // destruction(s2);
        }
    }
}

int exchange(ship_t *s1, ship_t *s2, belongings_t *from_s1, belongings_t *from_s2) {
    /*
     * Details on `given`:
     * It's a structure defining how much money, scraps and plasma s1 gives to s2
     */
    belongings_t *b1 = s1->belongings;
    belongings_t *b2 = s2->belongings;

    // If either ship doesn't have enough, abort, i.e. return -1
    // That allows us to test the outcome of the exchange
    if (b1->plasma < from_s1->plasma || b2->plasma < from_s2->plasma ||
        b1->money  < from_s1->money  || b2->money  < from_s2->money  ||
        b1->scraps < from_s1->scraps || b2->scraps < from_s2->scraps) {
        return -1;
    }

    // s2 gives to s1
    b1->plasma += from_s2->plasma;
    b2->plasma -= from_s2->plasma;

    b1->money += from_s2->money;
    b2->money -= from_s2->money;

    b1->scraps += from_s2->money;
    b2->scraps -= from_s2->scraps;

    // s1 gives to s2
    b2->plasma += from_s1->plasma;
    b1->plasma -= from_s1->plasma;

    b2->money += from_s1->money;
    b1->money -= from_s1->money;

    b2->scraps += from_s1->money;
    b1->scraps -= from_s1->scraps;

    return 0;
}

void loot(ship_t *s1, ship_t *s2)
{
    // s1 takes everything from s2
    // TODO maybe implement the fact that some of s2's belongings are lost in the process?
    // maybe through a `total` parameter: if true, everything goes, else only some part of it

    // s1 ain't giving nothing
    belongings_t *empty = (belongings_t *)malloc(sizeof(belongings_t));
    empty->plasma = empty->money = empty->scraps = 0;

    exchange(s1, s2, empty, s2->belongings);

    free(empty);
}

void init_menu_combat(){
	TTF_Font* police = TTF_OpenFont("../assets/fonts/Inter-UI-Regular.ttf", 12);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	SDL_Color couleur = { 20, 200, 20};
	SDL_Rect position;
	position.x = 16; position.y = 663;
	afficher_texte("Tirer",police,couleur,position);
	position.y=position.y+20;
	afficher_texte("Se reparer (10 scraps)",police,couleur,position);
	position.y=position.y+20;
	afficher_texte("Sauter vers un nouvel endroit",police,couleur,position);
	TTF_CloseFont(police);	
}


