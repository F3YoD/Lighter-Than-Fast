#include "game.h"

#define SHIPS_SCALE 6

void
play_game(void)
{
    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Map
    map_t map = NULL;
    unsigned short map_length = 6, map_max_height = 4;
    unsigned short height_index[map_length];
    int choice_node = 0;

    // Prepare shuttles
    ship_t *self = NULL, *foe = NULL;
    int self_curr_health, foe_curr_health, self_curr_shield, foe_curr_shield;

    // Gameplay
    enum menu_choice choice = NEW_GAME;
    unsigned msg_counter, current_col;
    int next_loop_delay, next_loop_time;
    SDL_Event event;
    bool show_menu = true;
    bool show_help = false;
    bool show_map = false;
    bool can_continue = false;
    bool action = false;

    while (choice != QUIT_GAME)
    { // Game loop, everything happens here
        SDL_RenderClear(renderer);
        next_loop_time = SDL_GetTicks() + 25; // 40 fps
        action = false;

        if (show_menu)
        { // Display user menu
            choice = menu(can_continue);
            show_menu = false;
            if (!can_continue && choice == QUIT_GAME)
                break;
        }
        if (!can_continue || choice == NEW_GAME)
        { // Load textures if not done, (re)gen map, reset messages counter
            display_fake_loading(1500);
            load_interface_components();

            msg_counter = 0;
            current_col = 0;
            can_continue = true;

            if (self != NULL)
                free(self);
            self = load_self();
            self_curr_health = self->health;
            self_curr_shield = self->shield;

            if (map != NULL)
                free_map(map, height_index, map_length);
            map = (map_t)malloc(map_length * sizeof(map_col_t));
            gen_map(map, height_index, map_length, map_max_height);
#ifdef DEBUG
            for (unsigned i = 0; i < map_length; i++)
                for (int j = 0; j < height_index[i]; j++)
                    printf("%d%s", j, (j == height_index[i] - 1) ? "\n" : " ");
#endif
        }

        render_background();

        // FIXME Manage combat here
        // Display player's ship
        render_self(self, self_curr_health, self_curr_shield);

        if (foe != NULL)
            render_foe(foe, foe_curr_health, foe_curr_shield);

        // Display combat choice box
        // TODO flip a coin to know whether the foe or the player starts

        // Manage foe's attack

        if (show_help)
            render_help_box();

        if (msg_counter < NB_DIALOGS)
        { // Display dialog
            display_dialog(msg_counter++);

            wait_key_press(-1);
            choice = CONTINUE_GAME;
            show_map = true;

            continue;
        }
        else if (show_map)
        { // Display map
            display_map(map, map_length, height_index, current_col, choice_node);

            // Choose a node
            bool node_chosen = false;
            bool valid_input = false;
            while (!valid_input)
            { // Wait till a node is chosen
                SDL_WaitEvent(&event);
                if (event.type != SDL_KEYUP)
                    continue;
                valid_input = true;
                switch (event.key.keysym.sym)
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
            { // Get foe from chosen map node
                foe = load_foe(map, choice_node, current_col, height_index[current_col]);
                foe_curr_health = foe->health;
                foe_curr_shield = foe->shield;
            }

            continue;
        }

        SDL_RenderPresent(renderer);

        // TODO try with SDL_WaitEvent once this is more complete
        while (SDL_PollEvent(&event) && !action)
        { // Get user input
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
        }

#ifndef DEBUG
        if (choice == QUIT_GAME && can_continue)
        { // Ask for user's confirmation to quit
            display_quit_dialog();

            bool has_chosen = false;
            while (!has_chosen)
            {
                SDL_WaitEvent(&event);
                if (event.type != SDL_KEYUP)
                    continue;
                if (event.key.keysym.sym == SDLK_o)
                    has_chosen = true;
                else if (event.key.keysym.sym == SDLK_n)
                {
                    choice = CONTINUE_GAME;
                    has_chosen = true;
                }
            }
        }

#endif
        // Wait before rendering next frame
        next_loop_delay = next_loop_time - SDL_GetTicks();
        if (next_loop_delay > 0)
            SDL_Delay(next_loop_delay);
    }

    /* Leave game */
    if (self != NULL)
        free(self); // or let it go, go, go
    if (map != NULL)
        free(map);
    free_interface_components();
    SDL_RenderClear(renderer);
}
