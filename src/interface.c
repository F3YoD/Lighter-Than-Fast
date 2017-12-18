#include "interface.h"

/* Global colors */
static SDL_Color white;

/* Global textures */
static SDL_Texture *bg_texture, *bg_overlay, *dialog_texture, *continue_texture, *alien_pointer;
static SDL_Texture *health_texture, *health_bg_texture, *shield_texture, *shield_bg_texture;
static SDL_Texture *red_dot_texture, *blue_dot_texture, *gray_dot_texture, *dot_texture;
static SDL_Texture *help_texture;
static SDL_Texture *self_texture, *foe_texture;

/* Rendering zones (i.e. rectangles) */
static SDL_Rect inner_overlay_rect, continue_msg_rect;
static SDL_Rect icon_rect, alien_pointer_map_rect;
static SDL_Rect help_rect;
static SDL_Rect self_rect, foe_rect;

void
load_interface_components(void)
{
    static bool loaded = false;
    if (loaded) return;

    bg_texture = load_img(BACKGROUND_IMAGE);
    bg_overlay = load_img("../assets/images/1px_overlay.png");
    continue_texture = texture_from_text(font, 1, continue_msg_rect, "Appuyez sur une touche pour continuer...", white, ALIGN_RIGHT);
    alien_pointer = load_img("../assets/images/alien1.png");

    health_bg_texture = load_img("../assets/images/health_gray.png");
    health_texture = load_img("../assets/images/health.png");
    shield_bg_texture = load_img("../assets/images/shield_gray.png");
    shield_texture = load_img("../assets/images/shield.png");

    red_dot_texture = load_img("../assets/images/red_dot.png");
    blue_dot_texture = load_img("../assets/images/blue_dot.png");
    gray_dot_texture = load_img("../assets/images/gray_dot.png");

    help_texture = texture_from_text(font, 5, help_rect, help_txt, white, ALIGN_LEFT);

    self_texture = foe_texture = NULL;

    init_colors();
    init_rectangles();

    loaded = true;
}

void
free_interface_components(void)
{
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bg_overlay);
    SDL_DestroyTexture(continue_texture);
    SDL_DestroyTexture(alien_pointer);

    SDL_DestroyTexture(health_bg_texture);
    SDL_DestroyTexture(health_texture);
    SDL_DestroyTexture(shield_bg_texture);
    SDL_DestroyTexture(shield_texture);

    SDL_DestroyTexture(help_texture);

    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(foe_texture);
}

void
init_colors(void)
{
    white = (SDL_Color){ 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };
    // FIXME add gray color, even others?
}

void
init_rectangles(void)
{
    static bool initiated = false;
    if (initiated) return;

    // FIXME inner_overlay_rect was formerly known as base_overlay_rect
    inner_overlay_rect = (SDL_Rect){ WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4, 3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 };
    continue_msg_rect = (SDL_Rect){ 5 * WINDOW_WIDTH / 6, 3 * WINDOW_HEIGHT / 4, 1, 1 };

    help_rect = rect_from_texture(help_texture, WINDOW_WIDTH - 224, WINDOW_HEIGHT - 64);
    help_rect.x -= 10;
    help_rect.y -= 10;
    help_rect.w += 20;
    help_rect.h += 20;

    SDL_QueryTexture(red_dot_texture, NULL, NULL, &icon_rect.w, &icon_rect.h);
}

