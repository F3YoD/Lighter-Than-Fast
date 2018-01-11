#include "tools.h"

int
gen_rand(unsigned short int min, unsigned short int max)
{
    if (min == max)
        return min;
    if (min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }
    return rand() % (max - min + 1) + min;
}

void
wait_key_press(void)
{
    SDL_Event e;
    do
    {
        SDL_WaitEvent(&e);
    } while (e.type != SDL_KEYUP);
}

SDL_Texture *
load_img(char *path)
{
    SDL_Texture *t;
    t = IMG_LoadTexture(renderer, path);
    if (!t)
    {
        fprintf(stderr, "could not write \"%s\": %s\n", path, TTF_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit(); /* This frees memory for everything SDL-related */
        exit(EXIT_FAILURE);
    }
    else if (PRINT_DEBUG)
        printf("\"%s\" loaded as texture\n", path);

    return t;
}

SDL_Texture *
create_txt(TTF_Font *font, char *str, SDL_Color color)
{
    SDL_Texture *t;
    SDL_Surface *tmp;
    tmp = TTF_RenderText_Blended(font, (str[0] == '\0' ? " " : str), color);
    if (!tmp)
    {
        fprintf(stderr, "could not write \"%s\": %s\n", str, TTF_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit(); /* This frees memory for everything SDL-related */
        exit(EXIT_FAILURE);
    }
    else if (PRINT_DEBUG)
        printf("\"%s\" loaded as surface -> ", str);
    t = SDL_CreateTextureFromSurface(renderer, tmp);
    check_SDL(t);
    SDL_FreeSurface(tmp);

    return t;
}

SDL_Texture *
texture_from_text(TTF_Font *font, unsigned short line_spacing, SDL_Rect origin, char *str, SDL_Color color, x_align align)
{
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Texture *t = NULL;
    char *token = NULL;
    char sep[] = "\n";
    int font_height = TTF_FontHeight(font);
    char *tmp, *tofree;
    tmp = tofree = strdup(str);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);

    while ((token = strsep(&tmp, sep)) != NULL)
    {
        // Render line
        t = create_txt(font, token, color);
        SDL_QueryTexture(t, NULL, NULL, &origin.w, &origin.h);

        if (align == ALIGN_CENTER)
            origin.x -= origin.w / 2;
        else if (align == ALIGN_RIGHT)
            origin.x -= origin.w;

        SDL_RenderCopy(renderer, t, NULL, &origin);

        // Prepare next line
        SDL_DestroyTexture(t);
        origin.y += line_spacing + font_height;
    }

    SDL_SetRenderTarget(renderer, NULL);
    return texture;
}

SDL_Rect
rect_from_texture(SDL_Texture *t, unsigned short int x, unsigned short int y)
{
    SDL_Rect r = { .x = x, .y = y };
    SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);

    return r;
}

bool
cmpnval(unsigned val, unsigned n, ...)
{
    va_list l;

    va_start(l, n);
    for (unsigned i = 0; i < n; i++)
        if (val == va_arg(l, unsigned))
            return true;
    va_end(l);

    return false;
}
