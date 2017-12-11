#include "game.h"
#include "dialogs.h"

#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"

void play_game(void)
{
#ifdef DEBUG
    puts("* Launching game");
#endif
    // Cosmetics
    SDL_Texture *bg_texture = NULL;
    SDL_Texture *bg_overlay = NULL;
    SDL_Texture *continue_texture = NULL;
    SDL_Rect base_overlay_rect = { WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4, 3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 };
    SDL_Rect continue_msg_rect = { 5 * WINDOW_WIDTH / 6, 3 * WINDOW_HEIGHT / 4, 1, 1 };

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Color white = { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };

    // Map
    map_t map = NULL;
    int map_length = 6;
    int map_max_height = 4;
    int height_index[map_length];

    // Create player's ship
    SDL_Texture *self_texture = NULL;
    SDL_Rect self_pos = { WINDOW_WIDTH / 20, 2 * WINDOW_HEIGHT / 7, 357, 286 };
    ship_t *self = NULL;

    // Bars
    SDL_Texture *health_texture = NULL;
    SDL_Texture *health_bg_texture = NULL;
    SDL_Texture *shield_texture = NULL;
    SDL_Texture *shield_bg_texture = NULL;
    SDL_Rect health_bg_rect = { 70, 620, 1, 1 };
    SDL_Rect shield_bg_rect = { 70, 640, 1, 1 };
    SDL_Rect health_clip = { 0, 0, 1, 1 };
    SDL_Rect shield_clip = { 0, 0, 1, 1 };
    SDL_Rect health_rect, shield_rect;

    // Help box
    SDL_Texture *help_texture = NULL;
    char help_txt[] = "Aide :\n"
        "ESC : Menu\n"
        "H : Aide";
    SDL_Rect help_rect = { WINDOW_WIDTH - 224, WINDOW_HEIGHT - 128, 1, 1 };

    // Gameplay
    enum menu_choice choice = NEW_GAME;
    int msg_counter;
    SDL_Event event;
    bool show_menu = true;
    bool show_help = false;
    bool show_map = false;
    bool can_continue = false;
    bool action = false;

    while (choice != QUIT_GAME)
    {
        if (show_menu)
            choice = menu(can_continue);
        if (choice == QUIT_GAME)
            break;
        else if (!can_continue || choice == NEW_GAME)
        {
            show_fake_loading(1500);

            msg_counter = 0;
            can_continue = true;

            if (!bg_texture)
                bg_texture = load_img(BACKGROUND_IMAGE);

            if (!bg_overlay)
                bg_overlay = load_img("../assets/images/1px_overlay.png");

            if (!help_texture)
            {
                help_texture = texture_from_text(font, 5, help_rect, help_txt, white, ALIGN_LEFT);
                help_rect.w = 200; help_rect.h = 120;
                help_rect.x -= 10;
                help_rect.y -= 10;
            }

            if (!continue_texture)
                continue_texture = texture_from_text(font, 1, continue_msg_rect, "Appuyez sur une touche pour continuer...", white, ALIGN_RIGHT);

            if (self != NULL)
                free(self);
            self = gen_self();
            if (!self_texture)
                self_texture = load_img(self->img_path);

            if (!health_texture)
            {
                health_texture = load_img("../assets/images/health.png");
                SDL_QueryTexture(health_texture, NULL, NULL, &health_bg_rect.w, &health_bg_rect.h);
                health_rect = health_bg_rect;
                health_clip.h = health_rect.h;
            }
            if (!health_bg_texture)
                health_bg_texture = load_img("../assets/images/health_gray.png");

            if (!shield_texture)
            {
                health_texture = load_img("../assets/images/shield.png");
                SDL_QueryTexture(shield_texture, NULL, NULL, &shield_bg_rect.w, &shield_bg_rect.h);
                shield_rect = shield_bg_rect;
                shield_clip.h = shield_rect.h;
            }
            if (!shield_bg_texture)
                health_bg_texture = load_img("../assets/images/shield_gray.png");

            if (map != NULL)
                free(map);
            map = (map_t)malloc(map_length * sizeof(map_col_t));
            gen_map(map, height_index, map_length, map_max_height);
#ifdef DEBUG
            for (int i = 0; i < map_length; i++)
                for (int j = 0; j < height_index[i]; j++)
                    printf("%d%s", j, (j == height_index[i] - 1) ? "\n" : " ");
#endif
        }

        SDL_RenderClear(renderer);

        show_menu = false;
        action = false;

        // Display background
        SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

        // Display player's ship
        SDL_RenderCopy(renderer, self_texture, NULL, &self_pos);

        // Display life and shield
        SDL_RenderCopy(renderer, shield_bg_texture, NULL, &health_bg_rect);
        // TODO Add ability to track max health?
        health_rect.w = self->health * health_bg_rect.w / 100;
        health_clip.w = health_rect.w;
        SDL_RenderCopy(renderer, health_texture, &health_clip, &health_rect);

        // Display help
        if (show_help)
        {
            SDL_RenderCopy(renderer, bg_overlay, NULL, &help_rect);
            SDL_RenderCopy(renderer, help_texture, NULL, NULL);
        }

        // Display overlay
        if (msg_counter < NB_DIALOGS)
        {
            SDL_Texture *dialog_texture = texture_from_text(font, 10, base_overlay_rect, dialogs[msg_counter], white, ALIGN_LEFT);

            SDL_RenderCopy(renderer, bg_overlay, NULL, NULL);
            SDL_RenderCopy(renderer, dialog_texture, NULL, NULL);
            SDL_RenderCopy(renderer, continue_texture, NULL, NULL);

            SDL_RenderPresent(renderer);

            SDL_DestroyTexture(dialog_texture);

            wait_key_press(-1);
            msg_counter++;
            choice = CONTINUE_GAME;
            show_map = true;
            action = true;
        }
        else if (show_map)
        {
            SDL_RenderCopy(renderer, bg_overlay, NULL, NULL);

            // All images must be the same size, use transparency to deal with different-sized icons
            SDL_Texture *red_dot_tex = load_img("../assets/images/red_dot.png");
            SDL_Texture *blue_dot_tex = load_img("../assets/images/blue_dot.png");
            SDL_Texture *gray_dot_tex = load_img("../assets/images/gray_dot.png");
            SDL_Texture *dot_tex = NULL;
            SDL_Rect icon_rect;
            SDL_QueryTexture(red_dot_tex, NULL, NULL, &icon_rect.w, &icon_rect.h);
            icon_rect.x = base_overlay_rect.x - icon_rect.w / 2;
            unsigned int step_x, step_y;
            step_x = base_overlay_rect.w / (map_length + 1);

            for (int i = 0; i < map_length; i++)
            {
                icon_rect.x += step_x;
                printf("column %d: x = %d\n", i, icon_rect.x);

                icon_rect.y = base_overlay_rect.y - icon_rect.h / 2;
                step_y = base_overlay_rect.h / (height_index[i] + 1);
                for (int j = 0; j < height_index[i]; j++)
                {
                    icon_rect.y += step_y;
                    printf(" line %d:  y = %d\n", j, icon_rect.y);
                    dot_tex = map[i][j]->is_shop ? blue_dot_tex : red_dot_tex;
                    SDL_RenderCopy(renderer, dot_tex, NULL, &icon_rect);
                }
            }

            SDL_RenderPresent(renderer);
            wait_key_press(-1);
            show_map = false;
            action = true;
        }

        if (!action) // the rendering must be done when an action is done
            SDL_RenderPresent(renderer);

        // Get user input
        // TODO try with SDL_WaitEvent once this is more complete
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
                case SDLK_m:
                    show_map = !show_map;
                    action = true;
                    break;
                case SDLK_h:
                    show_help = !show_help;
                    action = true;
                    break;
#ifdef DEBUG
                case SDLK_q:
                    choice = QUIT_GAME;
                    action = true;
                    break;
#endif
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

        #ifndef DEBUG
        if (choice == QUIT_GAME)
        {
            // TODO show dialog asking if user is sure
        }
        #endif
    }

    /* Leave game */
    if (self != NULL)
        free(self); // or let it go, go, go
    if (map != NULL)
        free(map);
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

    int i = 0;
    while (SDL_GetTicks() < endtime)
    {
        // Show green background
        SDL_SetRenderDrawColor(renderer, 0x0A, 0x35, 0x36, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Show shuttle and loading message
        SDL_RenderCopy(renderer, shuttle, NULL, &shuttle_rect);
        SDL_RenderCopy(renderer, load_msg, NULL, &load_rect);

        // Show all lines except one
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        for (int j = 0; j < 4; j++)
            if (j != i)
                SDL_RenderDrawLine(renderer, pts[j][0].x, pts[j][0].y, pts[j][1].x, pts[j][1].y);

        i = (i + 1) % 4;

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(shuttle);
    SDL_DestroyTexture(load_msg);

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0xFF);
    SDL_RenderClear(renderer);
}
