#ifndef _IMAGE_H
#define _IMAGE_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "shared.h"
#include "list.h"

#define MAX_FILEPATH_LENGTH 64

typedef struct
{
    int width;
    int height;
    int nb_frames;
    int curr_frame;
    unsigned delay;
    unsigned next_frame_time;
    char path[MAX_FILEPATH_LENGTH];
    SDL_Texture **textures;
} image;

bool is_animation(image *);

image *load_image(char *, int);
void load_frame(image *, int);
void preload_first_frame(image *);
void permanently_scale_image(image *, float, float);
void render_image(image *, int, int, int, int);
void free_image(image **);

#endif /* _IMAGE_H */
