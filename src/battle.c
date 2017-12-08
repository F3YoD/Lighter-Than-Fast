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
	TTF_Font* police = TTF_OpenFont("../assets/fonts/Inter-UI-Regular.ttf", 24);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	SDL_Color couleur = { 255, 0, 0};
	SDL_Rect position;
	position.x = 64; position.y = 663;
	afficher_texte("Tirer",police,couleur,position);
	position.y=position.y+25;
	afficher_texte("Se reparer (10 scraps)",police,couleur,position);
	position.y=position.y+25;
	afficher_texte("Sauter vers un nouvel endroit",police,couleur,position);
	TTF_CloseFont(police);	
}


// ================================================= SOUS PROGRAMME PIERRE PAQ1 =================================================== //

void combat(player_ship_t *pPlayer, ship_t *pPirate, int *pChoi, SDL_Event pEv, bool *pClique, int *pAction, SDL_Rect *pPos_tir){
// role : ce sous programme doit etre utiliser dans la game c-a-d dans la boucle
//	  while!
// parametrage :
//
//
	/// on cree un curseur (qui sera supprimer a la fin de ce sous programme)
	SDL_Texture *curseur = IMG_LoadTexture(renderer, "../assets/images/alien1.png");
	SDL_Rect pos_curseur;
	SDL_Rect pos_curseur_attaque;	
	SDL_Rect pos_curseur_defense;	
	SDL_Rect pos_curseur_fuite;

	/// initialisation des positions des curseurs
	pos_curseur_attaque.x = 20; pos_curseur_attaque.y = 670;		
	pos_curseur_defense.x = 20; pos_curseur_defense.y = 695;		
	pos_curseur_fuite.x = 20; pos_curseur_fuite.y = 720;

	/// initialisation du curseur sur la position du curseur d'attaque
	/// d'attaque en début de combat
	
	int choi = *pChoi;

	/// initialisation de l'action
	bool attaque = false;
	bool defense = false;
	bool fuite = false;

	/// initialisation de l'attaque
	SDL_Texture *tir = IMG_LoadTexture(renderer, "../assets/images/alien1.png");

	switch(choi){
		case CHOI_ATTAQUE:
			pos_curseur = pos_curseur_attaque;
			break;
		case CHOI_DEFENSE:		
			pos_curseur = pos_curseur_defense;
			break;
		case CHOI_FUITE:		
			pos_curseur = pos_curseur_fuite;
			break;
	}

	switch(pEv.type){
		case SDL_KEYDOWN:
			switch(pEv.key.keysym.sym){
				case SDLK_DOWN:
					*pClique = true;
					break;
				case SDLK_SPACE:
					if(pos_curseur.y == pos_curseur_attaque.y){
						*pAction = CHOI_ATTAQUE;
					}	
					break;
			}
			break;
	}
	
	switch(pEv.type){
		case SDL_KEYUP:
			switch(pEv.key.keysym.sym){
				case SDLK_DOWN:
					if(pos_curseur.y == pos_curseur_attaque.y && (*pClique)){
						pos_curseur = pos_curseur_defense;
						(*pChoi) = CHOI_DEFENSE;
						*pClique = false;
					}
					else if(pos_curseur.y == pos_curseur_defense.y && (*pClique)){
						pos_curseur = pos_curseur_fuite;
						(*pChoi) = CHOI_FUITE;
						*pClique = false;
					}	
					else if(pos_curseur.y == pos_curseur_fuite.y && (*pClique)){
						pos_curseur = pos_curseur_attaque;
						(*pChoi) = CHOI_ATTAQUE;
						*pClique = false;
					}
					break;
			}
			break;
	}
	
	if(*pAction == CHOI_ATTAQUE && pPos_tir->x < 800){
		pPos_tir->x += 10;
		SDL_QueryTexture(tir, NULL, NULL, &pPos_tir->w, &pPos_tir->h);
		SDL_RenderCopy(renderer, tir, NULL, &(*pPos_tir));
		SDL_DestroyTexture(tir);

		if (pPos_tir->x >= 800){
			pPirate->hp -= 10;
		}
	}
	else{
		*pAction = NE_FAIT_RIEN;
		pPos_tir->x = 100;
	}

	SDL_QueryTexture(curseur, NULL, NULL, &pos_curseur.w, &pos_curseur.h);
	SDL_RenderCopy(renderer, curseur, NULL, &pos_curseur);

	

	// ====================== liberation ==================== //
	SDL_DestroyTexture(curseur);
}



//void shop(){

//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
