#ifndef _IMAGE_
#define _IMAGE_

typedef struct {
	SDL_Surface * img;
	SDL_Texture * tex;
	SDL_Rect pos;
}image_t;

#endif
