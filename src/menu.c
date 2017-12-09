#include "menu.h"

#define BANNER_PATH "../assets/images/side_banner.png"

enum menu_choice menu(bool can_continue)
{
    #ifdef DEBUG
    puts("* Loading menu");
    #endif
    // *** Load background ***
    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0x19);

    SDL_Rect banner_rect = { 700, 0, 212, 768 };
    SDL_Texture *banner_texture = load_img(BANNER_PATH);
    SDL_Rect pointer_rect;
    SDL_Texture *pointer = load_img("../assets/images/alien1.png");
    SDL_QueryTexture(pointer, NULL, NULL, &pointer_rect.w, &pointer_rect.h);

    // *** Load text ***
    SDL_Rect base_txt_box = { 100, 620, 1, 1 };
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Color gray = { 0x20, 0x20, 0x20, 0xFF };

    char **menu_txt = (char **)malloc(NB_CHOICES * sizeof(char *));
    menu_txt[CONTINUE_GAME] = "Continuer";
    menu_txt[NEW_GAME] = "Nouvelle partie";
    menu_txt[QUIT_GAME] = "Quitter";

    SDL_Texture *tmp_tex = NULL;
    SDL_Texture **choices_textures = (SDL_Texture **)malloc(NB_CHOICES * sizeof(SDL_Texture *));
    for (int i = 0; i < NB_CHOICES; i++)
        choices_textures[i] = create_txt(font, menu_txt[i],
                                         ((i != CONTINUE_GAME || can_continue) ? white : gray));

    // *** Get user's choice ***
    enum menu_choice choice = can_continue ? CONTINUE_GAME : NEW_GAME;
    int quit = false;
    SDL_Event event;
    while (!quit)
    {
        // Show interface
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, banner_texture, NULL, &banner_rect);

        base_txt_box.y = 620;
        for (int i = NB_CHOICES - 1; i >= 0; i--)
        {
            tmp_tex = choices_textures[i];
            if (choice == i)
            {
                // Display alien as pointer
                pointer_rect.x = base_txt_box.x - pointer_rect.w - 8;
                pointer_rect.y = base_txt_box.y + (TTF_FontHeight(font) - pointer_rect.h) / 2;
                SDL_RenderCopy(renderer, pointer, NULL, &pointer_rect);
            }
            SDL_QueryTexture(tmp_tex, NULL, NULL, &base_txt_box.w, &base_txt_box.h);
            SDL_RenderCopy(renderer, tmp_tex, NULL, &base_txt_box);
            base_txt_box.y -= base_txt_box.h * 2;
        }

        SDL_RenderPresent(renderer);

        // Get user input
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_RETURN:
            case SDLK_RETURN2:
            case SDLK_KP_ENTER:
            case SDLK_SPACE:
            case SDLK_KP_SPACE:
                quit = true;
                break;
            case SDLK_ESCAPE:
            case SDLK_TAB:
                if (can_continue)
                {
                    choice = CONTINUE_GAME;
                    quit = true;
                }
                break;
            case SDLK_DOWN:
            case SDLK_j:
                choice = (choice + 1) % NB_CHOICES;
                if (!can_continue && choice == CONTINUE_GAME)
                    choice = (choice + 1) % NB_CHOICES;
                break;
            case SDLK_UP:
            case SDLK_k:
                choice = (choice + NB_CHOICES - 1) % NB_CHOICES;
                if (!can_continue && choice == CONTINUE_GAME)
                    choice = (choice + NB_CHOICES - 1) % NB_CHOICES;
                break;
            case SDLK_q:
                choice = QUIT_GAME;
                quit = true;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            choice = NEW_GAME;
        case SDL_QUIT:
            quit = true;
        default:
            break;
        }
    }

    // *** Cleaning ***
    for (int i = 0; i < NB_CHOICES; i++)
        SDL_DestroyTexture(choices_textures[i]);
    free(choices_textures);
    free(menu_txt);
    SDL_DestroyTexture(banner_texture);
    SDL_RenderClear(renderer);

    return choice;
}
