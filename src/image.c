#include "image.h"

bool
is_animation(image *img)
{
    return img->nb_frames > 1;
}

image *
load_image(char *path, int delay)
{
    image *img = (image *)malloc(sizeof(image));
    char filepath[MAX_FILEPATH_LENGTH];

    img->curr_frame = 0;
    img->delay = delay;
    img->width = img->height = 0;

    strncpy(img->path, path, MAX_FILEPATH_LENGTH);

    bool path_allows_animation = strstr(path, "%d") != NULL;

    if (!path_allows_animation)
    {
        img->nb_frames = 1;
        img->textures = (SDL_Texture **)malloc(sizeof(SDL_Texture *));
        img->textures[0] = NULL;
    }
    else
    {
        img->nb_frames = 0;
        img->next_frame_time = (unsigned)(-1);

        while (snprintf(filepath, MAX_FILEPATH_LENGTH, path, img->nb_frames), access(filepath, R_OK) != -1)
        {
            img->nb_frames += 1;
        }

        img->textures = (SDL_Texture **)malloc(img->nb_frames * sizeof(SDL_Texture *));

        for (int i = 0; i < img->nb_frames; i++)
        {
            img->textures[i] = NULL;
        }
    }

#ifdef DEBUG
    printf("[+] %s: ready to load %d image%s.\n", path, img->nb_frames, (img->nb_frames > 1) ? "s" : "");
#endif

    return img;
}

void
load_frame(image *img, int n)
{
    if (!img->textures[n])
    {
        if (is_animation(img))
        {
            char realpath[MAX_FILEPATH_LENGTH];
            snprintf(realpath, MAX_FILEPATH_LENGTH, img->path, n);
            img->textures[img->curr_frame] = IMG_LoadTexture(renderer, realpath);
            if (n == 0)
            {
                img->next_frame_time = SDL_GetTicks() + img->delay;
            }
        }
        else if (n == 0)
        {
            img->textures[n] = IMG_LoadTexture(renderer, img->path);
        }

        if (n == 0 && img->width == 0)
        {
            SDL_QueryTexture(img->textures[0], NULL, NULL, &img->width, &img->height);
        }
    }
}

void
permanently_scale_image(image *img, float scale_x, float scale_y)
{
    preload_first_frame(img);

    img->width *= scale_x;
    img->height *= scale_y;
}

void
render_image_scale_clip_align(image *img, int x, int y, float scale_x, float scale_y, int angle, SDL_Rect *clip_r, y_align y_al, x_align x_al)
{
    SDL_Rect r;

    // Show next frame if time is ok
    if (is_animation(img) && SDL_GetTicks() >= img->next_frame_time)
    {
        img->next_frame_time = SDL_GetTicks() + img->delay;
        img->curr_frame = (img->curr_frame + 1) % img->nb_frames;
    }

    // Load texture if not loaded yet
    load_frame(img, img->curr_frame);

    r = (SDL_Rect){ .x = x, .y = y };
    r.w = scale_x * (clip_r ? clip_r->w : img->width);
    r.h = scale_y * (clip_r ? clip_r->h : img->height);

    if (x_al != ALIGN_LEFT)
    {
        r.x -= (x_al == ALIGN_RIGHT) ? r.w : (r.w / 2);
    }

    if (y_al != ALIGN_TOP)
    {
        r.y -= (y_al == ALIGN_BOTTOM) ? r.h : (r.h / 2);
    }

    SDL_RenderCopy(renderer, img->textures[img->curr_frame], clip_r, &r);
}

void
free_image(image **img)
{
    if (*img)
    {
        if ((*img)->textures)
        {
            for (int i = 0; i < (*img)->nb_frames; i++)
            {
                if ((*img)->textures[i])
                {
                    SDL_DestroyTexture((*img)->textures[i]);
                }
            }

            free((*img)->textures);
        }

        free(*img);
    }

    *img = NULL;
}
