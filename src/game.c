#include "game.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"
#define SELF_SHIP_IMAGE "../assets/images/ship2.png"

void play_game(void)
{
#ifdef DEBUG
    puts("* Launching game");
#endif
    // Cosmetics
    SDL_Texture *bg_texture = NULL;
    SDL_Rect health_bar = { 10, 10, 1000, 16 };

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Color white = { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };

    // Map
    map_t map = NULL;
    int map_length = 6;
    int map_max_height = 4;
    int height_index[map_length];

    // Create player's ship
    SDL_Texture *self_texture = NULL;
    SDL_Rect self_pos = { 50, 215, 357, 286 };
    ship_t *self = NULL;

    // Help box
    // TODO
    char *help_txt = "a\nb";
    SDL_Texture *help_texture = create_txt(font, help_txt, white);
    SDL_Rect help_rect = rect_from_texture(help_texture, 800, 600);

    // Gameplay
    SDL_Event event;
    enum menu_choice choice = NEW_GAME;
    bool show_menu = true;
    bool show_help = false;
    bool show_overlay = false;
    bool can_continue = false;

    while (choice != QUIT_GAME)
    {
        if (show_menu)
            choice = menu(can_continue);
        if (choice == QUIT_GAME)
            break;
        else if (choice == NEW_GAME)
        {
            show_fake_loading(1500);

            if (!bg_texture)
                bg_texture = load_img(BACKGROUND_IMAGE);

            if (self != NULL)
                free(self);
            self = gen_self();
            if (!self_texture)
                self_texture = load_img(self->img_path);

            if (map != NULL)
                free(map);
            map = (map_t)malloc(map_length * sizeof(map_col_t));
            gen_map(map, height_index, map_length, map_max_height);

            choice = CONTINUE_GAME;

#ifdef DEBUG
            for (int i = 0; i < map_length; i++)
                for (int j = 0; j < height_index[i]; j++)
                {
                    /* map_node_t node = map[i][j]; */
                    printf("%d%s", j, (j == height_index[i] - 1) ? "\n" : " ");
                }

            puts("We have the map and everything!");
#endif
        }

        can_continue = true; // TODO manage file save
        show_menu = false;
        // Display background
        SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

        // Display player's ship
        SDL_RenderCopy(renderer, self_texture, NULL, &self_pos);

        // Display life and shield
        // TODO use characters to display life or shield
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &health_bar);

        // Display help
        if (show_help)
            SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);

        // Display overlay
        // TODO
        if (show_overlay)
        {
            
        }

        SDL_RenderPresent(renderer);

        // Get user input
        bool action = false;
        while (SDL_PollEvent(&event) && !action)
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
                case SDLK_h:
                    show_help = !show_help;
                    action = true;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                choice = QUIT_GAME;
                action = true;
            default:
                break;
            }
    }

    /* Leave game */
    if (self != NULL)
        free(self); // or let it go, go, go
    if (map != NULL)
        free(map);
    SDL_DestroyTexture(help_texture);
    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_RenderClear(renderer);
}

void show_fake_loading(unsigned int miliseconds)
{
    SDL_Color white = { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };
    SDL_Point pts[][2] = {
        { { 438, 459 }, { 438, 522 } },
        { { 489, 478 }, { 489, 542 } },
        { { 534, 478 }, { 534, 542 } },
        { { 585, 459 }, { 585, 522 } }
    };

    unsigned int endtime = SDL_GetTicks() + miliseconds;

    // Prepare shuttle symbol
    SDL_Texture *shuttle = load_img("../assets/images/big_shuttle_white.png");
    SDL_Rect shuttle_rect = rect_from_texture(shuttle, 437, 238);

    // Prepare "Loading..." message
    SDL_Texture *load_msg = create_txt(font, "Loading...", white);
    SDL_Rect load_rect = rect_from_texture(load_msg, 773, 688);

    while (SDL_GetTicks() < endtime)
        for (int j = 0; j < 4; j++)
        {
            // Show green background
            SDL_SetRenderDrawColor(renderer, 0x0A, 0x35, 0x36, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            // Show shuttle and loading message
            SDL_RenderCopy(renderer, shuttle, NULL, &shuttle_rect);
            SDL_RenderCopy(renderer, load_msg, NULL, &load_rect);

            // Show all lines except one
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
            for (int k = 0; k < 4; k++)
                if (j != k)
                    SDL_RenderDrawLine(renderer, pts[k][0].x, pts[k][0].y, pts[k][1].x, pts[k][1].y);

            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }

    SDL_DestroyTexture(shuttle);
    SDL_DestroyTexture(load_msg);

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0xFF);
    SDL_RenderClear(renderer);
}

ship_t *gen_self(void)
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
