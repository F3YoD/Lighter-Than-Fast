#ifndef _MENU_
#define _MENU_

#include <SDL2/SDL.h>

// NB_CHOICES allows to know the boundary of the enum
typedef enum { PLAY_GAME, QUIT_GAME, NB_CHOICES } menu_choice_t;

menu_choice_t menu(SDL_Renderer *);

#endif
