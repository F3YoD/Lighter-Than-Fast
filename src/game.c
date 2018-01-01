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
    bool node_chosen = false;
    bool valid_input = false;

    // Prepare shuttles
    ship_t *self = NULL, *foe = NULL;
    int self_curr_health, foe_curr_health, self_curr_shield, foe_curr_shield;

    // Gameplay
    enum menu_choice mchoice = NEW_GAME;
    enum combat_choice cchoice = COMBAT_ATTACK;
    enum shop_choice schoice = SHOP_HEALTH;
    unsigned msg_counter, current_col;
    int next_loop_delay, next_loop_time;
    SDL_Event event;
    bool show_menu = true;
    bool show_help = false;
    bool show_map = false;
    bool can_continue = false;

    while (mchoice != QUIT_GAME)
    { // Game loop, everything happens here
        SDL_RenderClear(renderer);
        next_loop_time = SDL_GetTicks() + 20; // 50 fps

        if (show_menu)
        { // Display user menu
            mchoice = menu(can_continue);
            show_menu = false;
            if (!can_continue && mchoice == QUIT_GAME)
                break;
        }
        if (!can_continue || mchoice == NEW_GAME)
        { // Load textures if not done, (re)gen map, reset messages counter
#ifdef DEBUG
            display_fake_loading(500);
#else
            display_fake_loading(can_continue ? 500 : 1500);
#endif
            load_interface_components();

            msg_counter = 0;
            current_col = 0;
            can_continue = true;

            if (self)
                free(self);
            self = load_self();
            self_curr_health = self->health;
            self_curr_shield = self->shield;

            if (foe)
            {
                free(foe); // FIXME isn't it freed in free_map?
                foe = NULL;
            }

            if (map)
                free_map(map, height_index, map_length);
            map = gen_map(height_index, map_length, map_max_height);
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

        if (foe)
        {
            render_foe(foe, foe_curr_health, foe_curr_shield);
            if (foe->is_shop)
            {
                render_shop_box(schoice, self, foe);
            }
            else
            {
                render_combat_box(cchoice, self);
            }

            if (false) // FIXME foe is dead, actually setting the foe as NULL is enough
                node_chosen = false;
        }

        // TODO flip a coin to know whether the foe or the player starts

        // Manage foe's attack

        if (show_help)
            render_help_box();

        if (msg_counter < NB_DIALOGS)
        {
            display_dialog(msg_counter++);

            wait_key_press(-1);
            mchoice = CONTINUE_GAME;
            show_map = true;

            continue;
        }
        else if (show_map)
        {
            display_map(map, map_length, height_index, current_col, choice_node);

            // Choose a node
            valid_input = false;
            while (!valid_input)
            { // Wait till a node is chosen
                SDL_WaitEvent(&event);
                if (event.type != SDL_KEYUP)
                    continue;
                node_chosen = false;
                valid_input = true;
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                case SDLK_SPACE:
                case SDLK_KP_SPACE:
                    if (!foe)
                        node_chosen = true;
                    show_map = false;
                    break;
                case SDLK_DOWN:
                case SDLK_j:
                    if (!foe)
                        choice_node = (choice_node + 1) % height_index[current_col];
                    break;
                case SDLK_UP:
                case SDLK_k:
                    if (!foe)
                        choice_node = (choice_node + height_index[current_col] - 1) % height_index[current_col];
                    break;
                case SDLK_ESCAPE:
                case SDLK_m:
                    if (foe)
                        show_map = false;
                    break;
                default:
                    valid_input = false;
                    break;
                }
            }

            if (node_chosen)
            {
                foe = load_foe(map, choice_node, current_col, height_index[current_col]);
                foe_curr_health = foe->health;
                foe_curr_shield = foe->shield;
            }

            continue;
        }

        SDL_RenderPresent(renderer);

        // TODO try with SDL_WaitEvent once this is more complete
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mchoice = QUIT_GAME;
                break;
            }
            else if (event.type != SDL_KEYUP)
                continue;

            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_TAB:
                show_menu = true;
                break;
            case SDLK_m:
                show_map = !show_map;
                break;
            case SDLK_h:
                show_help = !show_help;
                break;
            case SDLK_UP:
            case SDLK_k:
                if (foe && foe->is_shop)
                    schoice = (schoice + NB_CHOICES_SHOP - 1) % NB_CHOICES_SHOP;
                else if (foe)
                    cchoice = (cchoice + NB_CHOICES_COMBAT - 1) % NB_CHOICES_COMBAT;
                break;
            case SDLK_DOWN:
            case SDLK_j:
                if (foe && foe->is_shop)
                    schoice = (schoice + 1) % NB_CHOICES_SHOP;
                else if (foe)
                    cchoice = (cchoice + 1) % NB_CHOICES_COMBAT;
                break;
            case SDLK_RETURN:
            case SDLK_RETURN2:
            case SDLK_KP_ENTER:
            case SDLK_SPACE:
            case SDLK_KP_SPACE:
                if (foe && foe->is_shop)
                    switch (schoice)
                    {
                    case SHOP_HEALTH:
                        break;
                    case SHOP_SCRAPS:
                        break;
                    case SHOP_LEAVE:
                        break;
                    default:
                        break;
                    }
                else if (foe)
                    switch (cchoice)
                    {
                    case COMBAT_ATTACK:
                        shoot(foe, self, 0);
                        break;
                    case COMBAT_REPAIR:
                        break;
                    case COMBAT_FLEE:
                        break;
                    default:
                        break;
                    }
                break;
#ifdef DEBUG
            case SDLK_q:
                mchoice = QUIT_GAME;
                break;
            case SDLK_n:
                mchoice = NEW_GAME;
                break;
#endif
            default:
                continue;
            }
            break;
        }

#ifndef DEBUG
        // Ask for user's confirmation to quit
        if (mchoice == QUIT_GAME && can_continue)
        {
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
                    mchoice = CONTINUE_GAME;
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

    // Leave game
    // TODO create goodbye screen
    if (self != NULL)
        free(self); // or let it go, go, go
    if (map != NULL)
        free(map);
    free_interface_components();
    SDL_RenderClear(renderer);
}
