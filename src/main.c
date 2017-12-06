#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"
#include "game.h"

#include "extern.h"

// =================================== //
// 		CONSTANTES             //
// =================================== //

#define ETAT_MENU 0
#define ETAT_GAME 1
#define ETAT_QUIT 2

int main(int argc, char * argv[]){
   	char nom[40];
    	printf("saisir nom (sans espaces) : ");
    	scanf("%s", nom);
   	///variables
    	//SDL_Renderer * renderer = NULL;
    	int State = 0;
    	SDL_Surface * ecran = NULL;
    	//SDL_Window * fenetre = NULL;
    	// DEBUG
    	///fin variables

    	if(SDL_Init(SDL_INIT_VIDEO) != 0){
       		//on lance la sdl
       		fprintf(stdout, "echec de l'init sdl (%s)\n",SDL_GetError());
        	return EXIT_FAILURE;
    	}
    	printf("***** LANCEMENT SDL *****\n");

    	///init fenetre
		// on met en place la fenetre grace a SDL_Window*
		// puis on cree la fenetre de la maniere standard
		// suivante : 'fenetre = SDL_CreateWindow();'
    	fenetre = SDL_CreateWindow(
        	"Projet Lighter Than Fast: Unknow Within",
        	SDL_WINDOWPOS_UNDEFINED,
        	SDL_WINDOWPOS_UNDEFINED,
        	1024,
        	768,
        	0
    	);
    	///fin init fenetre

    ///init ecran surface
    ecran = SDL_GetWindowSurface(fenetre);
    // je met les caractéristique de la fenetre dans une surface
    // car on doit se servir de surface pour ecrire du texte dans
    // notre fenetre
    ///fin init ecran surface

    // DEBUG

    ///init renderer
    renderer = SDL_CreateRenderer(fenetre, -1,
                                  SDL_RENDERER_ACCELERATED);
    ///fin init renderer

    // on lance notre menu le joueur va donc faire un choix dans ce menu
    // il sera diriger soit dans le jeu, soit dans un tuto, option, ..etc
    // ou bien quitter directement
    menu(&State);
    switch(State){
    case ETAT_GAME :
        printf("***** DEBUT DE PARTIE *****\n\n\n");
        game(ecran, nom);
        break;
    case ETAT_QUIT:
        // le programme se ferme !
        printf("***** FERMETURE LTF *****\n");
        break;
    default :
        // on quitte le programme egalement
        printf("erreur de direction apres le menu\n");
        break;
    }

    ///libération mémoire
    //SDL_FreeSurface(ecran); // erreur de segmentation lors de l'utilisation de ce
            // sous programme de libération de surface
    SDL_DestroyWindow(fenetre);
    SDL_DestroyRenderer(renderer);
    printf("jeu libéré\n");
    ///fin libération mémoire

    SDL_Quit();
    return EXIT_SUCCESS;
}
