#ifndef _FOND_
#define _FOND_


typedef struct {
	SDL_Surface * img;
	SDL_Texture * tex;
	SDL_Rect pos;
}fond_t;


void load_fond(fond_t *, char * pDest, SDL_Renderer *);
void update_fond(fond_t, SDL_Renderer *);
void free_fond(fond_t *);


#endif
