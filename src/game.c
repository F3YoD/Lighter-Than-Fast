#include "game.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"

void play_game(bool *show_menu)
{
    #ifdef DEBUG
    puts("* Launching game");
    #endif
    // TODO maybe implement a loading screen!!
    /* Display basic interface */
    // TODO use a while loop to stay in the game till the boss is beaten
    // e.g. while (current_level < map.length)

    // Display background
    SDL_Texture *bg_texture = NULL;
    // TODO maybe use IMG_LoadTexture and macros at the same time
    //  - could be "IMG_CheckLoadTexture" e.g.
    //  - allows to show path of broken load
    //  - allows to use one fewer line still with verbose
    bg_texture = IMG_LoadTexture(renderer, BACKGROUND_IMAGE);
    check_IMG(bg_texture);
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

    // Create and display player's ship
    ship_t *self = gen_self();
    SDL_Texture *self_texture;
    self_texture = IMG_LoadTexture(renderer, self->img_path);
    check_IMG(self_texture);
    SDL_Rect self_pos = { 50, 215, 357, 286 };
    SDL_RenderCopy(renderer, self_texture, NULL, &self_pos);

    SDL_RenderPresent(renderer);

    // Display life and shield
    // TODO use characters to display life or shield

    /* Handle game */
    SDL_Delay(1000);
    *show_menu = true;

    // Manage map
    int map_lentgh = 6;
    int map_max_height = 4;
    map_t map = gen_map2(map_lentgh, map_max_height);
    #ifdef DEBUG
    // iter through columns
    for (int i = 0; i < map_lentgh; i++)
    {
        // TODO bug seems to come from gen_map
        //  - maybe just use two for loops and break if NULL
        //  - access like map_node_t node = map[i][j]
        for (int j = 0; j < map_max_height; j++)
        {
            map_node_t node = map[i][j];
            if (node == NULL)
                break;
            printf("%d ", j);
        }
        puts("");
    }
    #endif
    // TODO display map

    /* Leave game */
    free(self); // or let it go, go, go
    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);
}

ship_t *gen_self()
{
    ship_t *self = (ship_t *)malloc(sizeof(ship_t));

    sprintf(self->name, "UNSC Yvan");
    self->is_shop = false;
    self->health = 300; // TODO replace with balanced values
    self->shield = 100;
    self->belongings.plasma = 100;
    self->belongings.money = 100;
    self->belongings.scraps = 20;
    self->damage_min = 10;
    self->damage_max = 30;
    self->dodge_score = 0.1;
    sprintf(self->img_path, "../assets/images/ship2.png");

    return self;
}
