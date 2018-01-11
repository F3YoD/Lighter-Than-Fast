#ifndef _IMAGE_H
#define _IMAGE_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "shared.h"
#include "list.h"
#include "tools.h"

#define MAX_FILEPATH_LENGTH 64

#define preload_first_frame(img) load_frame((img), 0)

#define render_image_scale_clip(img, x, y, scx, scy, r)         render_image_scale_clip_align((img), (x), (y), (scx), (scy), 0, (r), ALIGN_TOP, ALIGN_LEFT)
#define render_image_scale_align(img, x, y, scx, scy, alv, alh) render_image_scale_clip_align((img), (x), (y), (scx), (scy), 0, NULL, (alv), (alh))
#define render_image_clip_align(img, x, y, r, alv, alh)         render_image_scale_clip_align((img), (x), (y), 1, 1, 0, (r), (alv), (alh))
#define render_image_scale(img, x, y, scx, scy)                 render_image_scale_clip_align((img), (x), (y), (scx), (scy), 0, NULL, ALIGN_TOP, ALIGN_LEFT)
#define render_image_clip(img, x, y, r)                         render_image_scale_clip_align((img), (x), (y), 1, 1, 0, (r), ALIGN_TOP, ALIGN_LEFT)
#define render_image_align(img, x, y, alv, alh)                 render_image_scale_clip_align((img), (x), (y), 1, 1, 0, NULL, (alv), (alh))
#define render_image(img, x, y)                                 render_image_scale_clip_align((img), (x), (y), 1, 1, 0, NULL, ALIGN_TOP, ALIGN_LEFT)

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
void render_image_scale_clip_align(image *, int, int, float, float, int, SDL_Rect *, y_align, x_align);
void free_image(image **);

#endif /* _IMAGE_H */
