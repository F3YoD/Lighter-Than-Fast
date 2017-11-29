#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "macros.h"
#include "menu.h"
#include "game.h"
#include "tools.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

/*
 * IDEAS:
 *  - get rid of interface.{h,c} and use it all in game.c
 *    - would allow to have more expressive code
 *  - get rid of everything jauge.{h,c}
 *    - should be rendered when the ship's life/shield changes
 *  - get rid of everything fond.{h,c}
 *    - it should be generated directly from game.c
 *  - are the aliens overkill?
 */

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    /* Init SDL */
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int img_init = IMG_Init(img_flags);
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || img_init != img_flags)
    {
        fprintf(stderr, "/!\\ Could not init SDL: %s\nSDL_image flags: %d/%d\n",
                SDL_GetError(), img_init, img_flags);
        return EXIT_FAILURE;
    }

    // Create window
    window = SDL_CreateWindow("Lighter Than Fast: Unknown Within",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    check_SDL(window);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    check_SDL(renderer);

    /* Get user selection */
    // TODO implement a "back to main menu" option
    bool show_menu;
    do
    {
        show_menu = false;
        switch (menu(renderer))
        {
        case PLAY_GAME:
            puts("Playing:");
            // TODO lancer le jeu
            play_game(renderer, &show_menu);
        case QUIT_GAME:
        default:
            break;
        }
    } while (show_menu);

    /* Exit */
    // TODO create goodbye screen
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
