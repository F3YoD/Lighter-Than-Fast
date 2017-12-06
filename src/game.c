#include "game.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"
#define SELF_SHIP_IMAGE "../assets/images/ship2.png"

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

    // Display life and shield
    // TODO use characters to display life or shield
    SDL_Rect health_bar = { 10, 10, 1000, 16 };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
    SDL_RenderFillRect(renderer, &health_bar);

    SDL_RenderPresent(renderer);

    /* Handle game */
    SDL_Delay(1000);
    *show_menu = true;

    // Manage map
    int map_length = 6;
    int map_max_height = 4;
    int height_index[map_length];
    map_t map = (map_t)malloc(map_length * sizeof(map_col_t));
    gen_map(map, height_index, map_length, map_max_height);

#ifdef DEBUG
    // iter through columns
    for (int i = 0; i < map_length; i++)
    {
        for (int j = 0; j < height_index[i]; j++)
        {
            map_node_t node = map[i][j];
            printf("%d ", j);
        }
        puts("");
    }
#endif

    // TODO display map
    // TODO create overlay (would be used for maps, possibly shops)
    //  - easier: create new window with only wanted content
    //  - harder: overlay on renderer

    /* Leave game */
    free(self); // or let it go, go, go
    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);
}

void _play_game(void)
{
#ifdef DEBUG
    puts("* Launching game");
#endif
    // Cosmetics
    SDL_Texture *bg_texture = NULL;
    SDL_Rect health_bar = { 10, 10, 1000, 16 };

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0xFF);
    SDL_RenderClear(renderer);

    // Map
    map_t map = NULL;
    int map_length = 6;
    int map_max_height = 4;
    int height_index[map_length];

    // Create player's ship
    SDL_Texture *self_texture = NULL;
    SDL_Rect self_pos = { 50, 215, 357, 286 };
    ship_t *self = gen_self();

    // Gameplay
    SDL_Event event;
    menu_choice_t choice = PLAY_GAME;
    bool show_menu = true;

    while (choice != QUIT_GAME)
    {
        if (show_menu)
            choice = _menu();
        if (!map)
        {
            bg_texture = IMG_LoadTexture(renderer, BACKGROUND_IMAGE);
            check_IMG(bg_texture);

            self_texture = IMG_LoadTexture(renderer, self->img_path);
            check_IMG(self_texture);

            map = (map_t)malloc(map_length * sizeof(map_col_t));
            gen_map(map, height_index, map_length, map_max_height);

#ifdef DEBUG
            for (int i = 0; i < map_length; i++)
                for (int j = 0; j < height_index[i]; j++)
                {
                    map_node_t node = map[i][j];
                    printf("%d%s", j, (j == height_index[i] - 1) ? "\n" : " ");
                }

            puts("We have the map and everything!");
#endif
        }
        if (choice != QUIT_GAME)
        {
            show_menu = false;
            // Display background
            SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

            // Display player's ship
            SDL_RenderCopy(renderer, self_texture, NULL, &self_pos);

            // Display life and shield
            // TODO use characters to display life or shield
            SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
            SDL_RenderFillRect(renderer, &health_bar);

            SDL_RenderPresent(renderer);

            // Get user input
            bool action = false;
            while (!action)
                while (SDL_PollEvent(&event))
                {
                    action = false;
                    switch (event.type)
                    {
                    case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                        case SDLK_TAB:
                            show_menu = true;
                            action = true;
                            break;
                        default:
                            break;
                        }
                        break;
                    case SDL_QUIT:
                        choice = QUIT_GAME;
                    default:
                        break;
                    }
                }

            // TODO display map
            // TODO create overlay (would be used for maps, possibly shops)
            //  - easier: create new window with only wanted content
            //  - harder: overlay on renderer
        }
    }

    /* Leave game */
    free(self); // or let it go, go, go
    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);
}

void show_fake_loading(int seconds)
{
    SDL_Rect pos1, pos2, pos3, pos4; // ship shakes between four positions
    /* pos1 = {  }; */
    // write background here
    // here
    for (int i = 0; i < seconds; i++)
    {
        // The body of this loop must take exactly one second
        SDL_Delay(250);
        SDL_Delay(250);
        SDL_Delay(250);
        SDL_Delay(250);
    }
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
    sprintf(self->img_path, SELF_SHIP_IMAGE);

    return self;
}
