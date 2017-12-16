#include "game.h"
#include "dialogs.h"

#define SHIPS_SCALE 6
#define BACKGROUND_IMAGE "../assets/images/gameFond1.jpg"

void play_game(void)
{
#ifdef DEBUG
    puts("* Launching game");
#endif
    // Cosmetics
    SDL_Texture *bg_texture, *bg_overlay, *dialog_texture, *continue_texture, *alien_pointer;
    bg_texture = bg_overlay = continue_texture = alien_pointer = NULL;
    SDL_Rect base_overlay_rect = { WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4, 3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 };
    SDL_Rect continue_msg_rect = { 5 * WINDOW_WIDTH / 6, 3 * WINDOW_HEIGHT / 4, 1, 1 };

    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Color white = { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };

    // Map
    SDL_Texture *red_dot_texture, *blue_dot_texture, *gray_dot_texture, *dot_texture;
    red_dot_texture = blue_dot_texture = gray_dot_texture = dot_texture = NULL;
    map_t map = NULL;
    int map_length = 6;
    int map_max_height = 4;
    int height_index[map_length];
    SDL_Rect icon_rect, alien_pointer_map_rect;
    unsigned int step_x, step_y;
    int choice_node = 0;

    // Create player's ship
    SDL_Texture *self_texture = NULL;
    SDL_Rect self_rect = { WINDOW_WIDTH / 20, 2 * WINDOW_HEIGHT / 7, 357, 286 };
    ship_t *self = NULL;
    unsigned int self_curr_health;

    // Create foe's ship
    SDL_Texture *foe_texture = NULL;
    // TODO change to be right-aligned
    SDL_Rect foe_rect = { 4 * WINDOW_WIDTH / 5, 2 * WINDOW_HEIGHT / 7, 1, 1 };
    ship_t *foe = NULL;
    unsigned int foe_curr_health;

    // Self bars
    SDL_Texture *health_texture, *health_bg_texture, *shield_texture, *shield_bg_texture;
    health_texture = health_bg_texture = shield_texture = shield_bg_texture = NULL;
    SDL_Rect health_bg_rect, shield_bg_rect, health_rect, shield_rect, health_clip, shield_clip;
    health_bg_rect.x = health_rect.x = shield_bg_rect.x = shield_rect.x = self_rect.x;
    health_clip.x = health_clip.y = shield_clip.x = shield_clip.y = 0;

    // Self bars
    SDL_Texture *foe_health_texture, *foe_health_bg_texture, *foe_shield_texture, *foe_shield_bg_texture;
    foe_health_texture = foe_health_bg_texture = foe_shield_texture = foe_shield_bg_texture = NULL;
    SDL_Rect foe_health_bg_rect, foe_shield_bg_rect, foe_health_rect, foe_shield_rect, foe_health_clip, foe_shield_clip;
    foe_health_bg_rect.x = foe_health_rect.x = foe_shield_bg_rect.x = foe_shield_rect.x = foe_rect.x;
    foe_health_clip.x = foe_health_clip.y = foe_shield_clip.x = foe_shield_clip.y = 0;

    // Help box
    SDL_Texture *help_texture = NULL;
    char help_txt[] = "Aide\n"
        "ESC : Menu\n"
        "M : Map\n"
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
        if (!can_continue && choice == QUIT_GAME)
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

            if (!alien_pointer)
                alien_pointer = load_img("../assets/images/alien1.png");

            if (self != NULL)
                free(self);
            self = gen_self();
            if (!self_texture)
            {
                self_texture = load_img(self->img_path);
                self_rect = rect_from_texture(self_texture, self_rect.x, self_rect.y);
                rect_scale(&self_rect, SHIPS_SCALE);
            }

            if (foe != NULL)
            {}
                // TODO
            // foe_texture is loaded when a new ennemy is loaded

            if (!health_texture)
            {
                health_texture = load_img("../assets/images/health.png");
                health_bg_rect = health_rect = rect_from_texture(health_texture, health_rect.x, health_rect.y);
                health_bg_rect.y = health_rect.y = self_rect.y + self_rect.h + 10;
                health_clip.h = health_rect.h;
            }
            if (!health_bg_texture)
                health_bg_texture = load_img("../assets/images/health_gray.png");

            if (!shield_texture)
            {
                shield_texture = load_img("../assets/images/shield.png");
                shield_rect = shield_bg_rect = rect_from_texture(shield_texture, shield_rect.x, shield_rect.y);
                shield_bg_rect.y = shield_rect.y = self_rect.y + self_rect.h + health_rect.h + 10;
                shield_clip.h = shield_rect.h;
            }
            if (!shield_bg_texture)
                shield_bg_texture = load_img("../assets/images/shield_gray.png");

            if (!red_dot_texture)
            {
                red_dot_texture = load_img("../assets/images/red_dot.png");   // Images must be same size
                blue_dot_texture = load_img("../assets/images/blue_dot.png"); // Use transparency to deal with different visible sizes
                gray_dot_texture = load_img("../assets/images/gray_dot.png");
                SDL_QueryTexture(red_dot_texture, NULL, NULL, &icon_rect.w, &icon_rect.h);
                step_x = base_overlay_rect.w / (map_length + 1);
            }
            if (map != NULL)
                free_map(map, height_index, map_length);
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

        // Display life and shield
        SDL_RenderCopy(renderer, health_bg_texture, NULL, &health_bg_rect);
        // TODO Add ability to track max health?
        health_rect.w = health_clip.w = self->health * health_bg_rect.w / 100;
        SDL_RenderCopy(renderer, health_texture, &health_clip, &health_rect);

        SDL_RenderCopy(renderer, shield_bg_texture, NULL, &shield_bg_rect);
        shield_rect.w = self->shield * shield_bg_rect.w / 50;
        shield_clip.w = shield_rect.w;
        SDL_RenderCopy(renderer, shield_texture, &shield_clip, &shield_rect);

        // TODO Manage combat here
        int current_col = 0;
        // Display player's ship
        SDL_RenderCopy(renderer, self_texture, NULL, &self_rect);
        // Display foe
        SDL_RenderCopy(renderer, foe_texture, NULL, &foe_rect);

        // Display foe's health/shield

        // Display combat choice box

        // Manage foe's attack

        // Display help
        if (show_help)
        {
            SDL_RenderCopy(renderer, bg_overlay, NULL, &help_rect);
            SDL_RenderCopy(renderer, help_texture, NULL, NULL);
        }

        // Display overlay
        if (msg_counter < NB_DIALOGS)
        {
            dialog_texture = texture_from_text(font, 10, base_overlay_rect, dialogs[msg_counter], white, ALIGN_LEFT);

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
            // Display map
            SDL_RenderCopy(renderer, bg_overlay, NULL, NULL);

            // Reset icon's position if the map has already been shown
            icon_rect.x = base_overlay_rect.x - icon_rect.w / 2;

            // Display all dots
            for (int i = 0; i < map_length; i++)
            {
                // Increment dot's position
                icon_rect.x += step_x;

                icon_rect.y = base_overlay_rect.y - icon_rect.h / 2;
                step_y = base_overlay_rect.h / (height_index[i] + 1);
                for (int j = 0; j < height_index[i]; j++)
                {
                    icon_rect.y += step_y;
                    // TODO prepare special dot for the boss
                    dot_texture = map[i][j]->is_shop ? blue_dot_texture : red_dot_texture;
                    SDL_RenderCopy(renderer, dot_texture, NULL, &icon_rect);

                    if (i == current_col && j == choice_node)
                    {
                        // Display pointer on node
                        alien_pointer_map_rect = rect_from_texture(alien_pointer, icon_rect.x, icon_rect.y);
                        alien_pointer_map_rect.x -= alien_pointer_map_rect.w + 5;
                        SDL_RenderCopy(renderer, alien_pointer, NULL, &alien_pointer_map_rect);
                    }
                }
            }

            SDL_RenderPresent(renderer);
            action = true;

            // Choose a node
            SDL_Event e;
            bool node_chosen = false;
            bool valid_input = false;
            while (!valid_input)
            {
                SDL_WaitEvent(&e);
                if (e.type != SDL_KEYUP)
                    continue;
                valid_input = true;
                switch (e.key.keysym.sym)
                {
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                case SDLK_SPACE:
                case SDLK_KP_SPACE:
                    node_chosen = true;
                    show_map = false;
                    break;
                case SDLK_DOWN:
                case SDLK_j:
                    choice_node = (choice_node + 1) % height_index[current_col];
                    break;
                case SDLK_UP:
                case SDLK_k:
                    choice_node = (choice_node + height_index[current_col] - 1) % height_index[current_col];
                    break;
                default:
                    valid_input = false;
                    break;
                }
            }

            if (node_chosen)
            {
                foe = load_foe(map, choice_node, current_col, height_index[current_col]);
                // foe is right-aligned
                if (foe_texture != NULL)
                    SDL_DestroyTexture(foe_texture);
                foe_texture = load_img(foe->img_path);
                foe_rect = rect_from_texture(foe_texture, foe_rect.x, foe_rect.y);
                rect_scale(&foe_rect, SHIPS_SCALE);
                foe_health_bg_rect.x = foe_health_rect.x = foe_rect.x;
                foe_rect.x -= foe_rect.w;
            }
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
        if (choice == QUIT_GAME && can_continue)
        {
            SDL_Texture *confirm_quit_texture = texture_from_text(font, 1, base_overlay_rect, "Voulez-vous vraiment quitter ?", white, ALIGN_LEFT);
            SDL_Texture *quit_choice_texture = texture_from_text(font, 1, continue_msg_rect, "(O)ui / (N)on", white, ALIGN_RIGHT);

            SDL_RenderCopy(renderer, bg_overlay, NULL, NULL);
            SDL_RenderCopy(renderer, confirm_quit_texture, NULL, NULL);
            SDL_RenderCopy(renderer, quit_choice_texture, NULL, NULL);

            SDL_RenderPresent(renderer);

            SDL_Event e;
            bool has_chosen = false;
            while (SDL_WaitEvent(&e) && !has_chosen)
            {
                switch (e.type)
                {
                case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_o)
                        has_chosen = true;
                    else if (e.key.keysym.sym == SDLK_n)
                    {
                        choice = CONTINUE_GAME;
                        has_chosen = true;
                    }
                    break;
                default:
                    break;
                }
            }
        }
#endif
    }

    /* Leave game */
    if (self != NULL)
        free(self); // or let it go, go, go
    if (map != NULL)
        free(map);
    SDL_DestroyTexture(help_texture);
    SDL_DestroyTexture(health_texture);
    SDL_DestroyTexture(health_bg_texture);
    SDL_DestroyTexture(shield_texture);
    SDL_DestroyTexture(shield_bg_texture);
    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(red_dot_texture);
    SDL_DestroyTexture(blue_dot_texture);
    SDL_DestroyTexture(gray_dot_texture);
    SDL_DestroyTexture(continue_texture);
    SDL_DestroyTexture(bg_overlay);
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
