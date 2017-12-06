#ifndef _FOND_
#define _FOND_

#include <SDL2/SDL.h>
#include "extern.h"
#include "image.h"

typedef struct {
	image_t fond;
	image_t fond_top;
	image_t fond_right;
}fond_t;

void load_fond(fond_t *);
void update_fond(fond_t *);
void free_fond(fond_t *);

#endif
