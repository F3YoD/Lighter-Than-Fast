#ifndef _IMAGE_
#define _IMAGE_

#include <SDL2/SDL.h>

typedef struct {
	SDL_Texture * tex;
	SDL_Rect pos;
}image_t;

#endif
