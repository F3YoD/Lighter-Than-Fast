#ifndef _IMAGE_H
#define _IMAGE_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "shared.h"
#include "list.h"

#define MAX_FILEPATH_LENGTH 64

#define preload_first_frame(img) load_frame((img), 0)

#define render_image_scale(img, x, y, scx, scy) render_image_scale_clip((img), (x), (y), (scx), (scy), NULL)
#define render_image_clip(img, x, y, r)         render_image_scale_clip((img), (x), (y), 1, 1, (r))
#define render_image(img, x, y)                 render_image_scale_clip((img), (x), (y), 1, 1, NULL)

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
void permanently_scale_image(image *, float, float);
void render_image_scale_clip(image *, int, int, float, float, SDL_Rect *);
void free_image(image **);

#endif /* _IMAGE_H */
