#include "menu.h"

#define MENU_BG "../assets/images/menu.bmp"

menu_choice_t menu()
{
    #ifdef DEBUG
    puts("* Loading menu");
    #endif
    /* Display background */
    SDL_Texture *bg_texture = NULL;
    bg_texture = IMG_LoadTexture(renderer, MENU_BG);
    check_IMG(bg_texture);

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
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    quit = true;
                    break;
                default:
                    choice = PLAY_GAME;
                    quit = true;
                    break;
                }
                break;
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
