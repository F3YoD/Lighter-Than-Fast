//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

#include "alien.h"

			//****************************//
			/*	      alien	      */
			//****************************//

void load_alien(alien_t * pA, SDL_Renderer * pR, interface_t * pI, int pId){
// role : ce sous programme, charge un alien en lui donnant grace au sdl 
//	  image les 4 images qui sont propre a l'alien. 
//	  de plus on donne un identifiant à l'alien, et une position en
//	  fonction de son identifiant

	const int esp = 35; // on espace entre les aliens

	printf("chargement de l'alien\n");
	pA->id = pId;
	pA->pv = 100;
	pA->img[0] = IMG_Load("../assets/images/alien1.png");
	pA->img[1] = IMG_Load("../assets/images/alien2.png");
	pA->img[2] = IMG_Load("../assets/images/alien3.png");
	pA->img[3] = IMG_Load("../assets/images/alien4.png");
	for(int i = 0; i < 4; i++){
		pA->tex[i] = SDL_CreateTextureFromSurface(pR, pA->img[i]);
	}
	pA->pos.x = pI->ship->img.pos.x + (pI->ship->img.pos.w) / 2 + pId*20 - esp; 
	pA->pos.y = pI->ship->img.pos.y + (pI->ship->img.pos.h) / 2 + pId*10;
}

void update_alien(alien_t * pA, SDL_Renderer * pR, SDL_Event pEv, interface_t * i, int pControl){
// role : ce sous programme affiche un l'alien *pA a la position pA->pos ..
//	  de plus si pControl correspond a pA->id (l'identifiant de 
//	  l'alien) on peu modifier la position de l'alien a l'aide des 
//	  touches directionnelles
//	  sinon on se contente d'afficher l'alien!
// parametrage : si controle = pA->id alors on peut bouger le perso! 
	if(pControl == pA->id){
		int murDroit = i->ship->img.pos.x + 380;
		int murGauche = i->ship->img.pos.x + 100;
		int murHaut = i->ship->img.pos.y + 100;
		int murBas = i->ship->img.pos.y + 290;	
		switch(pEv.type){
			case SDL_KEYDOWN:
				switch(pEv.key.keysym.sym){
					case SDLK_RIGHT:
						if(pA->pos.x < murDroit){
							pA->pos.x++;
						}	
						SDL_QueryTexture(pA->tex[3], NULL, NULL, &pA->pos.w, &pA->pos.h);
						SDL_RenderCopy(pR, pA->tex[3], NULL, &pA->pos);
						break;
					case SDLK_DOWN:
						SDL_QueryTexture(pA->tex[0], NULL, NULL, &pA->pos.w, &pA->pos.h);
						SDL_RenderCopy(pR, pA->tex[0], NULL, &pA->pos);
						if(pA->pos.y < murBas){
							pA->pos.y++;
						}
						break;	
					case SDLK_UP:	
						SDL_QueryTexture(pA->tex[1], NULL, NULL, &pA->pos.w, &pA->pos.h);
						SDL_RenderCopy(pR, pA->tex[1], NULL, &pA->pos);
						if(pA->pos.y > murHaut){
							pA->pos.y--;
						}
						break;
					case SDLK_LEFT:	
						if(pA->pos.x > murGauche){	
							pA->pos.x--;
						}
						
						SDL_QueryTexture(pA->tex[2], NULL, NULL, &pA->pos.w, &pA->pos.h);
						SDL_RenderCopy(pR, pA->tex[2], NULL, &pA->pos);
						break;
				}
				break;
			default:
				// on affiche le perso meme lorsque aucune touche n'est enfoncé
				SDL_QueryTexture(pA->tex[0], NULL, NULL, &pA->pos.w, &pA->pos.h);
				SDL_RenderCopy(pR, pA->tex[0], NULL, &pA->pos);
				break;
		}
	}
	else{
		//on veut quand meme afficher notre aliens dans tout les cas
		SDL_QueryTexture(pA->tex[0], NULL, NULL, &pA->pos.w, &pA->pos.h);
		SDL_RenderCopy(pR, pA->tex[0], NULL, &pA->pos);	
	}
}

void free_alien(alien_t * pA){
// role : libere la memoir utiliser par *pA
	printf("suppression alien\n");
	for(int i = 0; i < 4; i++){
		SDL_FreeSurface(pA->img[i]);
		SDL_DestroyTexture(pA->tex[i]);
	}
}

			//****************************//
			/*	  team    alien	      */
			//****************************//

void load_team(team_t * pT, SDL_Renderer * pR, interface_t * pI){
// role : charge un à un les alien présent dans le vaisseau en appellant 
//	  pTaille fois le sous programme load_alien(...)
	pT->taille = NBRE_ALIENS;
	for(int i = 0; i < pT->taille; i++){
		load_alien(&pT->aliens[i], pR, pI, i);
	}
}

//void drawAlien(alien_t * pA, SDL_Renderer * pR, SDL_Event pEv, interface_t i, int pControl){
void update_team(team_t * pT, SDL_Renderer * pR, SDL_Event pEv, interface_t * pI, int pControl){
// role : parcour tout les membre de l'equpage *pT du vaisseau et appel
//	  le sous programme update_alien qui permet plusieurs chose :
//		- l'affichage de l'alien en paramètre
//		- gere le deplacement de l'alien que l'on controle
//		  (l'alien d'indice pControl)	
	for(int i = 0; i < pT->taille; i++){
		update_alien(&pT->aliens[i], pR, pEv, pI, (pControl));
	}	
}

void freeTeam(team_t * pT){
// role : libère la mémoire utilise pour les membre de l'equipe *pT du type
//	  team_t, en libérant un à un les aliens présent grace au sous 
//	  programme free_alien(..)
	for(int i = 0; i < pT->taille; i++)
		free_alien(&pT->aliens[i]);	
	
	printf("team supprimer\n");
}

