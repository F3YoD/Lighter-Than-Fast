#include "interface.h"

/* Global colors */
static SDL_Color white, gray;

/* Global textures */
static SDL_Texture *bg_texture, *bg_overlay, *dialog_texture, *continue_texture, *alien_pointer;
static SDL_Texture *health_texture, *health_bg_texture, *shield_texture, *shield_bg_texture;
static SDL_Texture *map_texture;
static SDL_Texture *red_dot_texture, *blue_dot_texture, *gray_dot_texture, *dot_texture;
static SDL_Texture *choices_texture;
static SDL_Texture *combat_box_texture;
static SDL_Texture *help_texture;
static SDL_Texture *self_texture, *foe_texture;

/* Rendering zones (i.e. rectangles) */
static SDL_Rect inner_overlay_rect, continue_msg_rect;
static SDL_Rect icon_rect, alien_pointer_map_rect, alien_cursor_r;
static SDL_Rect help_rect;
static SDL_Rect self_rect, foe_rect;

static int font_height;

void
load_interface_components(void)
/**
 * Load images with multiple uses in memory.
 */
{
    static bool loaded = false;
    if (loaded) return;

    bg_texture = load_img(BACKGROUND_IMAGE);
    bg_overlay = load_img("../assets/images/1px_overlay.png");
    continue_texture = texture_from_text(font, 1, continue_msg_rect, "Appuyez sur une touche pour continuer...", white, ALIGN_RIGHT);
    alien_pointer = load_img("../assets/images/alien1.png");

    red_dot_texture = load_img("../assets/images/red_dot.png");
    blue_dot_texture = load_img("../assets/images/blue_dot.png");
    gray_dot_texture = load_img("../assets/images/gray_dot.png");

    self_texture = foe_texture = NULL;

    font_height = TTF_FontHeight(font);

    init_colors();
    init_rectangles();

    loaded = true;
}

void
free_interface_components(void)
/**
 * Destroy static textures of this file.
 * FIXME check if all textures are present here
 */
{
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(bg_overlay);
    SDL_DestroyTexture(continue_texture);
    SDL_DestroyTexture(alien_pointer);

    SDL_DestroyTexture(health_bg_texture);
    SDL_DestroyTexture(health_texture);
    SDL_DestroyTexture(shield_bg_texture);
    SDL_DestroyTexture(shield_texture);

    SDL_DestroyTexture(map_texture);

    SDL_DestroyTexture(red_dot_texture);
    SDL_DestroyTexture(blue_dot_texture);
    SDL_DestroyTexture(gray_dot_texture);

    SDL_DestroyTexture(choices_texture);
    SDL_DestroyTexture(combat_box_texture);
    SDL_DestroyTexture(help_texture);

    SDL_DestroyTexture(self_texture);
    SDL_DestroyTexture(foe_texture);
}

void
init_colors(void)
/**
 * Create colors for text rendering.
 */
{
    static bool initiated = false;
    if (initiated) return;

    white = (SDL_Color){ 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE };
    gray = (SDL_Color){ 0x20, 0x20, 0x20, SDL_ALPHA_OPAQUE };

    initiated = true;
}

void
init_rectangles(void)
/**
 * Set values for SDL_Rects with multiple uses.
 */
{
    static bool initiated = false;
    if (initiated) return;

    // FIXME inner_overlay_rect was formerly known as base_overlay_rect
    inner_overlay_rect = (SDL_Rect){ WINDOW_WIDTH / 8, WINDOW_HEIGHT / 4, 3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 };
    continue_msg_rect = (SDL_Rect){ 5 * WINDOW_WIDTH / 6, 3 * WINDOW_HEIGHT / 4, 1, 1 };

    SDL_QueryTexture(alien_pointer, NULL, NULL, &alien_cursor_r.w, &alien_cursor_r.h);

    SDL_QueryTexture(red_dot_texture, NULL, NULL, &icon_rect.w, &icon_rect.h);

    initiated = true;
}

void
display_menu(void)
{
    // FIXME
}

