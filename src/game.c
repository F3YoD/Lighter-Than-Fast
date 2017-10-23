#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "game.h"

// ============================================================= //
//			TEST STRUCT ET SS-PROG			 //
// ============================================================= //

typedef struct {
	int nbreVie;
	SDL_Surface * imgBarreVie;
	SDL_Texture * texture;
	SDL_Rect pos;
}barre_vie_t;

typedef struct {
	int nbrePoints;
	SDL_Surface * imgShield;
	SDL_Texture * texShield;
	SDL_Rect posShield;	
}shield_t;

typedef struct {
	SDL_Surface * img;
	SDL_Texture * tex;
	SDL_Rect pos;
}ship_t;

typedef struct interface {
		barre_vie_t barreVie;
		shield_t shield;
		ship_t ship;	
	}interface_t;

			//****************************//
			/*	  barre de vie 	      */
			//****************************//

void initBarreVie(barre_vie_t * pB,int pVie, char * pDest, SDL_Renderer * pR){
//
	pB->nbreVie = pVie;
	pB->imgBarreVie = IMG_Load(pDest);
	pB->texture = SDL_CreateTextureFromSurface(pR, (pB->imgBarreVie));
	pB->pos.x = 0; pB->pos.y = 0;
}

void afficheBarreVie(barre_vie_t pB, SDL_Renderer * pR){
	SDL_QueryTexture(pB.texture, NULL, NULL, &(pB.pos.w), &(pB.pos.h));
	SDL_RenderCopy(pR, pB.texture, NULL, &pB.pos);
}

void freeBarreVie(barre_vie_t * pB){
	SDL_FreeSurface(pB->imgBarreVie);
	SDL_DestroyTexture(pB->texture);
}
			
			//****************************//
			/*	      shield	      */
			//****************************//

void chargeShield(shield_t * pS, int pPoints, char * pDest, SDL_Renderer * pR){
	pS->nbrePoints = pPoints;
	pS->imgShield = IMG_Load(pDest);
	pS->texShield = SDL_CreateTextureFromSurface(pR, pS->imgShield);
	pS->posShield.x = 0; pS->posShield.y = 60;
}

void afficheShield(shield_t pS, SDL_Renderer * pR){
	SDL_QueryTexture(pS.texShield,NULL,NULL,&pS.posShield.w,&pS.posShield.h);
	SDL_RenderCopy(pR, pS.texShield, NULL, &pS.posShield);
}

void freeShield(shield_t * pS){
	SDL_FreeSurface(pS->imgShield);
	SDL_DestroyTexture(pS->texShield);
}

			//****************************//
			/*	      ship	      */
			//****************************//
void loadShip(ship_t * pS, char * pDest, SDL_Renderer * pR){
	pS->img = IMG_Load(pDest);
	pS->tex = SDL_CreateTextureFromSurface(pR, pS->img);
	pS->pos.x = 50; pS->pos.y = 350;
}

void drawShip(ship_t pS, SDL_Renderer * pR){
	SDL_QueryTexture(pS.tex,NULL,NULL,&pS.pos.w, &pS.pos.h);
	SDL_RenderCopy(pR, pS.tex, NULL, &pS.pos);
}

void freeShip(ship_t * pS){
	SDL_FreeSurface(pS->img);
	SDL_DestroyTexture(pS->tex);
}
	
			//****************************//
			/*	    interface	      */
			//****************************//

void loadInterface(interface_t * pI, SDL_Renderer * pR){
	initBarreVie(&pI->barreVie, 10, "./assets/images/lifebare.png", pR);
	chargeShield(&pI->shield, 100, "./assets/images/shieldbare.png", pR);
	loadShip(&pI->ship, "./assets/images/ship1.png", pR);
}

void drawInterface(interface_t pI, SDL_Renderer * pR){
	afficheBarreVie(pI.barreVie, pR);
	afficheShield(pI.shield, pR);
	drawShip(pI.ship, pR);
}

void destroyInterface(interface_t * pI){
	freeBarreVie(&pI->barreVie);
	freeShield(&pI->shield);
	freeShip(&pI->ship);
}

///////////////////////////////////////////////////////////////////

void game(SDL_Renderer * pRend, SDL_Surface * pEcran){
	
	int continuer = 1;
	SDL_Event ev;
			/* fond */
	SDL_Rect fond[1];
	//SDL_Texture texFond;
			/* ecrire test */
	SDL_Surface * texte = NULL;
	TTF_Font * police = NULL;
	SDL_Color couleurRouge = {255,0,0};
	SDL_Rect posTexte;
	
	interface_t i;
	loadInterface(&i, pRend);
/*	
	///init TTF
	TTF_Init();
	printf("init ttf\n");
	posTexte.x = 10; posTexte.y = 10;
	police = TTF_OpenFont(
	"usr/share/fonts/truetype/tlwg/Garuda.ttf", 16);
	if(!police){
		printf("TTP_OpenFont : %s\n", TTF_GetError());
	}
	texte = TTF_RenderText_Blended(police, "TEST", couleurRouge);
	SDL_BlitSurface(texte, NULL, pEcran, &posTexte);
	///fin init TTF
*/	
		/* affichage fond */
	fond[0].x = 0; fond[0].y = 0; fond[0].w = 1024; fond[0].h = 768;
	SDL_SetRenderDrawColor(pRend, 100,100,100,255);
	SDL_RenderFillRects(pRend, fond, 1);
		
	while(continuer){
		SDL_PollEvent(&ev);
		switch(ev.type){
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym){
					case SDLK_ESCAPE:
						continuer = 0;
						break;
				}
				break;
			case SDL_QUIT:
				continuer = 0;
				break;
		}
		drawInterface(i, pRend);
		SDL_RenderPresent(pRend);
	}
	
	///libération
//	TTF_CloseFont(police);
//	TTF_Quit();
	//SDL_FreeSurface(b.imgBarreVie);
	SDL_FreeSurface(texte);
	destroyInterface(&i);	
}