void
display_map(map_t map, unsigned map_length, unsigned short height_index[], unsigned current_col, unsigned choice_node)
{
    render_overlay_bg(NULL);

    unsigned step_x = inner_overlay_rect.w / (map_length + 1);
    unsigned step_y;

    icon_rect.x = inner_overlay_rect.x - icon_rect.w / 2;

    for (unsigned short i = 0; i < map_length; i++)
    { // Display all dots
        icon_rect.x += step_x;

        icon_rect.y = inner_overlay_rect.y - icon_rect.h / 2;
        step_y = inner_overlay_rect.h / (height_index[i] + 1);
        for (unsigned short j = 0; j < height_index[i]; j++)
        {
            icon_rect.y += step_y;
            // TODO prepare special dot for the boss
            dot_texture = map[i][j]->is_shop ? blue_dot_texture : red_dot_texture;
            SDL_RenderCopy(renderer, dot_texture, NULL, &icon_rect);

            if (i == current_col && j == choice_node)
            { // Display pointer on node
                alien_pointer_map_rect = rect_from_texture(alien_pointer, icon_rect.x, icon_rect.y);
                alien_pointer_map_rect.x -= alien_pointer_map_rect.w + 5;
                SDL_RenderCopy(renderer, alien_pointer, NULL, &alien_pointer_map_rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void
display_fake_loading(unsigned miliseconds)
{ //  A fake loading screen
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

void
display_dialog(unsigned counter)
{
    render_overlay_bg(NULL);

    dialog_texture = texture_from_text(font, 10, inner_overlay_rect, dialogs[counter], white, ALIGN_LEFT);

    SDL_RenderCopy(renderer, dialog_texture, NULL, NULL);
    SDL_RenderCopy(renderer, continue_texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(dialog_texture);
}

void
display_quit_dialog(void)
{
    SDL_Texture *confirm_quit_texture = texture_from_text(font, 1, inner_overlay_rect, "Voulez-vous vraiment quitter ?", white, ALIGN_LEFT);
    SDL_Texture *quit_choice_texture = texture_from_text(font, 1, continue_msg_rect, "(O)ui / (N)on", white, ALIGN_RIGHT);

    render_overlay_bg(NULL);
    SDL_RenderCopy(renderer, confirm_quit_texture, NULL, NULL);
    SDL_RenderCopy(renderer, quit_choice_texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(confirm_quit_texture);
    SDL_DestroyTexture(quit_choice_texture);
}

void
render_self(ship_t *self, short health, short shield)
{
    if (!self_texture)
    {
        self_texture = load_img(self->img_path);
        self_rect = rect_from_texture(self_texture, WINDOW_WIDTH / 20, 2 * WINDOW_HEIGHT / 7);
        rect_scale(&self_rect, 6);
    }

    SDL_RenderCopy(renderer, self_texture, NULL, &self_rect);
    render_bars(self, &self_rect, health, shield, false);
}

void
render_foe(ship_t *foe, short health, short shield)
{
    static ship_t *prev_foe = NULL;

    if (foe != prev_foe)
    {
        if (prev_foe)
            SDL_DestroyTexture(foe_texture);

        foe_texture = load_img(foe->img_path);
        foe_rect = rect_from_texture(foe_texture, 19 * WINDOW_WIDTH / 20, 2 * WINDOW_HEIGHT / 7);
        rect_scale(&foe_rect, 8);
        foe_rect.x -= foe_rect.w;

        prev_foe = foe;
    }

    SDL_RenderCopy(renderer, foe_texture, NULL, &foe_rect);
    render_bars(foe, &foe_rect, health, shield, true);
}

void
render_bars(ship_t *ship, SDL_Rect *ship_rect, int health, int shield, bool reversed)
{ // Health and shield bars rendering
    static bool first_run = true;
    static SDL_Rect health_bg_rect, shield_bg_rect, health_rect, shield_rect, health_clip, shield_clip;

    if (first_run)
    { // Init rect
        SDL_QueryTexture(health_bg_texture, NULL, NULL, &health_bg_rect.w, &health_bg_rect.h);
        SDL_QueryTexture(shield_bg_texture, NULL, NULL, &shield_bg_rect.w, &shield_bg_rect.h);
        health_rect.h = health_clip.h = health_bg_rect.h;
        shield_rect.h = shield_clip.h = shield_bg_rect.h;
        first_run = false;
    }

    // Define bars positions
    if (reversed)
        health_bg_rect.x = health_rect.x = shield_bg_rect.x = shield_rect.x = ship_rect->x + ship_rect->w;
    else
        health_bg_rect.x = health_rect.x = shield_bg_rect.x = shield_rect.x = ship_rect->x;
    health_bg_rect.y = health_rect.y = ship_rect->y + ship_rect->h + 10;
    shield_bg_rect.y = shield_rect.y = health_bg_rect.y + health_bg_rect.h + 2;

    // Define clipping
    health_rect.w = health_clip.w = health * health_bg_rect.w / ship->health;
    shield_rect.w = shield_clip.w = shield * shield_bg_rect.w / ship->shield;

    if (reversed)
    { // Move bars aside
        health_rect.x = health_bg_rect.x -= health_bg_rect.w;
        shield_rect.x = shield_bg_rect.x -= shield_bg_rect.w;
        health_clip.x = health_bg_rect.w - health_clip.w;
        shield_clip.x = shield_bg_rect.w - shield_clip.w;
        health_rect.x += health_clip.x;
        shield_rect.x += shield_clip.x;
    }
    else
        health_clip.x = health_clip.y = shield_clip.x = shield_clip.y = 0;

    // Render bars background
    SDL_RenderCopy(renderer, health_bg_texture, NULL, &health_bg_rect);
    SDL_RenderCopy(renderer, shield_bg_texture, NULL, &shield_bg_rect);

    // Render bars foreground
    SDL_RenderCopy(renderer, health_texture, &health_clip, &health_rect);
    SDL_RenderCopy(renderer, shield_texture, &shield_clip, &shield_rect);
}

void
render_help_box(void)
{
    render_overlay_bg(&help_rect);
    SDL_RenderCopy(renderer, help_texture, NULL, NULL);
}

void
render_overlay_bg(SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, bg_overlay, NULL, rect);
}

void
render_background(void)
{
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
}