void
display_map(map_t map, unsigned map_length, unsigned short height_index[], unsigned current_col, unsigned choice_node)
/**
 * Render the map and display it on an overlay.
 */
{
    static map_t prev_map;
    static unsigned short prev_col, prev_node;

    if (map_texture && map == prev_map && current_col == prev_col && choice_node == prev_node)
    {
        SDL_RenderCopy(renderer, map_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        return;
    }

    if (map_texture)
        SDL_DestroyTexture(map_texture);
    map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, map_texture);

    render_overlay_bg(NULL, 0);

    // Define the distance between two dots on map
    unsigned step_x = inner_overlay_rect.w / (map_length + 1);
    unsigned step_y;

    icon_rect.x = inner_overlay_rect.x - icon_rect.w / 2;

    // Render all columns
    for (unsigned short i = 0; i < map_length; i++)
    {
        // Determinate x position of this dot
        icon_rect.x += step_x;
        icon_rect.y = inner_overlay_rect.y - icon_rect.h / 2;

        step_y = inner_overlay_rect.h / (height_index[i] + 1);

        // Render all nodes
        for (unsigned short j = 0; j < height_index[i]; j++)
        {
            // Determinate y position
            icon_rect.y += step_y;

            // Choose icon texture depending on map node's nature
            if (!map[i] || !map[i][j])
                dot_texture = gray_dot_texture;
            else if (map[i][j]->is_shop)
                dot_texture = blue_dot_texture;
            else if (i == map_length - 1)
                dot_texture = red_dot_texture; // TODO prepare special dot for the boss
            else
                dot_texture = red_dot_texture;

            SDL_RenderCopy(renderer, dot_texture, NULL, &icon_rect);

            // Render cursor if necessary
            if (i == current_col && j == choice_node)
            {
                alien_pointer_map_rect = rect_from_texture(alien_pointer, icon_rect.x, icon_rect.y);
                alien_pointer_map_rect.x -= alien_pointer_map_rect.w + 5;
                alien_pointer_map_rect.y += (TTF_FontHeight(font) - alien_pointer_map_rect.h) / 2;
                SDL_RenderCopy(renderer, alien_pointer, NULL, &alien_pointer_map_rect);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderCopy(renderer, map_texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}

void
display_fake_loading(unsigned miliseconds)
/**
 * Display a fake loading screen during a given time in miliseconds.
 */
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

void
display_dialog(unsigned counter)
/**
 * Display immersive text.
 */
{
    render_overlay_bg(NULL, 0);

    dialog_texture = texture_from_text(font, 10, inner_overlay_rect, dialogs[counter], white, ALIGN_LEFT);

    SDL_RenderCopy(renderer, dialog_texture, NULL, NULL);
    SDL_RenderCopy(renderer, continue_texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(dialog_texture);
}

void
display_quit_dialog(void)
/**
 * Display text asking user if he wants to quit the game.
 */
{
    SDL_Texture *confirm_quit_texture = texture_from_text(font, 1, inner_overlay_rect, "Voulez-vous vraiment quitter ?", white, ALIGN_LEFT);
    SDL_Texture *quit_choice_texture = texture_from_text(font, 1, continue_msg_rect, "(O)ui / (N)on", white, ALIGN_RIGHT);

    render_overlay_bg(NULL, 0);
    SDL_RenderCopy(renderer, confirm_quit_texture, NULL, NULL);
    SDL_RenderCopy(renderer, quit_choice_texture, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(confirm_quit_texture);
    SDL_DestroyTexture(quit_choice_texture);
}

void
render_self(ship_t *self, short health, short shield)
/**
 * Render the ship representing the player.
 */
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
/**
 * Render the ship representing the ennemy.
 */
{
    static ship_t *prev_foe;

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
render_bars(ship_t *ship, SDL_Rect *ship_rect, short health, short shield, bool reversed)
/**
 * Render health and shield bars.
 * If true, the `reversed' parameter will display the bars for the foe rather than the player.
 * TODO regenerate the texture only if needed (i.e. health or shield change)
 */
{
    static SDL_Rect health_bg_rect, shield_bg_rect, health_rect, shield_rect, health_clip, shield_clip;

    // Load textures and create their rectangles
    if (!health_bg_texture)
    {
        health_bg_texture = load_img("../assets/images/health_gray.png");
        health_texture = load_img("../assets/images/health.png");
        shield_bg_texture = load_img("../assets/images/shield_gray.png");
        shield_texture = load_img("../assets/images/shield.png");

        SDL_QueryTexture(health_bg_texture, NULL, NULL, &health_bg_rect.w, &health_bg_rect.h);
        SDL_QueryTexture(shield_bg_texture, NULL, NULL, &shield_bg_rect.w, &shield_bg_rect.h);
        health_rect.h = health_clip.h = health_bg_rect.h;
        shield_rect.h = shield_clip.h = shield_bg_rect.h;
    }

    // Define bars positions
    if (reversed)
        health_bg_rect.x = health_rect.x = shield_bg_rect.x = shield_rect.x = ship_rect->x + ship_rect->w;
    else
        health_bg_rect.x = health_rect.x = shield_bg_rect.x = shield_rect.x = ship_rect->x;

    health_bg_rect.y = health_rect.y = ship_rect->y + ship_rect->h + 10;
    shield_bg_rect.y = shield_rect.y = health_bg_rect.y + health_bg_rect.h + 2;

    // Define clipping
    health_rect.w = health_clip.w = ship->health * health_bg_rect.w / health;
    shield_rect.w = shield_clip.w = ship->shield * shield_bg_rect.w / shield;

    // Move bars aside if rendering foe
    if (reversed)
    {
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
render_choices(SDL_Rect *choices_r, short nb_choices, char *choices_text[], short current_choice, short mask, short line_spacing, short overlay_padding)
/**
 * Render a set of choices (expressed by the strings in `choices_text[]') with a cursor.
 * The position of the choices on the screen is given through the `choices_r' structure.
 * Forbidden options can be expressed bit-wise with the `mask' parameter.
 * An optionnal overlay can be added if `overlay_padding' is greater or equal to zero.
 */
{
    // FIXME forbid cursor on choices forbidden by mask
    static short prev_mask, prev_choice;
    static char **prev_text;
    static SDL_Rect *prev_choices_r;

    static SDL_Rect bg_r, cursor_r;

    // (Re)evaluate cursor position if necessary
    if (!cursor_r.w || prev_choice != current_choice || prev_choices_r != choices_r)
    {
        // Evaluate cursor position
        if (!cursor_r.w)
            cursor_r = (SDL_Rect){ .w = alien_cursor_r.w, .h = alien_cursor_r.h };
        cursor_r.x = choices_r->x - cursor_r.w - 8;
        cursor_r.y = choices_r->y + (font_height + line_spacing) * current_choice + (font_height - cursor_r.h) / 2;

        // Allow parameters comparison
        prev_choice = current_choice;
    }

    // Reload the texture if a parameter changed
    if (mask != prev_mask || choices_text != prev_text || prev_choices_r != choices_r)
    {
        SDL_Texture *t;
        SDL_Color color;
        SDL_Rect r;

        r = bg_r = (SDL_Rect){ .x = choices_r->x, .y = choices_r->y };

        // Create new texture to render on
        if (choices_texture)
            SDL_DestroyTexture(choices_texture);
        choices_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_SetTextureBlendMode(choices_texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(renderer, choices_texture);

        // Render choices on new texture
        for (int i = 0; i < nb_choices; i++)
        {
            // Write in gray if the mask says so
            color = ((mask >> i) & 1) ? white : gray;
            t = create_txt(font, choices_text[i], color);

            // TODO the following line is inefficient, fix it
            r = rect_from_texture(t, r.x, r.y);
            SDL_RenderCopy(renderer, t, NULL, &r);

            // Memorize the highest width among the lines
            if (r.w > bg_r.w)
                bg_r.w = r.w;

            // Move rendering rectangle downward for next iteration
            if (i < nb_choices - 1)
                r.y += r.h + line_spacing;
            bg_r.h += r.h + (i > 0 ? line_spacing : 0);

            SDL_DestroyTexture(t);
        }

        // Count cursor in overlay size
        if (prev_text != choices_text)
        {
            bg_r.x = cursor_r.x;
            bg_r.w += cursor_r.w + 8;
        }

        // Allow parameters comparision
        prev_mask = mask;
        prev_text = choices_text;
        prev_choices_r = choices_r;
    }

    // Done rendering intermediary texture
    SDL_SetRenderTarget(renderer, NULL);

    // Render & display
    if (overlay_padding >= 0)
        render_overlay_bg(&bg_r, overlay_padding);
    SDL_RenderCopy(renderer, choices_texture, NULL, NULL);
    SDL_RenderCopy(renderer, alien_pointer, NULL, &cursor_r);
}

void
render_combat_box(enum combat_choice choice, ship_t *self)
/**
 * Render dialog to interact with shops
 */
{
    // TODO move this rect to init_rectangles and use it for shops as well if we keep having them at the same place?
    static SDL_Rect combat_r = { WINDOW_WIDTH / 20, 3 * WINDOW_HEIGHT / 4, 1, 1 };
    static short line_spacing = 8;
    short mask = 0;

    short prices[NB_CHOICES_COMBAT]; // TODO define prices
    prices[COMBAT_ATTACK] = 5;
    prices[COMBAT_REPAIR] = 1;
    prices[COMBAT_FLEE] = 10;

    const size_t max_size = 32;
    char *choices_text[NB_CHOICES_SHOP];

    // Constitute mask and perform memory allocation for choices strings
    for (int i = 0; i < NB_CHOICES_SHOP; i++)
    {
        choices_text[i] = (char *)malloc(max_size * sizeof(char));

        if ((i == COMBAT_REPAIR && self->belongings.scraps >= prices[i]) || self->belongings.plasma >= prices[i])
            mask |= 1 << i;
    }

    // Fill strings with actual values
    snprintf(choices_text[COMBAT_ATTACK], max_size, "Attaquer (%d plasma)", prices[COMBAT_ATTACK]);
    snprintf(choices_text[COMBAT_REPAIR], max_size, "Se reparer (%d scraps)", prices[COMBAT_REPAIR]);
    snprintf(choices_text[COMBAT_FLEE], max_size, "Fuir le combat (%d plasma)", prices[COMBAT_FLEE]);

    render_choices(&combat_r, NB_CHOICES_SHOP, choices_text, choice, mask, line_spacing, 20);
}

void
render_shop_box(enum shop_choice choice, ship_t *self, ship_t *shop)
/**
 * Render dialog to interact with shops
 */
{
    static SDL_Rect shop_r = { WINDOW_WIDTH / 20, 3 * WINDOW_HEIGHT / 4, 1, 1 };
    static short line_spacing = 8;
    short mask = 0;

    short prices[NB_CHOICES_SHOP]; // TODO define prices
    prices[SHOP_HEALTH] = 1;
    prices[SHOP_SCRAPS] = 1;
    prices[SHOP_LEAVE] = 0;

    const size_t max_size = 32;
    char *choices_text[NB_CHOICES_SHOP];

    // Constitute mask and perform memory allocation for choices strings
    for (int i = 0; i < NB_CHOICES_SHOP; i++)
    {
        choices_text[i] = (char *)malloc(max_size * sizeof(char));

        if (i == SHOP_LEAVE || (self->belongings.money >= prices[i] && shop->belongings.all[i] > 0))
            mask |= 1 << i;
    }

    // Fill strings with actual values
    snprintf(choices_text[SHOP_HEALTH], max_size, "Se guerir ($%d)", prices[SHOP_HEALTH]);
    snprintf(choices_text[SHOP_SCRAPS], max_size, "Acheter des scraps ($%d)", prices[SHOP_SCRAPS]);
    snprintf(choices_text[SHOP_LEAVE], max_size, "Sortir du shop");

    render_choices(&shop_r, NB_CHOICES_SHOP, choices_text, choice, mask, line_spacing, 20);
}

void
render_help_box(void)
/**
 * Render box to display help during game.
 */
{
    if (!help_texture)
    {
        help_texture = texture_from_text(font, 5, help_rect, help_txt, white, ALIGN_LEFT);
        help_rect = rect_from_texture(help_texture, WINDOW_WIDTH - 224, WINDOW_HEIGHT - 164);
    }


    render_overlay_bg(&help_rect, 10);
    SDL_RenderCopy(renderer, help_texture, NULL, &help_rect);
}

void
render_overlay_bg(SDL_Rect *rect, short padding)
/**
 * Render a semi-transparent background for dialogs/map readability.
 */
{
    SDL_Rect r;
    if (rect)
    {
        r = *rect;

        if (padding)
        {
            r.x -= padding;
            r.y -= padding;
            r.w += 2 * padding;
            r.h += 2 * padding;
        }
    }

    SDL_RenderCopy(renderer, bg_overlay, NULL, (rect ? &r : NULL));
}

void
render_background(void)
/**
 * Render background image.
 */
{
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
}
