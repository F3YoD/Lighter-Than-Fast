#include "game.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"

void play_game(bool *show_menu)
{
    // TODO maybe implement a loading screen!!
    /* Display basic interface */
    // TODO use a while loop to stay in the game till the boss is beaten
    // e.g. while (current_level < map.length)
    // TODO display map
    SDL_Surface *bg_surface = NULL;
    SDL_Texture *bg_texture = NULL;

    bg_surface = IMG_Load(BACKGROUND_IMAGE);
    check_SDL(bg_surface);
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    check_SDL(bg_texture);
    SDL_FreeSurface(bg_surface);

    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    /* Handle game */
    SDL_Delay(3000);

    /* Leave game */
    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);
}
