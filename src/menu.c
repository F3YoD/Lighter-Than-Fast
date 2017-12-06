#include "menu.h"

#define BANNER_PATH "../assets/images/side_banner.png"

menu_choice_t menu(bool can_continue)
{
    #ifdef DEBUG
    puts("* Loading menu");
    #endif
    // *** Load background ***
    SDL_SetRenderDrawColor(renderer, 0x06, 0x00, 0x0B, 0x19);
    SDL_Rect bg = { 0, 0, 1024, 768 };
    SDL_RenderFillRect(renderer, &bg);

    SDL_Rect banner_pos = { 700, 0, 212, 768 };

    SDL_Texture *banner_texture = NULL;
    SDL_Texture *pointer = NULL;
    banner_texture = IMG_LoadTexture(renderer, BANNER_PATH);
    check_IMG(banner_texture);
    pointer = IMG_LoadTexture(renderer, "../assets/images/alien1.png");
    check_IMG(pointer);
    int pointer_w, pointer_h;
    SDL_QueryTexture(pointer, NULL, NULL, &pointer_w, &pointer_h);

    // *** Load text ***
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Color gray = { 0x20, 0x20, 0x20, 0xFF };

    char **menu_txt = (char **)malloc(NB_CHOICES * sizeof(char *));
    menu_txt[CONTINUE_GAME] = "Continuer";
    menu_txt[NEW_GAME] = "Nouvelle partie";
    menu_txt[QUIT_GAME] = "Quitter";

    SDL_Surface *tmp_sur = NULL;
    SDL_Texture *tmp_tex = NULL;
    SDL_Texture **choices_textures = (SDL_Texture **)malloc(NB_CHOICES * sizeof(SDL_Texture *));
    for (int i = 0; i < NB_CHOICES; i++)
    {
        tmp_sur = TTF_RenderText_Blended(font, menu_txt[i],
                                         ((i != CONTINUE_GAME || can_continue) ? white : gray));
        check_TTF(tmp_sur);
        choices_textures[i] = SDL_CreateTextureFromSurface(renderer, tmp_sur);
        check_SDL(choices_textures[i]);
        SDL_FreeSurface(tmp_sur);
    }

    // *** Get user's choice ***
    enum menu_choice choice = can_continue ? CONTINUE_GAME : NEW_GAME;
    int quit = false;
    SDL_Event event;
    while (!quit)
    {
        // Show interface
        SDL_RenderCopy(renderer, banner_texture, NULL, &banner_pos);

        SDL_Rect txt_box = { 100, 620, 1, 1 };
        for (int i = NB_CHOICES - 1; i >= 0; i--)
        {
            tmp_tex = choices_textures[i];
            if (choice == i)
            {
                // Display alien as pointer
                SDL_Rect pointer_pos = { txt_box.x - pointer_w - 8, txt_box.y + (TTF_FontHeight(font) - pointer_h) / 2, pointer_w, pointer_h };
                SDL_RenderCopy(renderer, pointer, NULL, &pointer_pos);
            }
            SDL_QueryTexture(tmp_tex, NULL, NULL, &txt_box.w, &txt_box.h);
            SDL_RenderCopy(renderer, tmp_tex, NULL, &txt_box);
            txt_box.y -= txt_box.h * 2;
        }

        SDL_RenderPresent(renderer);

        // Get user input
        while (SDL_PollEvent(&event))
        {
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
        SDL_RenderClear(renderer);
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
