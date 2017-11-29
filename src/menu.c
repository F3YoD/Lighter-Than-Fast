#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "macros.h"
#include "menu.h"

#define MENU_BG "../assets/images/menu.bmp"

menu_choice_t menu(SDL_Renderer *renderer)
{
    /* Display background */
    SDL_Surface *bg_surface = NULL;
    SDL_Texture *bg_texture = NULL;

    bg_surface = SDL_LoadBMP(MENU_BG);
    check_SDL(bg_surface);
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    check_SDL(bg_texture);
    SDL_FreeSurface(bg_surface);

    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    /* Get user's choice */
    menu_choice_t choice = QUIT_GAME;
    int quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                choice = PLAY_GAME;
            case SDL_QUIT:
                quit = true;
            default:
                break;
            }
        }
    }

    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);

    return choice;
}
